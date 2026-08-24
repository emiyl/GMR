// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Platform\MemoryManager.cpp
// Compiled into : x64\Release-Zeus\MemoryManager.obj
// 62 function symbol(s) attributed to this object.

void MM_RA_AutoMutex::MM_RA_AutoMutex(void *, bool);
void MM_RA_AutoMutex::~MM_RA_AutoMutex(void);
/* type 0x603 */ operator new(/* type 0x23 */);
void operator delete(/* type 0x603 */, /* type 0x23 */);
/* type 0x603 */ operator new[](/* type 0x23 */);
void operator delete[](/* type 0x603 */);
void operator delete[](/* type 0x603 */, /* type 0x23 */);
/* type 0x603 */ MemoryManager::Alloc(/* type 0x23 */, void *, int32_t, bool);
void CBucket<8,131072,1>::Check(void);
void CBucket<16,262144,1>::Check(void);
void CBucket<256,1048576,1>::Check(void);
void CBucket<32,262144,1>::Check(void);
void CBucket<512,2097152,1>::Check(void);
void CBucket<64,524288,1>::Check(void);
void CBucket<16384,262144,1>::Check(void);
void CBucket<128,524288,1>::Check(void);
void MemoryManager::DumpMemory(/* type 0x603 */, /* type 0x603 */, bool);
bool CBucket<8,131072,1>::Free(void *);
bool CBucket<16,262144,1>::Free(void *);
bool CBucket<256,1048576,1>::Free(void *);
bool CBucket<32,262144,1>::Free(void *);
bool CBucket<512,2097152,1>::Free(void *);
bool CBucket<64,524288,1>::Free(void *);
bool CBucket<16384,262144,1>::Free(void *);
bool CBucket<128,524288,1>::Free(void *);
void MemoryManager::Free(void *, bool);
int32_t CBucket<8,131072,1>::GetSize(void);
int32_t CBucket<16,262144,1>::GetSize(void);
int32_t CBucket<256,1048576,1>::GetSize(void);
int32_t CBucket<32,262144,1>::GetSize(void);
int32_t CBucket<512,2097152,1>::GetSize(void);
int32_t CBucket<64,524288,1>::GetSize(void);
int32_t CBucket<16384,262144,1>::GetSize(void);
int32_t CBucket<128,524288,1>::GetSize(void);
/* type 0x603 */ MemoryManager::ReAlloc(/* type 0x603 */, /* type 0x23 */, void *, int32_t, bool);
/* type 0x603 */ MemoryManager::_Alloc(/* type 0x23 */, void *, int32_t, bool);
void addPageToGlobalPageList(/* type 0x603 */, /* type 0x603 */);
/* type 0x603 */ bucketAlloc(/* type 0x23 */, bool);
void * globalPageListFindAddr(void *);
/* type 0x603 */ yy_calloc(/* type 0x23 */, /* type 0x23 */);
/* type 0x603 */ yy_malloc(/* type 0x23 */);
/* type 0x670 */ yy_strdup(void *);
