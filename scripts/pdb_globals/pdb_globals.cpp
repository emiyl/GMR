#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

#include "llvm/DebugInfo/CodeView/CodeView.h"
#include "llvm/DebugInfo/CodeView/CVRecord.h"
#include "llvm/DebugInfo/PDB/Native/DbiStream.h"
#include "llvm/DebugInfo/PDB/Native/ModuleDebugStream.h"
#include "llvm/DebugInfo/PDB/Native/NativeSession.h"
#include "llvm/DebugInfo/PDB/Native/PDBFile.h"

#include "llvm/Support/Endian.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/MemoryBuffer.h"

using namespace llvm;
using namespace llvm::codeview;
using namespace llvm::pdb;

static uint16_t readU16(const uint8_t *p)
{
    return support::endian::read16le(p);
}

static uint32_t readU32(const uint8_t *p)
{
    return support::endian::read32le(p);
}

static void printDataSymbol(const CVSymbol &Symbol,
                            const char *Kind)
{
    ArrayRef<uint8_t> Data = Symbol.content();

    /*
     * DATASYM32:
     *
     *   uint32_t TypeIndex
     *   uint32_t Offset
     *   uint16_t Segment
     *   char     Name[]
     */
    if (Data.size() < 10)
        return;

    uint32_t TypeIndex =
        readU32(Data.data());

    uint32_t Offset =
        readU32(Data.data() + 4);

    uint16_t Segment =
        readU16(Data.data() + 8);

    StringRef Name(
        reinterpret_cast<const char *>(Data.data() + 10),
        Data.size() - 10);

    size_t Nul = Name.find('\0');

    if (Nul != StringRef::npos)
        Name = Name.substr(0, Nul);

    std::cout
        << "    ["
        << Kind
        << "] "
        << Name.str()
        << "  seg="
        << Segment
        << " off=0x"
        << std::hex
        << Offset
        << std::dec
        << " type=0x"
        << std::hex
        << TypeIndex
        << std::dec
        << "\n";
}

int main(int argc, char **argv)
{
    InitLLVM X(argc, argv);

    if (argc != 2)
    {
        std::cerr
            << "Usage: "
            << argv[0]
            << " <file.pdb>\n";

        return 1;
    }

    const char *PdbPath = argv[1];

    /*
     * Load PDB into memory.
     *
     * MemoryBuffer::getFile() returns ErrorOr,
     * not Expected.
     */
    auto BufferOrError =
        MemoryBuffer::getFile(PdbPath);

    if (!BufferOrError)
    {
        std::cerr
            << "error: could not open PDB: "
            << BufferOrError.getError().message()
            << "\n";

        return 1;
    }

    std::unique_ptr<MemoryBuffer> Buffer =
        std::move(*BufferOrError);

    /*
     * LLVM 22:
     *
     *   NativeSession::createFromPdb(
     *       std::unique_ptr<MemoryBuffer>,
     *       std::unique_ptr<IPDBSession> &)
     */
    std::unique_ptr<IPDBSession> BaseSession;

    Error SessionError =
        NativeSession::createFromPdb(
            std::move(Buffer),
            BaseSession);

    if (SessionError)
    {
        logAllUnhandledErrors(
            std::move(SessionError),
            errs(),
            "error: ");

        return 1;
    }

    /*
     * NativeSession isn't LLVM-castable, so use the
     * concrete pointer from the IPDBSession.
     *
     * createFromPdb() creates a NativeSession, and
     * getPDBFile() is exposed through IPDBSession's
     * native implementation.
     */
    auto *Session =
        static_cast<NativeSession *>(
            BaseSession.get());

    if (!Session)
    {
        std::cerr
            << "error: invalid PDB session\n";

        return 1;
    }

    PDBFile &Pdb =
        Session->getPDBFile();

    /*
     * Get DBI stream.
     */
    auto DbiOrError =
        Pdb.getPDBDbiStream();

    if (!DbiOrError)
    {
        logAllUnhandledErrors(
            DbiOrError.takeError(),
            errs(),
            "error: ");

        return 1;
    }

    /*
     * LLVM 22 returns Expected<DbiStream&>.
     */
    DbiStream &Dbi =
        *DbiOrError;

    const DbiModuleList &Modules =
        Dbi.modules();

    uint32_t ModuleCount =
        Modules.getModuleCount();

    std::cout
        << "PDB: "
        << PdbPath
        << "\n";

    std::cout
        << "Modules: "
        << ModuleCount
        << "\n";

    std::cout
        << "========================================\n";

    size_t TotalSymbols = 0;

    /*
     * Walk every compilation unit.
     */
    for (uint32_t Modi = 0;
         Modi < ModuleCount;
         ++Modi)
    {
        DbiModuleDescriptor Module =
            Modules.getModuleDescriptor(Modi);

        StringRef ObjName =
            Module.getObjFileName();

        StringRef ModuleName =
            Module.getModuleName();

        std::cout
            << "\nModule "
            << Modi
            << "\n";

        std::cout
            << "  Object: "
            << ObjName.str()
            << "\n";

        std::cout
            << "  Module: "
            << ModuleName.str()
            << "\n";

        /*
         * Read this module's CodeView symbol stream.
         */
        auto StreamOrError =
            Session->getModuleDebugStream(Modi);

        if (!StreamOrError)
        {
            consumeError(
                StreamOrError.takeError());

            std::cout
                << "  No readable symbol stream.\n";

            continue;
        }

        ModuleDebugStreamRef &Stream =
            *StreamOrError;

        const CVSymbolArray &Symbols =
            Stream.getSymbolArray();

        /*
         * Look specifically for file/global data.
         */
        for (const CVSymbol &Symbol : Symbols)
        {
            switch (Symbol.kind())
            {
            case SymbolKind::S_GDATA32:
                printDataSymbol(
                    Symbol,
                    "GDATA");

                ++TotalSymbols;
                break;

            case SymbolKind::S_LDATA32:
                printDataSymbol(
                    Symbol,
                    "LDATA");

                ++TotalSymbols;
                break;

            case SymbolKind::S_GTHREAD32:
                printDataSymbol(
                    Symbol,
                    "GTHREAD");

                ++TotalSymbols;
                break;

            case SymbolKind::S_LTHREAD32:
                printDataSymbol(
                    Symbol,
                    "LTHREAD");

                ++TotalSymbols;
                break;

            default:
                break;
            }
        }
    }

    std::cout
        << "\n========================================\n";

    std::cout
        << "Total data symbols: "
        << TotalSymbols
        << "\n";

    return 0;
}