// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\IO\Win32\LoadSave.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\LoadSave.obj
// 36 function symbol(s) attributed to this object.

void HTTP_REQ_CONTEXT_WIN32::HTTP_REQ_CONTEXT_WIN32(void *, int32_t, void *, void *, /* type 0x603 */, int32_t, void *, int32_t);
void HTTP_REQ_CONTEXT_WIN32::~HTTP_REQ_CONTEXT_WIN32(void);
void HTTP_URL_DETAILS::~HTTP_URL_DETAILS(void);
bool AddHttpThread(void *, void *);
bool LoadSave::BundleFileExists(void *);
void HTTP_CompleteReadFile(void *);
void HTTP_CrackUrl(void *, void *);
void LoadSave::HTTP_Get(void *, void *, void *, /* type 0x603 */, int32_t);
/* type 0x22 */ HTTP_Get_Proc(/* type 0x603 */);
void LoadSave::HTTP_Post(void *, void *, void *, void *, /* type 0x603 */, int32_t);
/* type 0x22 */ HTTP_Post_Proc(/* type 0x603 */);
void LoadSave::HTTP_Request(void *, void *, void *, void *, void *, void *, /* type 0x603 */, int32_t, int32_t, bool);
/* type 0x22 */ HTTP_Request_Proc(/* type 0x603 */);
void LogInetError(/* type 0x22 */, void *);
bool LoadSave::ReadBundleFileAsync(void *, void *, /* type 0x13 */);
void ReadBundleFileAsyncThreadFunc(/* type 0x13 */);
void RemoveHttpRequest(void *);
int32_t LoadSave::RemoveSaveFile(void *, /* type 0x603 */);
bool LoadSave::WriteFile(void *, void *, int32_t, void *, /* type 0x603 */);
void * YYFOPEN(void *, void *);
bool LoadSave::_FileExists(char*);
int32_t LoadSave::_GetBundleFileName(char*, int32_t, void *);
int32_t LoadSave::_GetSaveFileName(char*, int32_t, void *);
void _LogInetError(/* type 0x22 */, void *, void *);
char* LoadSave::_ReadFile(void *, /* type 0x675 */);
