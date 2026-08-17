#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <locale.h>
#include <string>
#include <windows.h>

#include "GameMaker.h"
#include "MemoryManager.h"
#include "Graphics_Perf.h"
#include "RomDisk.h"
#include "globals.h"
#include "custom/logging.h"
#include "../box2d/include/box2d/b2_body.h"

// Not checked
inline int QueryPerformanceFrequency(int64_t* value)
{
    if (value == nullptr)
        return 0;
    *value = 1000000LL;
    return 1;
}

// Not checked
inline int QueryPerformanceCounter(int64_t* value)
{
    if (value == nullptr)
        return 0;
    const auto now = std::chrono::steady_clock::now().time_since_epoch();
    *value = std::chrono::duration_cast<std::chrono::microseconds>(now).count();
    return 1;
}

// Not checked
inline uint64_t GetTickCount64()
{
    const auto now = std::chrono::steady_clock::now().time_since_epoch();
    return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now).count());
}

// Not checked
inline int64_t Timing_Time()
{
    const auto now = std::chrono::steady_clock::now().time_since_epoch();
    return static_cast<int64_t>(std::chrono::duration_cast<std::chrono::microseconds>(now).count());
}

inline void InitFastCRC() {}
inline void INITIALIZE_PlatformSpecific() {}
inline void MakeTempDir() {}
inline void GR_Draw_Circle_Precision(int) {}
inline void ProcessMessages() {}
inline void ParticleType_DestroyAll() {}
inline void ParticleSystem_DestroyAll() {}
inline void INITIALIZE_Run_Global() {}
inline void INITIALIZE_Time_Main() {}
inline void InitLocalVariables() {}
inline void InitGlobalVariables() {}
inline void HighScore_Clear() {}

struct RView
{
    bool def;
    float worldx;
    float worldy;
    float worldw;
    float worldh;
    float portx;
    float porty;
    float portw;
    float porth;
    float worldangle;
    int SurfaceID;
    int cameraID;
};

struct RIntPoint
{
    float x;
    float y;
    float speed;
    float l;	
};

struct DynamicArrayOfRIntPoint
{
    int length;
    int* arr;
};

struct RWayPoint
{
    float x;
    float y;
    float speed;
};

struct DynamicArrayOfRWayPoint
{
    int length;
    RWayPoint* arr;
};

struct CPath
{
    DynamicArrayOfRWayPoint points;
    DynamicArrayOfRIntPoint intpoints;
    int count;
    int kind;
    int closed;
    int precision;
    int intcount;
    int length;
};

struct DynamicArrayOfCPath
{
    int length;
    CPath** arr;
};


template<typename K, typename V, int N>
class CHashMap
{
public:
    int m_curSize;           // 0x00
    int m_numUsed;           // 0x04
    int m_curMask;           // 0x08
    int m_growThreshold;     // 0x0C
    void* m_elements;        // 0x10
    void (*m_deleter)(K*, V*); // 0x18
    int m_maxInsertSteps;    // 0x20
    int m_stepLoadThreshold; // 0x24

    static void Init(CHashMap<K, V, N>* map)
    {
        if (map == nullptr)
            return;

        map->m_curSize = N;
        map->m_numUsed = 0;
        map->m_curMask = N - 1;
        map->m_growThreshold = static_cast<int>(N * 0.75f);
        map->m_elements = nullptr;
        map->m_deleter = nullptr;
        map->m_maxInsertSteps = 8;
        map->m_stepLoadThreshold = 4;
    }
};

enum class eGML_TYPE : uint32_t {
    eGMLT_NONE = 0,
    eGMLT_DOUBLE = 1,
    eGMLT_STRING = 2,
    eGMLT_INT32 = 4,
    eGMLT_ERROR = 0xffff0000
};

template <typename T>
struct RefThing
{
    T m_thing;
    int m_refCount;
    int m_size;
};

struct RValue;
struct RefDynamicArrayOfRValue;

struct Element {
    RValue* v;
    int32_t k;
    uint32_t h;
};

struct StructVarsMap {
    int32_t m_curSize;
    int32_t m_numUsed;
    int32_t m_curMask;
    int32_t m_growThreshold;
    Element* m_elements;
};

