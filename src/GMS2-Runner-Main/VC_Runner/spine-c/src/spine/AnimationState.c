// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\spine-c\src\spine\AnimationState.c
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\AnimationState.obj
// 24 function symbol(s) attributed to this object.

int32_t _spAnimationState_addPropertyIDs(void *, /* type 0x623 */, int32_t);
void _spAnimationState_animationsChanged(void *);
void _spAnimationState_applyAttachmentTimeline(void *, void *, void *, float, /* type 0x99f3 (LF_ENUM) */, int32_t);
float _spAnimationState_applyMixingFrom(void *, void *, void *, /* type 0x99f3 (LF_ENUM) */);
void _spAnimationState_applyRotateTimeline(void *, void *, void *, float, float, /* type 0x99f3 (LF_ENUM) */, /* type 0x640 */, int32_t, int32_t);
void _spAnimationState_disposeTrackEntry(void *);
void * _spAnimationState_expandToIndex(void *, int32_t);
void _spAnimationState_queueEvents(void *, void *, float);
/* type 0x640 */ _spAnimationState_resizeTimelinesRotation(void *, int32_t);
void _spAnimationState_setAttachment(void *, void *, void *, void *, int32_t);
void _spAnimationState_setCurrent(void *, int32_t, void *, int32_t);
void * _spAnimationState_trackEntry(void *, int32_t, void *, int32_t, void *);
int32_t _spAnimationState_updateMixingFrom(void *, void *, float);
void _spEventQueue_drain(void *);
void _spEventQueue_end(void *, void *);
void _spEventQueue_ensureCapacity(void *, int32_t);
void _spEventQueue_event(void *, void *, void *);
int32_t spAnimationState_apply(void *, void *);
void spAnimationState_clearNext(void *, void *);
void spAnimationState_clearTrack(void *, int32_t);
void * spAnimationState_create(void *);
void * spAnimationState_setAnimation(void *, int32_t, void *, int32_t);
void spAnimationState_update(void *, float);
float spTrackEntry_getAnimationTime(void *);
