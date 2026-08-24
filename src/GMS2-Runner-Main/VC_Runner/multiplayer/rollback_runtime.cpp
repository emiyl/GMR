// Reconstructed from PDB debug info.
// Original path : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\multiplayer\rollback_runtime.cpp
// Compiled into : D:\a\GameMaker\GameMaker\GameMaker\Runner\GMS2-Runner-Main\VC_Runner\x64\Release-Zeus\rollback_runtime.obj
// 73 function symbol(s) attributed to this object.

void std::_Tree_val<std::_Tree_simple_types<std::pair<int const ,Rollback::PlayerInfo> > >::_Erase_tree<std::allocator<std::_Tree_node<std::pair<int const ,Rollback::PlayerInfo>,void *> > >(void *, void *);
void std::_Tree_val<std::_Tree_simple_types<std::pair<int const ,Rollback::PlayerPref> > >::_Erase_tree<std::allocator<std::_Tree_node<std::pair<int const ,Rollback::PlayerPref>,void *> > >(void *, void *);
void std::map<int,int,std::less<int>,std::allocator<std::pair<int const ,int> > >::map<int,int,std::less<int>,std::allocator<std::pair<int const ,int> > >(void);
void std::_Alloc_construct_ptr<std::allocator<std::_Tree_node<std::pair<int const ,int>,void *> > >::~_Alloc_construct_ptr<std::allocator<std::_Tree_node<std::pair<int const ,int>,void *> > >(void);
void std::_Alloc_construct_ptr<std::allocator<std::_Tree_node<std::pair<int const ,Rollback::PlayerPref>,void *> > >::~_Alloc_construct_ptr<std::allocator<std::_Tree_node<std::pair<int const ,Rollback::PlayerPref>,void *> > >(void);
void std::_Hash<std::_Uset_traits<RValue *,std::_Uhash_compare<RValue *,std::hash<RValue *>,std::equal_to<RValue *> >,std::allocator<RValue *>,0> >::~_Hash<std::_Uset_traits<RValue *,std::_Uhash_compare<RValue *,std::hash<RValue *>,std::equal_to<RValue *> >,std::allocator<RValue *>,0> >(void);
void std::_Hash_vec<std::allocator<std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<RValue *> >,std::_Iterator_base0> > >::~_Hash_vec<std::allocator<std::_List_unchecked_const_iterator<std::_List_val<std::_List_simple_types<RValue *> >,std::_Iterator_base0> > >(void);
void std::_Tree<std::_Tmap_traits<int,Rollback::PlayerPref,std::less<int>,std::allocator<std::pair<int const ,Rollback::PlayerPref> >,0> >::~_Tree<std::_Tmap_traits<int,Rollback::PlayerPref,std::less<int>,std::allocator<std::pair<int const ,Rollback::PlayerPref> >,0> >(void);
void std::list<RValue *,std::allocator<RValue *> >::~list<RValue *,std::allocator<RValue *> >(void);
void std::map<int,Rollback::PlayerInfo,std::less<int>,std::allocator<std::pair<int const ,Rollback::PlayerInfo> > >::~map<int,Rollback::PlayerInfo,std::less<int>,std::allocator<std::pair<int const ,Rollback::PlayerInfo> > >(void);
void Rollback::DeadRefsCheckContext::~DeadRefsCheckContext(void);
void Rollback::DumpDiff::~DumpDiff(void);
void * std::map<int,int,std::less<int>,std::allocator<std::pair<int const ,int> > >::operator[](void *);
void Rollback::Check_Dead_Refs(void);
void Rollback::Create_Player(void *, int32_t);
void Rollback::Create_Players(void);
void * Rollback::GetPlayerLayer(void);
void Rollback::Multiplayer_Step(void *);
bool Rollback::Multiplayer_Step_Advance(void);
void Rollback::Set_Player_Status(int32_t, void *);
void * std::_Tree_val<std::_Tree_simple_types<std::pair<int const ,int> > >::_Extract(/* struct 0x16031 */);
void * std::_Tree_val<std::_Tree_simple_types<std::pair<int const ,int> > >::_Insert_node(void, void *);
void * std::_Tree_val<std::_Tree_simple_types<std::pair<int const ,Rollback::PlayerPref> > >::_Insert_node(void, void *);
void std::_Tree_val<std::_Tree_simple_types<std::pair<int const ,int> > >::_Lrotate(void *);
void std::_Tree_val<std::_Tree_simple_types<std::pair<int const ,int> > >::_Rrotate(void *);
bool Rollback::GMSessionListener::advance_frame(void);
void * std::allocator<std::_Tree_node<std::pair<int const ,Rollback::PlayerPref>,void *> >::allocate(void);
uint8_t* Rollback::GMSessionListener::allocate_buffer(uint32_t);
void std::_Tree<std::_Tmap_traits<int,int,std::less<int>,std::allocator<std::pair<int const ,int> >,0> >::clear(void);
bool Rollback::GMSessionListener::compress_game_state(uint8_t*, uint32_t, void *, void *);
bool Rollback::GMSessionListener::decompress_game_state(uint8_t*, uint32_t, void *, void *);
/* type 0x23 */ std::_Tree<std::_Tmap_traits<int,int,std::less<int>,std::allocator<std::pair<int const ,int> >,0> >::erase(void *);
void Rollback::GMSessionListener::free_buffer(uint8_t*);
bool Rollback::GMSessionListener::is_ready_to_start(void);
bool Rollback::GMSessionListener::load_game_state(uint8_t*, int32_t, uint8_t*, int32_t);
bool Rollback::GMSessionListener::log_game_state(void *, uint8_t*, int32_t);
bool Rollback::GMSessionListener::log_game_state_diff(uint8_t*, int32_t, uint8_t*, int32_t);
void Rollback::log_game_state_summary(uint8_t*, int32_t);
bool Rollback::GMSessionListener::on_event(void *);
bool Rollback::GMSessionListener::save_game_state(void *, void *, void *, void *);
void Rollback::show_message_in_runner(void *, /* type 0x0 */);