enum EJSRetValBool : uint32_t {
    EJSRVB_FALSE = 0,
    EJSRVB_TRUE = 1,
    EJSRVB_TYPE_ERROR = 2
};

struct YYObjectBase;

struct CWeakRef {
    YYObjectBase* pWeakRef;
};

struct YYObjectBase {
    StructVarsMap* m_yyvarsMap;
    YYObjectBase* m_pNextObject;
    YYObjectBase* m_pPrevObject;
    YYObjectBase* m_prototype;
    char* m_class;
    void (*m_getOwnProperty)(YYObjectBase*, RValue*, char*);
    void (*m_deleteProperty)(YYObjectBase*, RValue*, char*, bool);
    EJSRetValBool (*m_defineOwnProperty)(YYObjectBase*, char*, RValue*, bool);
    CWeakRef** m_pWeakRefs;
    uint32_t m_numWeakRefs;
    uint32_t m_nvars;
    uint32_t m_flags;
    uint32_t m_capacity;
    uint32_t m_visited;
    uint32_t m_visitedGC;
    int32_t m_GCgen;
    int32_t m_GCcreationframe;
    int32_t m_slot;
    int32_t kind;
    int32_t m_rvalueInitType;
    int32_t m_curSlot;
};

struct vec4 {
    float x;
    float y;
    float z;
    float w;
};

struct matrix44 {
    vec4 m[4];
};

struct RefDynamicArrayOfRValue {
    YYObjectBase* pObjThing;
    RValue* pArray;
    int64_t owner;
    int32_t refcount;
    int32_t flags;
    int32_t visited;
    int32_t len;
    int32_t capacity;
};

struct RValue {
    union {
        int32_t v32;
        int64_t v64;
        double val;
        RefThing<const char *>* pRefString;
        RefDynamicArrayOfRValue* pRefArray;
        vec4* pVec4;
        matrix44* pMatrix44;
        void* ptr;
        YYObjectBase* pObj;
    };
    uint32_t flags;
    uint32_t kind;
};

struct RToken {
    int32_t kind;
    eGML_TYPE type;
    int32_t ind;
    int32_t ind2;
    RValue value;
    int32_t itemnumb;
    RToken* items;
    int32_t position;
};

struct VMBuffer {
    int32_t m_size;
    int32_t m_numLocalVarsUsed;
    int32_t m_numArguments;
    unsigned char* m_pBuffer;
    void** m_pConvertedBuffer;
    int32_t m_pJumpBuffer;
};

struct YYVAR {
    char* pName;
    int32_t val;
};

struct CInstance;

struct YYGMLFuncs {
    char* pName;
    void (*pFunc)(CInstance*, CInstance*);
    YYVAR* pFuncVar;
};

struct CCode {
    CCode* m_pNext;
    int32_t i_kind;
    bool i_compiled;
    char* i_str;
    RToken i_token;
    RValue i_value;
    VMBuffer* i_pVM;
    VMBuffer* i_pVMDebugInfo;
    char* i_pCode;
    char* i_pName;
    int32_t i_CodeIndex;
    YYGMLFuncs* i_pFunc;
    bool i_watch;
    int32_t i_offset;
    int32_t i_locals;
    int32_t i_args;
    int32_t i_flags;
    YYObjectBase* i_pPrototype;
};

struct CEvent {
    CCode* e_code;
    int32_t m_OwnerObjectID;
};

struct CPhysicsDataGM {
    float* m_physicsVertices;
    bool m_physicsObject;
    bool m_physicsSensor;
    bool m_physicsAwake;
    bool m_physicsKinematic;
    int32_t m_physicsShape;
    int32_t m_physicsGroup;
    float m_physicsDensity;
    float m_physicsRestitution;
    float m_physicsLinearDamping;
    float m_physicsAngularDamping;
    float m_physicsFriction;
    int32_t m_physicsVertexCount;
};

struct STouchRecord {
    int64_t m_time;
    int32_t m_posX;
    int32_t m_posY;
    float m_inchPosX;
    float m_inchPosY;
    float m_inchVelX;
    float m_inchVelY;
};

struct CTouchAction {
    int32_t m_touchID;
    int32_t m_touchUID;
    STouchRecord m_startRec;
    STouchRecord m_recs[64];
    int32_t m_recHead;
    int32_t m_recTail;
    bool m_released;
    int64_t m_releaseTime;
};

