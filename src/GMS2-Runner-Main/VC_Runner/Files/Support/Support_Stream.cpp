// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Support\Support_Stream.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\Support_Stream.obj
// 18 function symbol(s) attributed to this object.

void CStream::CStream(int32_t);
void CStream::~CStream(void);
void CStream::ConvertFromString(void *);
void CStream::ConvertToString(void *);
/* type 0x603 */ MyZAlloc(/* type 0x603 */, uint32_t, uint32_t);
void MyZFree(/* type 0x603 */, /* type 0x603 */);
void * CStream::ReadCompressedStream(void);
/* type 0x13 */ CStream::ReadInteger64(void);
int32_t CStream::ReadInteger(void);
double CStream::ReadReal(void);
void CStream::ReadString(void *);
int32_t CStream::Write(/* type 0x603 */, int32_t);
void CStream::WriteInteger64(/* type 0x13 */);
void CStream::WriteInteger(int32_t);
int32_t ZDecompressStream(void *, void *);
int32_t CStream::_AllocExtraSpace(int32_t);
