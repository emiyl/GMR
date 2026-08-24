// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Shader\EffectsManager.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\EffectsManager.obj
// 49 function symbol(s) attributed to this object.

void FilterHost::FilterHost(void *, void *);
void EffectInfo::~EffectInfo(void);
void EffectParameterInfo::~EffectParameterInfo(void);
void EffectsManager::~EffectsManager(void);
int32_t EffectsManager::AcquireTempSurface(int32_t, int32_t);
void EffectsManager::Clean(void);
void * EffectsManager::CreateNewEffectInstance(void *, bool);
void EffectsInfoDeleter(void *, void *);
void EffectsManager::ExecuteEffectEventsForRoom(void *, void *, bool);
void F_Effect_dispose(void *, void *, void *, int32_t, void *);
void F_FilterHost_cleanup(void *, void *, void *, int32_t, void *);
void F_FilterHost_dispose(void *, void *, void *, int32_t, void *);
void F_FilterHost_layer_begin(void *, void *, void *, int32_t, void *);
void F_FilterHost_layer_end(void *, void *, void *, int32_t, void *);
void F_FilterHost_room_end(void *, void *, void *, int32_t, void *);
void F_FilterHost_room_start(void *, void *, void *, int32_t, void *);
void F_FilterHost_step(void *, void *, void *, int32_t, void *);
void EffectInstance::Free(bool);
void FilterHost::Free(bool);
void FilterHost::GetCustomShaderConstants(void);
void * EffectsManager::GetEffectInfo(void *);
void * EffectInstance::GetParamVar(void *);
void CHashMap<char const *,EffectInfo *,3>::Init(void);
void EffectsManager::Init(void);
void CHashMap<char const *,EffectInfo *,3>::Insert(void *, void *);
void FilterHost::LayerBegin(int32_t);
void FilterHost::LayerEnd(int32_t);
bool EffectInstance::Mark4GC(/* type 0x675 */, int32_t);
void EffectInstance::PreFree(void);
void EffectsManager::ReleaseTempSurface(int32_t);
void EffectInstance::SetDefaultValues(void);
void EffectInstance::SetParam(void *, int32_t, int32_t, /* type 0x603 */);
bool EffectInstance::SetParamVar(void *, void *);
void EffectsManager::SetupEffectInfo(void);
void EffectInfo::SetupFromJson(void *);
void EffectsManager::SetupLayerEffect(void *, void *);
void EffectsManager::StepEffectsForRoom(void *);
void EffectInstance::ThreadFree(bool, void *);
void FilterHost::ThreadFree(bool, void *);
