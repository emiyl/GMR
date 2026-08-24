// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\libjpeg\jmemmgr.c
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\jmemmgr.obj
// 12 function symbol(s) attributed to this object.

void * access_virt_barray(void *, void *, uint32_t, uint32_t, unsigned char);
void * access_virt_sarray(void *, void *, uint32_t, uint32_t, unsigned char);
void * alloc_barray(void *, int32_t, uint32_t, uint32_t);
/* type 0x603 */ alloc_large(void *, int32_t, /* type 0x23 */);
void * alloc_sarray(void *, int32_t, uint32_t, uint32_t);
/* type 0x603 */ alloc_small(void *, int32_t, /* type 0x23 */);
void free_pool(void *, int32_t);
void jinit_memory_mgr(void *);
void realize_virt_arrays(void *);
void * request_virt_barray(void *, int32_t, unsigned char, uint32_t, uint32_t, uint32_t);
void * request_virt_sarray(void *, int32_t, unsigned char, uint32_t, uint32_t, uint32_t);
void self_destruct(void *);