struct SLinkedListNode {
    SLinkedListNode* m_pNext; // 0x00
    SLinkedListNode* m_pPrev; // 0x08
    CTouchAction* m_pObj;     // 0x10
};

template <typename T>
struct SLinkedList {
    SLinkedListNode* m_pFirst;
    SLinkedListNode* m_pLast;
    int m_Count;
};

struct CObjectGM {
    char* m_pName;
    CObjectGM* m_pParent;
    CHashMap<int, CObjectGM*, 2>* m_childrenMap;
    CHashMap<uint64_t, CEvent*, 3>* m_eventsMap;
    CPhysicsDataGM m_physicsData;
    SLinkedList<CInstance> m_Instances;
    SLinkedList<CInstance> m_Instances_Recursive;
    uint32_t m_Flags;
    int32_t m_spriteindex;
    int32_t m_depth;
    int32_t m_parent;
    int32_t m_mask;
    int32_t m_ID;
};

template<typename T>
struct HashNode {
    HashNode<T>* m_pPrev;
    HashNode<T>* m_pNext;
    uint32_t     m_ID;
    T*           m_pObj;
};

template<typename T>
struct HashLink {
    HashNode<T>* m_pFirst;
    HashNode<T>* m_pLast;
};

template<typename T>
struct Hash {
    HashLink<T>* m_pHashingTable;
    int32_t      m_HashingMask;
    int32_t      m_Count;
};

struct CPhysicsObject {
    b2Body *m_pBody;
    b2Vec2 m_visualOffset;
    b2Vec2 m_previousPosition;
    int32_t m_collisionCategory;
    uint32_t m_nextFixtureIndex;
    // Hash<CPhysicsObject::b2FixtureContainer> *m_pFixtureMap;
};

// We don't have the library for this
struct spAttachment;
struct spAtlas;
struct spSkeleton;
struct spSkeletonBounds;
struct spAnimation;
struct spAnimationState;
struct spAnimationStateData;
struct spSkeletonData;
struct spSkin;

struct CSkeletonSkin {
    spSkin* m_skin;
    bool m_owned;
    int32_t m_globalRefCount;
};

struct CSkeletonInstance {
    float   m_lastFrame;
    int32_t m_lastFrameDir;
    float   m_lastEventFrame;
    bool    m_drawCollisionData;
    bool    m_forceUpdate;
    float   m_angle;
    int     m_attachmentCount;

    spAttachment**        m_ppAttachments;
    spAtlas**              m_ppAttachmentAtlases;
    spSkeleton*            m_skeleton;
    spSkeletonBounds*      m_originalSkeletonBounds;
    spSkeletonBounds*      m_rotatedSkeletonBounds;
    spAnimation*           m_animation;
    spAnimationState*      m_animationState;
    spAnimationStateData*  m_animationStateData;
    spSkeletonData*        m_skeletonData;

    CSkeletonSkin*         m_runtimeSkin;
};

struct CSequenceBaseTrack;
struct CSequence;

struct yyMatrix_u_0 {
    union {
        float m[16];

        struct {
            float _11;
            float _12;
            float _13;
            float _14;
            float _21;
            float _22;
            float _23;
            float _24;
            float _31;
            float _32;
            float _33;
            float _34;
            float _41;
            float _42;
            float _43;
            float _44;
        } _s_1;

        struct {
            uint32_t _d11;
            uint32_t _d12;
            uint32_t _d13;
            uint32_t _d14;
            uint32_t _d21;
            uint32_t _d22;
            uint32_t _d23;
            uint32_t _d24;
            uint32_t _d31;
            uint32_t _d32;
            uint32_t _d33;
            uint32_t _d34;
            uint32_t _d41;
            uint32_t _d42;
            uint32_t _d43;
            uint32_t _d44;
        } _s_2;
    };
};

