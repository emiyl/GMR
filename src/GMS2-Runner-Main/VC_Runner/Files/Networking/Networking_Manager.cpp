// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\Files\Networking\Networking_Manager.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\Networking_Manager.obj
// 64 function symbol(s) attributed to this object.

void SOCKET_AutoMutex::~SOCKET_AutoMutex(void);
int32_t AllocSocket(void);
void F_NETWORK_Connect(void *, void *, void *, int32_t, void *);
void F_NETWORK_Connect_ASync(void *, void *, void *, int32_t, void *);
void F_NETWORK_Connect_ASync_ex(void *, void *, void *, int32_t, void *);
void F_NETWORK_Connect_ex(void *, void *, void *, int32_t, void *);
void F_NETWORK_Create_Server(void *, void *, void *, int32_t, void *);
void F_NETWORK_Create_Server_Raw(void *, void *, void *, int32_t, void *);
void F_NETWORK_Create_Socket(void *, void *, void *, int32_t, void *);
void F_NETWORK_Create_Socket_Ext(void *, void *, void *, int32_t, void *);
void F_NETWORK_Destroy_Socket(void *, void *, void *, int32_t, void *);
void F_NETWORK_Resolve(void *, void *, void *, int32_t, void *);
void F_NETWORK_Send_Broadcast(void *, void *, void *, int32_t, void *);
void F_NETWORK_Send_Packet(void *, void *, void *, int32_t, void *);
void F_NETWORK_Send_Raw(void *, void *, void *, int32_t, void *);
void F_NETWORK_Send_UDP(void *, void *, void *, int32_t, void *);
void F_NETWORK_Send_UDP_Raw(void *, void *, void *, int32_t, void *);
void F_NETWORK_Set_Config(void *, void *, void *, int32_t, void *);
void F_NETWORK_Set_Timeout(void *, void *, void *, int32_t, void *);
int32_t FreeSocket(void *);
void FreeSocket(int32_t);
void InitNetworkingFunctions(void);
bool IsWindows8OrGreater(void);
void PollServersOnly(void);
void ProcessNetworking(void);
void QuitNetworkingFunctions(void);
bool RelyAckAdd(int32_t, void *, int32_t, uint32_t);
void RelyAckSendToClient(void *);
void RelyAddPacket(int32_t, void *, int32_t, uint32_t, int32_t);
void RelyDeletePacket(void *);
int32_t RelySendAckPacket(int32_t, void *, int32_t, int32_t);
int32_t RelySendData(int32_t, void *, int32_t, int32_t, int32_t);
int32_t RelySendReliable(int32_t, void *, int32_t, int32_t, int32_t);
void ThrowConnectingSocketNetworkEvent(int32_t, int32_t, int32_t, int32_t, /* type 0x670 */, bool);
void ThrowNetworkEvent(int32_t, int32_t, int32_t, void *);
void ThrowNonBlockingConnectSocketNetworkEvent(int32_t, bool);
void createServerHelper(void *, void *, void *, int32_t, void *, bool);
double networkSendUDPHelper(int32_t, /* type 0x670 */, int32_t, int32_t, int32_t, bool, void *);
