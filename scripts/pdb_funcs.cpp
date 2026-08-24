#include <llvm/DebugInfo/PDB/Native/NativeSession.h>
#include <llvm/DebugInfo/PDB/Native/NativeSessionBuilder.h>
#include <llvm/DebugInfo/PDB/PDB.h>
#include <llvm/DebugInfo/PDB/PDBSymbol.h>
#include <llvm/DebugInfo/PDB/PDBSymbolExe.h>
#include <llvm/DebugInfo/PDB/PDBSymbolFunc.h>
#include <llvm/DebugInfo/PDB/PDBSymbolTypeFunctionSig.h>
#include <llvm/DebugInfo/PDB/PDBSymbolType.h>

#include <iostream>
#include <memory>

using namespace llvm;
using namespace llvm::pdb;

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " Runner.pdb\n";
        return 1;
    }

    BumpPtrAllocator Allocator;

    auto Session = NativeSession::createFromPdb(
        argv[1],
        std::make_shared<BumpPtrAllocator>(Allocator)
    );

    if (!Session) {
        std::cerr << "Failed to open PDB\n";
        return 1;
    }

    auto Global = Session->getGlobalScope();

    if (!Global) {
        std::cerr << "Failed to get global scope\n";
        return 1;
    }

    auto Functions = Global->findAllChildren<PDBSymbolFunc>();

    while (auto Function = Functions->getNext()) {
        std::cout << Function->getName() << "\n";

        auto Type = Function->getType();

        if (Type)
            std::cout << "  type: " << Type->getName() << "\n";
    }

    return 0;
}