using yyMatrix = yyMatrix_u_0;
struct FontEffectParams {
    bool enabled;
    float thicknessMod;
    uint32_t coreCol;
    float coreAlpha;
    bool glowEnabled;
    float glowStart;
    float glowEnd;
    uint32_t glowCol;
    float glowAlpha;
    bool outlineEnabled;
    float outlineDist;
    uint32_t outlineCol;
    float outlineAlpha;
    bool dropShadowEnabled;
    float shadowWidth;
    float shadowOffsetX;
    float shadowOffsetY;
    uint32_t shadowCol;
    float shadowAlpha;
};

struct TrackEval {
    yyMatrix matrix;
    float matrixHeadPosition;
    char overridden;
    uint64_t hascreationvalue;
    uint64_t paramset;
    float X;
    float Y;
    float Rotation;
    float ScaleX;
    float ScaleY;
    float colorMultiply[4];
    float colorAdd[4];
    float XOrigin;
    float YOrigin;
    float Gain;
    float Pitch;
    float FalloffRef;
    float FalloffMax;
    float FalloffFactor;
    float ImageIndex;
    float ImageSpeed;
    float ImageDistance;
    FontEffectParams* pFontEffectParams;
    union {
        int32_t spriteIndex;
        int32_t instanceID;
        int32_t particleSystemID;
        struct {
            int32_t emitterIndex;
            int32_t soundIndex;
        };
        struct {
            CSequence* pSequence;
            int32_t sequenceID;
        };
        struct {
            float FrameSizeX;
            float FrameSizeY;
            float CharacterSpacing;
            float LineSpacing;
            float ParagraphSpacing;
        };
    };
};

struct TrackEvalNode {
    CSequenceBaseTrack* track;
    TrackEval value;
    TrackEvalNode* next;
    TrackEvalNode* parent;
    TrackEvalNode* subtree;
};

struct CSeqStackSnapshot {
    int32_t stackSize;
    YYObjectBase** pStack;
};

struct CSeqTrackAudioInfo {
    int32_t soundindex;
    int32_t playdir;
    int32_t emitterindex;
};

struct CTrackKeyBase {
    int32_t channel;
};

struct CSeqTrackInstanceInfo {
    CTrackKeyBase* pKeyData;
    int32_t objectID;
    int32_t instanceID;
    bool ownedBySequence;
};

struct CSeqTrackParticleInfo {
    CTrackKeyBase* pKeyData;
    int32_t particleSystemID;
};

struct CSequenceInstance {
    int32_t id;
    TrackEvalNode* pEvalNodeHead;
    int32_t sequenceID;
    float headPosition;
    float lastHeadPosition;
    float headDirection;
    float speedScale;
    float volume;
    bool paused;
    bool finished;
    bool hasPlayed;
    bool wrapped;
    int32_t cachedElementID;
    CHashMap<CSeqStackSnapshot, CSeqTrackAudioInfo, 3> trackAudio;
    CHashMap<CSeqStackSnapshot, CSeqTrackInstanceInfo, 3> trackInstances;
    CHashMap<CSeqStackSnapshot, CSeqTrackParticleInfo, 3> trackParticles;
};

struct tagYYRect {
    float left;
    float top;
    float right;
    float bottom;
};

struct cInstancePathAndTimeline {
    int32_t i_pathindex;
    float i_pathposition;
    float i_pathpositionprevious;
    float i_pathspeed;
    float i_pathscale;
    float i_pathorientation;
    int32_t i_pathend;
    float i_pathxstart;
    float i_pathystart;
    int32_t i_timelineindex;
    float i_timelineprevposition;
    float i_timelineposition;
    float i_timelinespeed;
};

struct SLink;

struct SLinkListEx {
    SLink* head;
    SLink* tail;
    int32_t offset;
};

struct SLink {
    SLink* next;
    SLink* prev;
    SLinkListEx* list;
};

