// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Debug\Debug_NetworkInterface.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\Debug_NetworkInterface.obj
// 38 function symbol(s) attributed to this object.

void VMBuffer::~VMBuffer(void);
void DebugUpdateSelectedInstance(void);
void Debug_AddTag(void, void *, char *);
/* struct 0x6ed5 */ Debug_ExecuteBreakCondition(void *);
void Debug_FreeTags(void);
void Debug_GetBuffers(void *, void *);
void Debug_GetData(/* type 0x68a8 (LF_ENUM) */, void *, uint8_t*, int32_t);
void Debug_GetPing(void *, void *);
void Debug_GetSelectedInstance(void *);
void Debug_GetStructures(void *, void *);
void Debug_GetTextures(void *, void *);
void Debug_GetWatches(void *, void *);
void Debug_PokeStructure(void *, void *);
void Debug_QueryHeapMem(void *, void *, void *);
void Debug_ReadCommand(/* type 0x68a8 (LF_ENUM) */, void *, void *);
void Debug_SetBreakpoints(uint8_t*, int32_t);
void Debug_StartStopTarget(bool);
void Debug_WriteOutput(void *);
void Debug_WriteSurfaceIds(void *, bool);
bool DebuggerIsConnected(void);
int32_t DebuggerMessageLoop(void);
void DebuggerRunBackgroundMessageLoop(void);
void ExecuteDebugScript(char*, void *, void *);
void ProcessDebugPacket(void *, void *, int32_t);
void TickDebugger(void);
/* type 0x603 */ thread_tick_func(/* type 0x603 */);
