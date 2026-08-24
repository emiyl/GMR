// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Run\Run_Command.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\Run_Command.obj
// 53 function symbol(s) attributed to this object.

void CPool<RTree<CInstance *,float,float,6,2>::Node>::AllocBatch(void);
void * RTree<CInstance *,float,float,6,2>::AllocNode(void);
void RTree<CInstance *,float,float,6,2>::ChoosePartition(void *, int32_t);
void Command_Bounce(void *, bool, bool);
void Command_Change(void *, int32_t, bool);
void * Command_CollisionEllipse(void *, float, float, float, float, int32_t, bool, bool, void *);
void * Command_CollisionLine(void *, float, float, float, float, /* type 0x689c (LF_ENUM) */, int32_t, bool, bool, void *);
void * Command_CollisionPoint(void *, float, float, int32_t, bool, bool, void *);
void * Command_CollisionRectangle(void *, float, float, float, float, /* type 0x689c (LF_ENUM) */, int32_t, bool, bool, void *);
void * Command_Create_Depth(int32_t, float, float, int32_t, void *, void *);
void * Command_Create_Layer(int32_t, float, float, int32_t, void *, void *);
void Command_Destroy(void *);
void Command_EndGame(void);
void Command_GotoRoom(int32_t, int32_t);
int32_t Command_InstanceNumber(int32_t);
void * Command_InstancePlace(void *, float, float, int32_t, void *);
void * Command_InstancePosition(float, float, /* type 0x689c (LF_ENUM) */, int32_t, void *);
bool Command_IsEmpty(void *, float, float, int32_t);
bool Command_IsFree(void *, float, float);
void Command_NextRoom(int32_t);
void Command_PreviousRoom(int32_t);
void Command_Snap(void *, float, float);
int32_t Command_Unzip(void *, void *, int32_t, int32_t, /* type 0x670 */);
int32_t Command_Unzip_Async(void *, void *);
bool RTree<CInstance *,float,float,6,2>::InsertRect(void *, void *, int32_t);
bool RTree<CInstance *,float,float,6,2>::InsertRectRec(void *, void *, void *, int32_t);
/* struct 0xecfd */ RTree<CInstance *,float,float,6,2>::NodeCover(void *);
bool RTree<CInstance *,float,float,6,2>::Overlap(void *, void *);
int32_t RTree<CInstance *,float,float,6,2>::PickBranch(void *, void *);
void RTree<CInstance *,float,float,6,2>::PickSeeds(void *);
bool RTree<CInstance *,float,float,6,2>::Search(void *, void *, void *, void *, /* type 0x603 */);
int32_t RTree<CInstance *,float,float,6,2>::Search(void *, void *, void *, /* type 0x603 */);
bool RTree<CInstance *,float,float,6,2>::SearchLine(void *, void *, void *, void *, /* type 0x603 */);
void ShallowCopyVars(void *, void *);
int32_t ShouldUseFastCollision(int32_t, void *);
void RTree<CInstance *,float,float,6,2>::SplitNode(void *, void *, void *);
int32_t UnzipAsyncBuffLoadCallback(void *, /* type 0x603 */, /* type 0x674 */);
int32_t UnzipAsyncBuffSaveCallback(void *, /* type 0x603 */, /* type 0x674 */);
void UnzipDecompressJob(/* type 0x13 */);
void UnzipSaveFilesJob(/* type 0x13 */);
bool collisionResultCollisionLine(void *, /* type 0x603 */);
bool collisionResultCollisionRect(void *, /* type 0x603 */);
bool collisionResultInstancePlace(void *, /* type 0x603 */);
bool collisionResultIsEmpty(void *, /* type 0x603 */);
bool collisionResultIsFree(void *, /* type 0x603 */);