struct CInstance {
    int64_t m_CreateCounter;
    CObjectGM *m_pObject;
    CPhysicsObject *m_pPhysicsObject;
    CSkeletonInstance *m_pSkeletonAnimation;
    CSkeletonInstance *m_pMaskSkeleton;
    CSequenceInstance *m_pControllingSeqInst;
    uint32_t m_Instflags;
    int32_t i_id;
    int32_t i_objectindex;
    int32_t i_spriteindex;
    float i_sequencePos;
    float i_lastSequencePos;
    float i_sequenceDir;
    float i_imageindex;
    float i_frameoverflow;
    float i_imagespeed;
    float i_imagescalex;
    float i_imagescaley;
    float i_imageangle;
    uint32_t i_imagealpha;
    uint32_t i_imageblend;
    float i_x;
    float i_y;
    float i_xstart;
    float i_ystart;
    float i_xprevious;
    float i_yprevious;
    float i_direction;
    float i_speed;
    float i_friction;
    float i_gravitydir;
    float i_gravity;
    float i_hspeed;
    float i_vspeed;
    tagYYRect i_bbox;
    int32_t i_timer[12];
    int64_t i_rollbackFrameKilled;
    cInstancePathAndTimeline *m_pPathAndTimeline;
    CCode *i_initcode;
    CCode *i_precreatecode;
    CObjectGM *m_pOldObject;
    int32_t m_nLayerID;
    int32_t i_maskindex;
    short m_nMouseOver;
    CInstance *m_pNext;
    CInstance *m_pPrev;
    SLink m_collisionLink;
    SLink m_dirtyLink;
    SLink m_withLink;
    float i_depth;
    float i_lastImageNumber;
    uint32_t m_collisionTestNumber;
};

// Not checked
struct YYChangeList
{
    int Count = 0;
};

// Not checked
struct CCameraManager
{
    static void SetupGMLFunctions(void*) {}
};

RView _views[32]{};
DynamicArrayOfCPath items{};
YYChangeList g_InstanceChangeArray{};
YYChangeList g_InstanceChangeDepth{};

int GraphicsPerf::ms_DisplayFlags = 0;
int GraphicsPerf::ms_MinimisedFlags = 0;

bool DebugMode = false;
bool ExtDisabled = false;
bool option_displayerrors = true;

enum class WallpaperDisplayMode
{
    Main,
    Monitor,
    Span
};

WallpaperDisplayMode g_WallpaperDisplayMode = WallpaperDisplayMode::Main;

