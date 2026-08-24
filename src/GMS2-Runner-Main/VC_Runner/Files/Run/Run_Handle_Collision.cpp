// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Run\Run_Handle_Collision.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\Run_Handle_Collision.obj
// 21 function symbol(s) attributed to this object.

void RTree<CInstance *,float,float,6,2>::RTree<CInstance *,float,float,6,2>(int32_t);
void CPool<RTree<CInstance *,float,float,6,2>::Node>::~CPool<RTree<CInstance *,float,float,6,2>::Node>(void);
void CleanCollisions(void);
void CollisionMarkDirty(void *);
void CollisionMarkTest(void *);
void CollisionRemove(void *);
void CollisionUpdate(void *, void *);
void * GetCollisionTreeForDomain(/* type 0x689c (LF_ENUM) */);
void HandleCollision(void);
void RebuildTree(bool);
bool RTree<CInstance *,float,float,6,2>::RemoveRect(void *, void *, void *);
bool RTree<CInstance *,float,float,6,2>::RemoveRectRec(void *, void *, void *, void *);
void UpdateTree(void);
bool collisionResult(void *, /* type 0x603 */);
void processCollision(void *);
