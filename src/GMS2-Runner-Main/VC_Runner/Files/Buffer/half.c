// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Buffer\half.c
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\IBuffer.obj
// 42 function symbol(s) attributed to this object.

void IBuffer::IBuffer(int32_t, /* type 0x8229 (LF_ENUM) */, int32_t);
void IBuffer::~IBuffer(void);
int32_t IBuffer::Base64decode(void *, int32_t, int32_t);
void IBuffer::Base64encode(void *, int32_t, int32_t);
void IBuffer::CRC32(void *, int32_t, int32_t);
uchar* uint8_t* IBuffer::Compress(int32_t, int32_t, void *);
void IBuffer::Copy(int32_t, int32_t, void *, int32_t, bool);
int32_t IBuffer::CopyMemoryToBuffer(void *, void *, int32_t, int32_t, int32_t, int32_t, bool, bool, bool);
int32_t IBuffer::CopyMemoryToMemory(uchar* uint8_t*, int32_t, uchar* uint8_t*, int32_t, int32_t, int32_t, int32_t, bool, bool);
uchar* uint8_t* IBuffer::Decompress(void *);
void IBuffer::Fill(int32_t, int32_t, /* type 0x7ded (LF_ENUM) */, void *, int32_t, bool);
void IBuffer::GetSurface(int32_t);
bool IBuffer::GetSurfaceDepth(int32_t);
int32_t IBuffer::Load(void *, int32_t, int32_t, int32_t);
void IBuffer::MD5(void *, int32_t, int32_t);
void IBuffer::Peek(int32_t, /* type 0x7ded (LF_ENUM) */, void *);
void IBuffer::Poke(int32_t, /* type 0x7ded (LF_ENUM) */, void *);
/* type 0x23 */ IBuffer::Read(void *, /* type 0x23 */, /* type 0x23 */);
int32_t IBuffer::Read(/* type 0x7ded (LF_ENUM) */, void *);
void * IBuffer::ReadString(void);
void IBuffer::Resize(int32_t);
void IBuffer::SHA1(void *, int32_t, int32_t);
int32_t IBuffer::Save(void *, int32_t, int32_t);
int32_t IBuffer::Seek(/* type 0x8249 (LF_ENUM) */, int32_t);
void IBuffer::SetSurface(int32_t, int32_t);
bool IBuffer::SetSurfaceDepth(int32_t, int32_t);
int32_t IBuffer::SizeOf(/* type 0x7ded (LF_ENUM) */);
int32_t IBuffer::Write(void *);
/* type 0x23 */ IBuffer::Write(void *, /* type 0x23 */, /* type 0x23 */);
int32_t IBuffer::Write(/* type 0x7ded (LF_ENUM) */, void *);
int32_t IBuffer::WriteArray(/* type 0x7ded (LF_ENUM) */, uchar* uint8_t*, int32_t);
/* type 0x21 */ double_to_half(double);
uint32_t half_to_float(/* type 0x21 */);
