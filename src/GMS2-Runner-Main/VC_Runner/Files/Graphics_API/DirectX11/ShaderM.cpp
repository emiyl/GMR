// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Graphics_API\DirectX11\ShaderM.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\ShaderM.obj
// 29 function symbol(s) attributed to this object.

void D3D11ConstantBuffer::D3D11ConstantBuffer(void);
void D3D11ConstantBufferVariable::D3D11ConstantBufferVariable(void);
void D3D11Sampler::D3D11Sampler(void);
void D3D11ConstantBuffer::~D3D11ConstantBuffer(void);
void D3D11ConstantBufferVariable::~D3D11ConstantBufferVariable(void);
void D3D11Sampler::~D3D11Sampler(void);
void CreateConstantBuffers(void *);
void CreateConstantBuffersD3DResources(void *);
void CreateInputs(void *);
void CreateSamplers(void *);
void CreateVariables(void *);
void InvalidateShaderResources(void);
int32_t Shader_Add(void *, void *, bool);
int32_t Shader_Get_Sampler_Index(void *, void *);
int32_t Shader_Get_Uniform_Handle(void *, void *);
bool Shader_Load(void *);
bool Shader_Set_Uniform_F(int32_t, int32_t, double, double, double, double);
bool Shader_Set_Uniform_FA(int32_t, int32_t, /* type 0x640 */);
bool Shader_Set_Uniform_I(int32_t, int32_t, double, double, double, double);
bool Shader_Set_Uniform_IA(int32_t, int32_t, /* type 0x674 */);
bool Shader_Set_Uniform_Matrix_N(int32_t, int32_t, /* type 0x640 */);
void * _CloneFromShaderHeader(void *);
void * _GetInputLayout(int32_t, /* type 0x674 */, void *, /* type 0x674 */, void *, int32_t, char*, int32_t);
int32_t _InitShader(void *);
void _SetVar(void *, int32_t, /* type 0x603 */, int32_t);