// Not checked
static void CopyToken(const char* src, char* dst, std::size_t dstSize)
{
    if (dst == nullptr || dstSize == 0)
        return;

    std::size_t i = 0;
    while (src[i] != '\0' && i + 1 < dstSize)
    {
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
}

// Not checked
static const char* SkipWhitespace(const char* text)
{
    while (*text == ' ' || *text == '\t' || *text == '\r' || *text == '\n')
        ++text;
    return text;
}

// Not checked
static bool MatchOption(const char* arg, const char* option)
{
    return std::strcmp(arg, option) == 0;
}

// Not checked
static char* DuplicateString(const char* src)
{
    if (src == nullptr)
        return nullptr;

    const std::size_t length = std::strlen(src) + 1u;
    char* copy = static_cast<char*>(std::malloc(length));
    if (copy != nullptr)
        std::memcpy(copy, src, length);
    return copy;
}

void ProcessCommandLine(char* param_1)
{
    if (param_1 == nullptr)
    {
        g_fInAWindow = false;
        ExtDisabled = false;
        g_IO_Record = false;
        g_IO_Playback = false;
        g_fNoAudio = false;
        g_fVMUse = true;
        GraphicsPerf::ms_DisplayFlags = 0;
        DebugMode = false;
        return;
    }

    g_fVMUse = true;
    GraphicsPerf::ms_DisplayFlags = 0;
    DebugMode = false;
    ExtDisabled = false;
    g_IO_Record = false;
    g_IO_Playback = false;
    g_fNoAudio = false;
    g_fInAWindow = false;

    const char* cursor = SkipWhitespace(param_1);
    while (*cursor != '\0')
    {
        const char* argStart = cursor;
        while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
            ++cursor;

        const std::size_t argLen = static_cast<std::size_t>(cursor - argStart);
        if (argLen >= sizeof(g_CmdBuffer))
            break;

        CopyToken(argStart, g_CmdBuffer, sizeof(g_CmdBuffer));

        if (MatchOption(g_CmdBuffer, "-debug"))
        {
            g_fVMDebug = true;
        }
        else if (MatchOption(g_CmdBuffer, "-trace"))
        {
            g_fVMTrace = true;
        }
        else if (MatchOption(g_CmdBuffer, "-displayerrors"))
        {
            option_displayerrors = false;
        }
        else if (MatchOption(g_CmdBuffer, "-vmuse"))
        {
            g_fVMUse = false;
        }
        else if (MatchOption(g_CmdBuffer, "-noaudio"))
        {
            g_fNoAudio = true;
        }
        else if (MatchOption(g_CmdBuffer, "-window"))
        {
            g_fInAWindow = true;
        }
        else if (MatchOption(g_CmdBuffer, "-minidump"))
        {
            g_fCreateMiniDump = true;
            g_fFullMiniDump = false;
        }
        else if (MatchOption(g_CmdBuffer, "-fullminidump"))
        {
            g_fCreateMiniDump = true;
            g_fFullMiniDump = true;
        }
        else if (MatchOption(g_CmdBuffer, "-debugoutput"))
        {
            g_OutputDebugOutput = true;
        }
        else if (MatchOption(g_CmdBuffer, "-extdisabled"))
        {
            ExtDisabled = true;
        }
        else if (MatchOption(g_CmdBuffer, "-game"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pGameName != nullptr)
                {
                    std::free(g_pGameName);
                    g_pGameName = nullptr;
                }
                g_pGameName = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-exitgame"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pExitGame_CMD != nullptr)
                {
                    std::free(g_pExitGame_CMD);
                    g_pExitGame_CMD = nullptr;
                }
                g_pExitGame_CMD = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-yydebugpath"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pYYDebugPath != nullptr)
                {
                    std::free(g_pYYDebugPath);
                    g_pYYDebugPath = nullptr;
                }
                g_pYYDebugPath = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-exitdir"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pExitDir_CMD != nullptr)
                {
                    std::free(g_pExitDir_CMD);
                    g_pExitDir_CMD = nullptr;
                }
                g_pExitDir_CMD = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-io_record"))
        {
            g_IO_Record = true;
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pIO_RecordFileName != nullptr)
                {
                    std::free(g_pIO_RecordFileName);
                    g_pIO_RecordFileName = nullptr;
                }
                g_pIO_RecordFileName = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-steam"))
        {
            g_SteamWorkshop = true;
        }
        else if (MatchOption(g_CmdBuffer, "-fullscreen"))
        {
            GraphicsPerf::ms_DisplayFlags |= 0x40000010;
        }
        else if (MatchOption(g_CmdBuffer, "-debugnetwork"))
        {
            g_DebugNetworkOutput = true;
        }
        else if (MatchOption(g_CmdBuffer, "-playback"))
        {
            g_IO_Playback = true;
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_pIO_RecordFileName != nullptr)
                {
                    std::free(g_pIO_RecordFileName);
                    g_pIO_RecordFileName = nullptr;
                }
                g_pIO_RecordFileName = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-debugconsole"))
        {
            g_ConsoleOutput = true;
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_DebugConsoleOutputFileName != nullptr)
                {
                    std::free(g_DebugConsoleOutputFileName);
                    g_DebugConsoleOutputFileName = nullptr;
                }
                g_DebugConsoleOutputFileName = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-headless"))
        {
            g_fHeadless = true;
            g_fExitAfterFirstRoomCreationCode = true;
            g_fNoErrorWindow = true;
            g_fDisableWindow = true;
            g_fCreateMiniDump = true;
            g_fFullMiniDump = false;
            g_fDoGC = false;
        }
        else if (MatchOption(g_CmdBuffer, "-profile"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (g_ProfileDumpFileName != nullptr)
                {
                    std::free(g_ProfileDumpFileName);
                    g_ProfileDumpFileName = nullptr;
                }
                g_ProfileDumpFileName = DuplicateString(next);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
            const char* intervalStart = SkipWhitespace(cursor);
            if (*intervalStart != '\0')
            {
                g_ProfileDumpInterval = std::atoi(intervalStart);
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-sleepmargin"))
        {
            const char* value = SkipWhitespace(cursor);
            if (*value != '\0')
            {
                g_SleepMargin = std::atoi(value);
                g_OverrideSleepMargin = true;
                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-overridevbmethod"))
        {
            g_OverrideVBmethod = true;
        }
        else if (MatchOption(g_CmdBuffer, "-wallpaper"))
        {
            const char* next = SkipWhitespace(cursor);
            if (*next != '\0')
            {
                if (std::strcmp(next, "main") == 0)
                    g_WallpaperDisplayMode = WallpaperDisplayMode::Main;
                else if (std::strcmp(next, "monitor") == 0)
                    g_WallpaperDisplayMode = WallpaperDisplayMode::Monitor;
                else if (std::strcmp(next, "span") == 0)
                    g_WallpaperDisplayMode = WallpaperDisplayMode::Span;
                else if (std::strcmp(next, "monitor") == 0)
                    g_Monitor = std::atoi(next);

                while (*cursor != '\0' && *cursor != ' ' && *cursor != '\t' && *cursor != '\r' && *cursor != '\n')
                    ++cursor;
            }
        }
        else if (MatchOption(g_CmdBuffer, "-manualvsync"))
        {
            g_ManualVSync = true;
        }
        else if (MatchOption(g_CmdBuffer, "-nodirectinput"))
        {
            g_NoDirectInput = true;
        }
        else if (MatchOption(g_CmdBuffer, "-wallpaperon"))
        {
            g_fDoWallpaper = true;
        }
        else if (MatchOption(g_CmdBuffer, "-sethighpriority"))
        {
            g_bSetHighProcessPriority = false;
        }

        cursor = SkipWhitespace(cursor);
    }
}

bool Init(void)
{
    uint64_t startTick = 0;
    int64_t timingNow = 0;

    RomDisk::ms_pRomDiskBase = g_RomDisk;
    RomDisk::ms_nRomDiskSize = 0;

    int32_t count;
    std::memcpy(&count, g_RomDisk, sizeof(count));

    if (count > 0)
    {
        int index = 0;
        while (index < count)
        {
            int32_t entryValue;
            std::memcpy(
                &entryValue,
                g_RomDisk + static_cast<size_t>(index) * 8 + 4,
                sizeof(entryValue)
            );

            RomDisk::ms_nRomDiskSize = index + entryValue;

            ++index;
        }
    }

    if (!QueryPerformanceFrequency(reinterpret_cast<int64_t*>(&g_QPCFreq)))
    {
        startTick = GetTickCount64() * 1000ULL;
        timing_start = startTick;
        g_QPCFreq = 0;
    }
    else
    {
        QueryPerformanceCounter(reinterpret_cast<int64_t*>(&timing_start));
    }

    g_TimingStart = timing_start;
    g_flagBitPattern = static_cast<int>(Timing_Time());

    InitFastCRC();
    INITIALIZE_PlatformSpecific();
    MakeTempDir();
    GR_Draw_Circle_Precision(0x18);

    setlocale(LC_ALL, ".UTF8");
    setlocale(LC_CTYPE, "C");
    setlocale(LC_ALL, "");

    g_AppSurfaceEnabled = true;
    g_bUsingAppSurface = true;

    for (int i = 0; i < 32; ++i)
        _views[i].def = false;

    _views_count = 0;

    ParticleType_DestroyAll();
    ParticleSystem_DestroyAll();
    INITIALIZE_Run_Global();
    INITIALIZE_Time_Main();

    using BuiltinVarLookupMap = CHashMap<void*, void*, 8>;

    BuiltinVarLookupMap* hashMap =
        static_cast<BuiltinVarLookupMap*>(
            MemoryManager::_Alloc(0x28, "", 0x406e2960, true));

    if (hashMap == nullptr)
    {
        MemoryManager::DumpMemory(nullptr, nullptr, false);

        char msg[1024];
        std::snprintf(msg, sizeof(msg),
            "Memory allocation failed: Attempting ...");
        YYError(msg);
        return false;
    }

    hashMap->m_elements = nullptr;
    hashMap->m_curSize = 8;
    hashMap->m_deleter = nullptr;
    BuiltinVarLookupMap::Init(hashMap);
    g_builtinVarLookup = hashMap;

    InitLocalVariables();
    InitGlobalVariables();

    items.arr = nullptr;
    items.length = 0;
    HighScore_Clear();

    g_InstanceChangeArray.Count = 0;
    g_InstanceChangeDepth.Count = 0;

    CCameraManager::SetupGMLFunctions(reinterpret_cast<CCameraManager*>(builtin_variables));
    ProcessMessages();

    return true;
}