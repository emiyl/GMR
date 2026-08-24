// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Graphics\Graphics_Texture.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\Graphics_Texture.obj
// 51 function symbol(s) attributed to this object.

void SSpriteLoadRequest::SSpriteLoadRequest(void *, int32_t, int32_t, int32_t, int32_t, bool);
void TextureLoadManager::LockHelper::~LockHelper(void);
void SSpriteLoadRequest::~SSpriteLoadRequest(void);
void TextureLoadManager::AbortTextureGroupLoadRequest(void *, bool);
void TextureLoadManager::AbortTextureGroupLoadRequests(int32_t, bool);
int32_t AllocTexture(void);
bool DrawIt_Color(/* type 0x603 */, float, float, float, float, float, float, float, float, float, float, float, float, uint32_t, uint32_t, uint32_t, uint32_t);
int32_t GR_Texture_Create(uint8_t*, uint32_t, bool, bool);
int32_t GR_Texture_Create_And_Fill(int32_t, int32_t,uint8_t*, uint32_t, /* type 0x72fd (LF_ENUM) */, /* type 0x7362 (LF_ENUM) */);
int32_t GR_Texture_Create_Bytes(int32_t, int32_t, void *);
int32_t GR_Texture_Create_Empty(int32_t, int32_t, bool, bool, /* type 0x72fd (LF_ENUM) */);
int32_t GR_Texture_Create_From_File(uint8_t*, uint32_t);
bool GR_Texture_Draw(int32_t, float, float, float, float, float, float, float, uint32_t, float);
bool GR_Texture_Draw(void *, float, float, float, float, float, float, float, uint32_t, float);
bool GR_Texture_Draw_Part(int32_t, float, float, float, float, float, float, float, float, float, uint32_t, float);
bool GR_Texture_Draw_Part(void *, float, float, float, float, float, float, float, float, float, uint32_t, float);
bool GR_Texture_Draw_Part_Color(int32_t, float, float, float, float, float, float, float, float, float, uint32_t, uint32_t, uint32_t, uint32_t, float);
bool GR_Texture_Draw_Part_Color(void *, float, float, float, float, float, float, float, float, float, uint32_t, uint32_t, uint32_t, uint32_t, float);
bool GR_Texture_Draw_Simple(int32_t, float, float);
bool GR_Texture_Draw_Simple(void *, float, float);
bool GR_Texture_Draw_Tiled(int32_t, float, float, float, float, float, float, bool, bool, float, float, float, float, uint32_t, float);
bool GR_Texture_Draw_Tiled(void *, float, float, float, float, float, float, bool, bool, float, float, float, float, uint32_t, float);
bool GR_Texture_Exists(int32_t, bool, bool, bool, bool);
void GR_Texture_Free(int32_t);
void * GR_Texture_Get(int32_t, bool, bool, bool, bool);
/* type 0x603 */ GR_Texture_Get_Surface(int32_t);
void GR_Texture_Init(void);
bool GR_Texture_Is_Format_Supported(/* type 0x72fd (LF_ENUM) */);
void * TextureLoadManager::GetSpriteLoadRequest(int32_t);
int32_t TextureLoadManager::GetTextureGroupLoadRequestInProgress(int32_t, bool);
void * TextureLoadManager::GetTextureLoadRequest(int32_t);
bool TextureLoadManager::LoadGroup(int32_t, bool, bool);
void TextureLoadManager::Process(void);
bool TextureLoadManager::ProcessSpriteLoadRequest(void *, bool);
bool TextureLoadManager::ProcessTextureGroupLoadRequest(void *, bool);
bool TextureLoadManager::ProcessTextureLoadRequest(void *, bool);
void TextureDecompressAsyncFunc(void *, int32_t, int32_t, /* type 0x13 */);
void * TextureGroupInfo_Create(/* type 0x674 */);
bool TextureGroupInfo_Delete(int32_t);
void * TextureGroupInfo_FindTex(int32_t);
int32_t TextureGroupInfo_GetStatus(int32_t);
bool TextureGroupInfo_Load(uint8_t*, uint32_t,uint8_t*);
void TextureGroupInfo_RefreshTextureState(int32_t);
void TextureLoadRequestAsyncFunc(void *, int32_t, /* type 0x13 */);
bool TextureLoadManager::UnloadGroup(int32_t);
