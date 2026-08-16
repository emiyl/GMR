import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressRangeIterator;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Program;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.symbol.Namespace;
import ghidra.program.model.symbol.Symbol;
import ghidra.util.task.TaskMonitor;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.lang.reflect.Method;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Iterator;

public class ExportDelinker extends GhidraScript {
    private static final String ANALYZER_CLASS = "ghidra.app.analyzers.RelocationTableSynthesizerAnalyzer";
    private static final String EXPORTER_CLASS = "ghidra.app.util.exporter.CoffRelocatableObjectExporter";

    private static List<String> parseCsvLine(String line) {
        List<String> result = new ArrayList<>();
        StringBuilder current = new StringBuilder();
        boolean inQuotes = false;

        for (char c : line.toCharArray()) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                result.add(current.toString().trim());
                current.setLength(0);
            } else {
                current.append(c);
            }
        }

        result.add(current.toString().trim());
        return result;
    }

    private static final class LittleEndianOutputStream extends ByteArrayOutputStream {
        public void writeByte(int value) {
            write(value & 0xFF);
        }

        public void writeShort(int value) {
            write(value & 0xFF);
            write((value >>> 8) & 0xFF);
        }

        public void writeInt(int value) {
            write(value & 0xFF);
            write((value >>> 8) & 0xFF);
            write((value >>> 16) & 0xFF);
            write((value >>> 24) & 0xFF);
        }
    }

    private static final class Ghidra12CompatibleCoffExporter {
        private static final int PE_IMAGE_FILE_MACHINE_AMD64 = 0x8664;
        private static final int PE_IMAGE_FILE_MACHINE_I386 = 0x014c;
        private static final int IMAGE_SCN_CNT_CODE = 0x00000020;
        private static final int IMAGE_SCN_MEM_EXECUTE = 0x20000000;
        private static final int IMAGE_SCN_MEM_READ = 0x40000000;
        private static final int IMAGE_SCN_ALIGN_16BYTES = 0x00200000;
        private static final int IMAGE_SYM_CLASS_EXTERNAL = 2;
        private static final int IMAGE_SYM_CLASS_SECTION = 3;
        private static final int SIZEOF_SYMBOL = 18;

        public void export(File outFile, Program program, AddressSet set, TaskMonitor monitor) throws Exception {
            if (set == null || set.isEmpty()) {
                throw new IllegalArgumentException("Address set is empty");
            }

            Address sectionStart = set.getMinAddress();
            Memory memory = program.getMemory();
            List<String> functionNames = new ArrayList<>();
            List<Long> functionOffsets = new ArrayList<>();

            Iterator<Function> functions = program.getFunctionManager().getFunctionsOverlapping(set);
            while (functions.hasNext()) {
                Function function = functions.next();
                if (!set.intersects(function.getBody())) {
                    continue;
                }
                functionNames.add(function.getName());
                functionOffsets.add(function.getEntryPoint().subtract(sectionStart));
            }

            if (functionNames.isEmpty()) {
                FunctionIterator allFunctions = program.getFunctionManager().getFunctions(true);
                while (allFunctions.hasNext()) {
                    Function function = allFunctions.next();
                    if (!set.intersects(function.getBody())) {
                        continue;
                    }
                    functionNames.add(function.getName());
                    functionOffsets.add(function.getEntryPoint().subtract(sectionStart));
                }
            }

            if (functionNames.isEmpty()) {
                throw new IllegalStateException("No functions found within selected address set");
            }

            ByteArrayOutputStream rawData = new ByteArrayOutputStream();
            Address current = sectionStart;
            AddressRangeIterator ranges = set.getAddressRanges();
            while (ranges.hasNext()) {
                AddressRange range = ranges.next();
                long gap = range.getMinAddress().subtract(current);
                if (gap > 0) {
                    for (long i = 0; i < gap; i++) {
                        rawData.write(0);
                    }
                }
                int chunkLength = (int) range.getLength();
                byte[] chunk = new byte[chunkLength];
                int read = memory.getBytes(range.getMinAddress(), chunk);
                if (read != chunkLength) {
                    throw new IllegalStateException("Short read from memory: expected " + chunkLength + " got " + read);
                }
                rawData.write(chunk);
                current = range.getMaxAddress().add(1);
            }

            byte[] sectionBytes = rawData.toByteArray();
            int dataOffset = 20 + 40;
            int rawDataSize = alignUp(sectionBytes.length, 4);
            int symbolCount = 1 + functionNames.size();
            int symbolTableOffset = dataOffset + rawDataSize;
            int stringTableOffset = symbolTableOffset + (symbolCount * SIZEOF_SYMBOL);

            LittleEndianOutputStream out = new LittleEndianOutputStream();

            int machineType = program.getLanguage().getProcessor().toString().equals("x86") ? PE_IMAGE_FILE_MACHINE_I386 : PE_IMAGE_FILE_MACHINE_AMD64;
            out.writeShort(machineType);
            out.writeShort(1);
            out.writeInt(0);
            out.writeInt(symbolTableOffset);
            out.writeInt(symbolCount);
            out.writeShort(0);
            out.writeShort(0);

            byte[] sectionName = new byte[8];
            byte[] textName = ".text".getBytes(StandardCharsets.US_ASCII);
            System.arraycopy(textName, 0, sectionName, 0, Math.min(textName.length, 8));
            out.write(sectionName);
            out.writeInt(sectionBytes.length);
            out.writeInt(0);
            out.writeInt(rawDataSize);
            out.writeInt(dataOffset);
            out.writeInt(0);
            out.writeInt(0);
            out.writeShort(0);
            out.writeShort(0);
            out.writeInt(IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_READ | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_ALIGN_16BYTES);

            byte[] paddedSection = new byte[rawDataSize];
            System.arraycopy(sectionBytes, 0, paddedSection, 0, sectionBytes.length);
            out.write(paddedSection);

            LittleEndianOutputStream symbolTable = new LittleEndianOutputStream();

            byte[] textSymbolName = new byte[8];
            byte[] textLabel = ".text".getBytes(StandardCharsets.US_ASCII);
            System.arraycopy(textLabel, 0, textSymbolName, 0, Math.min(textLabel.length, 8));
            symbolTable.write(textSymbolName);
            symbolTable.writeInt(0);
            symbolTable.writeShort(1);
            symbolTable.writeShort(0);
            symbolTable.writeByte(IMAGE_SYM_CLASS_SECTION);
            symbolTable.writeByte(0);

            int stringOffset = 4;
            for (int i = 0; i < functionNames.size(); i++) {
                String functionName = functionNames.get(i);
                byte[] nameBytes = functionName.getBytes(StandardCharsets.US_ASCII);
                if (functionName.length() <= 8) {
                    byte[] shortName = new byte[8];
                    System.arraycopy(nameBytes, 0, shortName, 0, Math.min(nameBytes.length, 8));
                    symbolTable.write(shortName);
                    symbolTable.writeInt((int) functionOffsets.get(i).longValue());
                    symbolTable.writeShort(1);
                    symbolTable.writeShort(0x20);
                    symbolTable.writeByte(IMAGE_SYM_CLASS_EXTERNAL);
                    symbolTable.writeByte(0);
                } else {
                    symbolTable.writeInt(0);
                    symbolTable.writeInt(stringOffset);
                    symbolTable.writeInt((int) functionOffsets.get(i).longValue());
                    symbolTable.writeShort(1);
                    symbolTable.writeShort(0x20);
                    symbolTable.writeByte(IMAGE_SYM_CLASS_EXTERNAL);
                    symbolTable.writeByte(0);
                    stringOffset += nameBytes.length + 1;
                }
            }

            out.write(symbolTable.toByteArray());

            LittleEndianOutputStream stringTable = new LittleEndianOutputStream();
            int totalStringBytes = 4;
            for (String functionName : functionNames) {
                if (functionName.length() > 8) {
                    totalStringBytes += functionName.getBytes(StandardCharsets.US_ASCII).length + 1;
                }
            }
            stringTable.writeInt(totalStringBytes);
            for (String functionName : functionNames) {
                if (functionName.length() > 8) {
                    stringTable.write(functionName.getBytes(StandardCharsets.US_ASCII));
                    stringTable.write(0);
                }
            }
            out.write(stringTable.toByteArray());

            outFile.getParentFile().mkdirs();
            try (FileOutputStream fos = new FileOutputStream(outFile)) {
                fos.write(out.toByteArray());
            }
        }

        private static int alignUp(int value, int alignment) {
            return (value + alignment - 1) & ~(alignment - 1);
        }
    }

    private Object makeExporter() throws Exception {
        try {
            Class<?> exporterClass = Class.forName(EXPORTER_CLASS);
            return exporterClass.getDeclaredConstructor().newInstance();
        } catch (ClassNotFoundException e) {
            return new Ghidra12CompatibleCoffExporter();
        }
    }

    private void synthesizeRelocationsIfAvailable() throws Exception {
        try {
            Class<?> analyzerClass = Class.forName(ANALYZER_CLASS);
            Object analyzer = analyzerClass.getDeclaredConstructor().newInstance();
            Method added = analyzerClass.getMethod(
                "added",
                ghidra.program.model.listing.Program.class,
                ghidra.program.model.mem.Memory.class,
                ghidra.util.task.TaskMonitor.class,
                ghidra.app.util.importer.MessageLog.class
            );
            added.invoke(analyzer, currentProgram, currentProgram.getMemory(), monitor, new ghidra.app.util.importer.MessageLog());
        } catch (ClassNotFoundException ignored) {
            // Newer Ghidra versions no longer ship the legacy relocation synthesizer.
        }
    }

    private void exportObject(Object exporter, File outFile, AddressSet set) throws Exception {
        if (exporter instanceof Ghidra12CompatibleCoffExporter) {
            ((Ghidra12CompatibleCoffExporter) exporter).export(outFile, currentProgram, set, monitor);
            return;
        }
        Method export = exporter.getClass().getMethod(
            "export",
            File.class,
            ghidra.program.model.listing.Program.class,
            AddressSet.class,
            ghidra.util.task.TaskMonitor.class
        );
        export.invoke(exporter, outFile, currentProgram, set, monitor);
    }

    @Override
    protected void run() throws Exception {
        synthesizeRelocationsIfAvailable();
        Object exporter = makeExporter();

        String[] args = getScriptArgs();
        if (args == null || args.length == 0) {
            throw new IllegalArgumentException(
                "Usage: ExportDelinker.java [mapping.csv] <output_dir>"
            );
        }

        File outDir = new File(args[args.length - 1]);
        outDir.mkdirs();

        if (args.length == 1) {
            AddressSet set = new AddressSet();
            for (Symbol symbol : currentProgram.getSymbolTable().getSymbols("")) {
                if (symbol.getObject() instanceof Namespace) {
                    Namespace ns = (Namespace) symbol.getObject();
                    set = set.union(ns.getBody());
                }
            }

            if (set.isEmpty()) {
                for (var function : currentProgram.getFunctionManager().getFunctions(true)) {
                    set = set.union(function.getBody());
                }
            }

            if (set.isEmpty()) {
                printf("No symbols found in program, skipping export.\n");
                return;
            }

            File outFile = new File(outDir, "all_functions.obj");
            exportObject(exporter, outFile, set);
            return;
        }

        File inFile = new File(args[0]);

        String configFile = Files.readString(
            inFile.toPath(),
            StandardCharsets.UTF_8
        );
        
        List<String> lines = Arrays.asList(configFile.split("\\r?\\n"));
        List<List<String>> records = new ArrayList<>();
        for (String line : lines) {
            records.add(parseCsvLine(line));
        }

        for (List<String> record : records) {
            if (record.size() == 0 || record.get(0).trim().isEmpty()) {
                continue;
            }

            String objClass = record.get(0).trim();
            File outFile = new File(outDir, objClass + ".obj");

            AddressSet set = new AddressSet();

            for (int i = 1; i < record.size(); i++) {
                String trimmed = record.get(i).trim();
                if (trimmed.isEmpty()) {
                    continue;
                }

                List<String> ghidraClassNameParts = new ArrayList<>(Arrays.asList(trimmed.split("::")));
                String finalPart = ghidraClassNameParts.remove(ghidraClassNameParts.size() - 1);

                Namespace curNs = null;
                for (String nsPart : ghidraClassNameParts) {
                    curNs = this.getNamespace(curNs, nsPart);
                }

                Symbol sym = null;
                for (Symbol candidate : currentProgram.getSymbolTable().getSymbols(finalPart, curNs)) {
                    if (candidate.getObject() instanceof Function || candidate.getObject() instanceof Namespace) {
                        sym = candidate;
                        break;
                    }
                    if (sym == null) {
                        sym = candidate;
                    }
                }

                if (sym == null) {
                    printf("Cannot find namespace or function %s, skipping.\n", trimmed);
                    continue;
                }

                Object obj = sym.getObject();
                
                if (obj instanceof Function) {
                    Function function = (Function) obj;
                    set = set.union(function.getBody());
                } else if (obj instanceof Namespace) {
                    Namespace ns = (Namespace) obj;
                    set = set.union(ns.getBody());
                } else {
                    printf("Symbol %s is not a namespace or a function, skipping.\n", trimmed);
                    continue;
                }
            }

            if (set.isEmpty()) {
                printf("No namespaces found for %s.obj, skipping.\n", objClass);
                continue;
            }

            exportObject(exporter, outFile, set);
        }
    }
}
