// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Physics\PhysicsWorld_Class.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\PhysicsWorld_Class.obj
// 39 function symbol(s) attributed to this object.

void CPhysicsWorld::CPhysicsWorld(float, int32_t);
void ContactsStack::ContactsStack(void);
void CPhysicsWorld::~CPhysicsWorld(void);
void ContactsStack::~ContactsStack(void);
void ApplyOffsetToFixture(void *, void *);
void b2ContactListener::BeginContact(void *);
int32_t CPhysicsWorld::BuildCollisionBits(int32_t);
int32_t CPhysicsWorld::CreateBody(void *, void *, float, float, bool);
int32_t CPhysicsWorld::CreatePulleyJoint(void *, void *, float, float, float, float, float, float, float, float, float, bool);
void CPhysicsWorld::DeleteParticleGroup(int32_t);
void CPhysicsWorld::DeleteParticlePolyRegion(/* type 0x640 */, int32_t);
void CPhysicsWorld::DrawParticles(uint32_t, int32_t, void *, int32_t);
void CPhysicsWorld::DrawParticlesExt(uint32_t, int32_t, void *, int32_t, float, float, float, uint32_t, float);
void b2ContactListener::EndContact(void *);
bool CPhysicsWorld::GetCurrentContactNormal(void *, int32_t, void *, void *);
bool CPhysicsWorld::GetCurrentContactPosition(void *, int32_t, void *, void *);
int32_t CPhysicsWorld::GetFreeParticleGroupSlot(void);
void CPhysicsWorld::GetParticleData(void *, uint32_t, int32_t, int32_t);
void CPhysicsWorld::Init(void);
void b2ContactListener::PostSolve(void *, void *);
void b2ContactListener::PreSolve(void *, void *);
void CPhysicsWorld::SetGravity(float, float);
bool CPhysicsWorld::TestOverlap(void *, void *, float, float, float);
void CPhysicsWorld::Update(int32_t, bool);
void CPhysicsWorld::UpdateInstantiatedShapesCollisionBits(void);
void _b2relassert(bool, void *);
void yoyo_b2relassert(bool, void *);
