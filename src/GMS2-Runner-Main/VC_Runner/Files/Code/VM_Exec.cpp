// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Code\VM_Exec.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\VM_Exec.obj
// 154 function symbol(s) attributed to this object.

#include <stdint.h>

void Buffer_Standard::Buffer_Standard(/* type 0x603 */, int32_t, /* type 0x8229 (LF_ENUM) */, int32_t, bool);
void TErrStreamConsole::TErrStreamConsole(void);
void YYGMLException::YYGMLException(void *);
void YYGMLException::YYGMLException(void *, void *, void *, void *, void *, int32_t, void *, int32_t);
void AddGCRefObj(void *, bool, void *, bool);
/* type 0x603 */ CBucket<32768,1048576,0>::Alloc(bool);
void CBucket<32768,1048576,0>::Check(void);
uint8_t* CheckForStackResize(uint8_t*, void *, int32_t);
void VM::ClearBreakpointsFromMemory(void);
bool ConvertStringToBool(char *param_1,bool param_2,bool *param_3);

uint8_t* DoAdd(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoAnd(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoBranch(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoBranchFalse(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoBranchTrue(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoBreakDoBreak(uint8_t param_1, uint8_t param_2, uint8_t *param_3, uint8_t *param_4, VMExec *param_5, bool param_6);
uint8_t* DoCall(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoCallGML(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoCallLibrary(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoCallScript(void *, int32_t, uint8_t*, void *, void *, void *);
uint8_t* DoConv(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoConvIntToVariable(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoDiv(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoDup(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoExit(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);

void DoFullGC(void);
void DoGenerationalGC(int32_t);

uint8_t* DoMod(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoMul(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoNeg(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoNot(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoOr(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoPop(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoPopEnv(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoPopLocalVariable(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoPopNull(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoPush(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoPushBuiltin(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoPushEnv(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoPushGlobal(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoPushImmediate(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoPushLocal(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoRem(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoRet(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoSet(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoShl(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoShr(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoSub(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);
uint8_t* DoXor(uint32_t param_1, uint8_t *param_2, uint8_t *param_3, VMExec *param_4);

void VM::Exec(void *, void *, void *, void *, void *, int32_t, void *, int32_t, void *);
void VM::ExecDebug(void *, void *, bool);
void VM::ExecRelease(void *, void *);
void F_VMGetCallStack(void *, void *, void *, int32_t, void *);
bool CBucket<32768,1048576,0>::Free(void *);
void FreeAllObjects(void);
/* type 0x603 */ GCThreadFunc(void *);
void VM::GetAllInstanceIDs(void *, bool);
void VM::GetDSMap(void *, int32_t, int32_t);
void * YYGMLException::GetExceptionObject(void);
void VM::GetGlobalVariables(void *, bool);
void VM::GetInstanceVariables(void *, void *, bool);
void VM::GetLocalVariables(void *, void *, bool, int32_t);
void VM::GetObjectBaseVariables(void *, void *, bool);
void VM::GetRuntimeState(void *, int32_t);
int32_t CBucket<32768,1048576,0>::GetSize(void);
void VM::GetStructureCounts(void *);
void HandleInstance(void *);
bool HasGMLExceptionHandler(void);
void CHashMap<int,CInstance *,3>::Init(void);
void CHashMap<int,CInstance *,3>::Insert(int32_t, void *);
bool InstanceHandled(void *);
void MarkAndSweepGen(int32_t, int32_t, bool);
void TErrStreamConsole::Output(void *, /* type 0x0 */);
uint8_t* PerformReturn(uint8_t*, void *);
bool VM::PokeDSList(int32_t, int32_t, void *);
bool VM::PokeDSMap(int32_t, int32_t, void *);
bool VM::PokeDSPriority(int32_t, int32_t, void *);
bool VM::PokeDSQueue(int32_t, int32_t, void *);
bool VM::PokeDSStack(int32_t, int32_t, void *);
void ProcessObjectDisposeList(void);
void PushContextStack(void *);
bool RValue_IsCallable(void *);
void ResetGC(void);
void ResetObjectGCList(void);
void VMError(void *, void *, /* type 0x0 */);
void VM::WriteBreakpointsToMemory(void);
void VM::WriteCallStack(void *, void *, bool);
int32_t VM::WriteDSSizeCount(void *, int32_t, void *);
void VM::WriteInstanceBuiltInVariables(void *, void *);
void VM::WriteRValueToBuffer(void *, void *);
void * YYAllocLocalStackNew(int32_t);
void YYCatchGMLException(void *);
void YYCreateString(void *, void *);
void YYCreateString(void *, void *);
void YYError(void *, /* type 0x0 */);
void * YYGML_CallMethod(void *, void *, void *, int32_t, void *, void *);
void * YYGML_GetStaticObject(int32_t);
void YYSetScriptRef(void *);
void YYSetString(void *, void *);
void * YYStrDup(void *);
void YYWarning(void *, /* type 0x0 */);
void YYprintf(void *, /* type 0x0 */);
bool tryParseBool(void *, void *);
bool tryParseDouble(void *, void *);
bool tryParseInt32(void *, void *);
bool tryParseInt64(void *, void *);
void * vmGetCallStack(void);
