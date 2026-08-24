// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Graphics_API\DirectX11\TexturesM.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\TexturesM.obj
// 21 function symbol(s) attributed to this object.

void Texture::Texture(int32_t, int32_t, int32_t);
/* type 0x736a (LF_ENUM) */ ConvertInternalToD3DTexFormat(/* type 0x72fd (LF_ENUM) */);
bool Graphics::CopySurface(/* type 0x603 */, int32_t, int32_t, int32_t, /* type 0x603 */, int32_t, /* type 0x72fd (LF_ENUM) */);
/* type 0x603 */ Graphics::CreateTexture(int32_t, int32_t, int32_t, /* type 0x7362 (LF_ENUM) */, /* type 0x72fd (LF_ENUM) */, uint8_t*);
/* type 0x603 */ Graphics::CreateTextureFromData(uint8_t*, uint32_t, int32_t, int32_t, void *, /* type 0x72fd (LF_ENUM) */, /* type 0x7362 (LF_ENUM) */);
/* type 0x603 */ Graphics::CreateTextureFromFile(uint8_t*, uint32_t, void *, /* type 0x72fd (LF_ENUM) */, bool);
void Graphics::FlushTexture(/* type 0x603 */);
void FreeTexInfo(void *);
void Graphics::FreeTexture(/* type 0x603 */);
bool Graphics::SaveRenderTarget(void);
void Texture::SetReady(void);
bool Graphics::SetRenderTarget(int32_t, /* type 0x603 */, /* type 0x603 */);
void SetupBlankTexture(void);
void SetupD3DTexture(void *, /* type 0x735c (LF_ENUM) */, void *, int32_t, int32_t);
void SetupD3DTextureIfInvalid(void *, bool, /* type 0x735c (LF_ENUM) */, void *, int32_t, int32_t);
void SetupScreenTexture(void);
bool Graphics::UpdateRegion(/* type 0x603 */, int32_t, int32_t, int32_t, int32_t);
void _InvalidateTextureState(void);
void _SetRTConfig(void);
void _SetTexture(int32_t, /* type 0x603 */, bool);
