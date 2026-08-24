// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Graphics\Graphics_Surface.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\Graphics_Surface.obj
// 25 function symbol(s) attributed to this object.

void Hash<RSurface>::Add(uint32_t, void *);
void Hash<RSurface>::Clear(/* type 0x6f9f (LF_ENUM) */);
bool Hash<RSurface>::Delete(uint32_t, /* type 0x6f9f (LF_ENUM) */);
bool FindActiveSurface(int32_t);
int32_t GR_Surface_Create(int32_t, int32_t, int32_t, /* type 0x72fd (LF_ENUM) */);
void GR_Surface_Draw(int32_t, float, float, float, float, float, uint32_t, float);
void GR_Surface_DrawStretched(int32_t, float, float, float, float, uint32_t, float);
void GR_Surface_DrawTiled(int32_t, float, float, float, float, bool, bool, float, float, float, float, uint32_t, float);
bool GR_Surface_Exists(int32_t);
void GR_Surface_FreeAll(void);
void * GR_Surface_Get(int32_t);
/* type 0x72fd (LF_ENUM) */ GR_Surface_Get_Format(int32_t);
int32_t GR_Surface_Get_Height(int32_t);
/* type 0x13 */ GR_Surface_Get_Texture(int32_t);
int32_t GR_Surface_Get_Width(int32_t);
bool GR_Surface_Is_Format_Supported(/* type 0x72fd (LF_ENUM) */);
bool GR_Surface_Resize(int32_t, int32_t, int32_t);
void * GR_Surface_Screenshot_Part(int32_t, int32_t, int32_t, int32_t, int32_t);
void * GetSurfaceFormatName(/* type 0x72fd (LF_ENUM) */);
bool YYGML_draw_surface_part_ext(int32_t, float, float, float, float, float, float, float, float, int32_t, float);
bool YYGML_surface_reset_target(void);
bool YYGML_surface_set_target_ext(int32_t, int32_t, int32_t);
void * _FreeSurfaceData(int32_t);
