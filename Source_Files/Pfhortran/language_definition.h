// Supersedes file "Pfhortran Language Definition".
// Translations of names into internal numbers (can be symbolic constants)
// Format: {"Name", Number}, [C syntax for array member that's a struct]
{"Camera_Move", Camera_Move},
{"Camera_Look", Camera_Look},
{"Wait_Ticks", Wait_Ticks},
{"Inflict_Damage", Inflict_Damage},
{"Jump", Jump},
{"Enable_Player", Enable_Player},
{"Disable_Player", Disable_Player},
{"Script_End", Script_End},
{"Hide_Interface", Hide_Interface},
{"Show_Interface", Show_Interface},
{"Set_Tag_State", Set_Tag_State},
{"Get_Tag_State", Get_Tag_State},
{"Def", Define},
{"Define", Define},
{"Add", sAdd},
{"Subtract", sSubtract},
{"If_Equal", If_Equal},
{"If_=", If_Equal},
{"Set", Set},
{"Call", Call},
{"Return", Return},
{"If_Greater", If_Greater},
{"If_>", If_Greater},
{"If_Less", If_Less},
{"If_<", If_Less},
{"If_!Equal", If_Not_Equal},
{"If_Not_Equal", If_Not_Equal},
{"If_!=", If_Not_Equal},
{"Get_Life", Get_Life},
{"Set_Life", Set_Life},
{"Get_Oxygen", Get_Oxygen},
{"Set_Oxygen", Set_Oxygen},
{"End", End},
{"Get_My_Value", Get_My_Value},
{"Add_Item", Add_Item},
{"Select_Weapon", Select_Weapon},
{"Block_Start", Block_Start},
{"Block_End", Block_End},
{"Init_Cameras", Init_Cameras},
{"Select_Camera", Select_Camera},
{"Set_Camera_Poly", Set_Camera_Poly},
{"Set_Camera_Pos", Set_Camera_Pos},
{"Set_Camera_YP", Set_Camera_YP},
{"Activate_Camera", Activate_Camera},
{"Use_Camera", Use_Camera},
{"Init_Paths", Init_Paths},
{"New_Path", New_Path},
{"Dispose_Path", Dispose_Path},
{"Select_Path", Select_Path},
{"Set_Path_Move_Speed", Set_Path_Move_Speed},
{"Select_Point", Select_Point},
{"Set_Point_Poly", Set_Point_Poly},
{"Set_Point_Pos", Set_Point_Pos},
{"Set_Point_YP", Set_Point_YP},
{"Start_Camera_On_Path", Start_Camera_On_Path},
{"Set_Path_Roll_Speed", Set_Path_Roll_Speed},
{"Wait_For_Path", Wait_For_Path},
{"Change_Soundtrack", Change_Soundtrack},
{"Set_Fog_Depth", Set_Fog_Depth},
{"Set_Fog_Color", Set_Fog_Color},
{"Get_Fog_Depth", Get_Fog_Depth},
{"Get_Fog_Color", Get_Fog_Color},
{"Teleport_Player", Teleport_Player},
{"Monster_New", Monster_New},
{"Monster_Sleep", Monster_Sleep},
{"Monster_Hurt", Monster_Hurt},
{"Monster_Attack", Monster_Attack},
{"Monster_Move", Monster_Move},
{"Monster_Select", Monster_Select},
{"Monster_Get_Immunity", Monster_Get_Immunity},
{"Monster_Set_Immunity", Monster_Set_Immunity},
{"Monster_Get_Weakness", Monster_Get_Weakness},
{"Monster_Set_Weakness", Monster_Set_Weakness},
{"Monster_Get_Friend", Monster_Get_Friend},
{"Monster_Set_Friend", Monster_Set_Friend},
{"Monster_Get_Enemy", Monster_Get_Enemy},
{"Monster_Set_Enemy", Monster_Set_Enemy},
{"Monster_Get_Item", Monster_Get_Item},
{"Monster_Set_Item", Monster_Set_Item},
{"Monster_Get_Nuke", Monster_Get_Nuke},
{"Monster_Set_Nuke", Monster_Set_Nuke},
{"Set_UnderFog_Depth", Set_UnderFog_Depth},
{"Set_UnderFog_Color", Set_UnderFog_Color},
{"Get_UnderFog_Depth", Get_UnderFog_Depth},
{"Get_UnderFog_Color", Get_UnderFog_Color},
{"Get_Random", Get_Random},
{"Set_Platform_State", Set_Platform_State},
{"Get_Platform_State", Get_Platform_State},
{"Set_Light_State", Set_Light_State},
{"Get_Light_State", Get_Light_State},
{"Get_Player_Poly", Get_Player_Poly},
{"Get_Fog_Presence", Get_Fog_Presence},
{"Set_Fog_Presence", Set_Fog_Presence},
{"Get_UnderFog_Presence", Get_UnderFog_Presence},
{"Set_UnderFog_Presence", Set_UnderFog_Presence},
{"Remove_Item", Remove_Item},
{"Player_Control", Player_Control},
{"Play_Sound",Play_Sound},
{"TRUE", 0x1},
{"FALSE", 0x0},
{"knife", 0x0},
{"fist", 0x0},
{"magnum", 0x01},
{"magnum_magazine", 0x02},
{"plasma_pistol", 0x03},
{"plasma_magazine", 0x04},
{"assault_rifle", 0x05},
{"assault_rifle_magazine", 0x06},
{"assault_grenade_magazine", 0x07},
{"missile_launcher", 0x08},
{"missile_launcher_magazine", 0x09},
{"invisibility_powerup", 0x0A},
{"invincibility_powerup", 0x0B},
{"infravision_powerup", 0x0C},
{"alien_shotgun", 0x0D},
{"alien_shotgun_magazine", 0x0E},
{"flamethrower", 0x0F},
{"flamethrower_canister", 0x10},
{"extravision_powerup", 0x11},
{"oxygen_powerup", 0x12},
{"energy_powerup", 0x13},
{"double_energy_powerup", 0x14},
{"triple_energy_powerup", 0x15},
{"shotgun", 0x16},
{"shotgun_magazine", 0x17},
{"spht_door_key", 0x18},
{"uplink_chip", 0x19},
{"smg", 0x22},
{"smg_ammo", 0x23},
{"default_camera", 0x0},
{"minor_tick", 0x01},
{"major_tick", 0x02},
{"kamikaze_tick", 0x03},
{"minor_compiler", 0x04},
{"major_compiler", 0x05},
{"minor_invisible_compiler", 0x06},
{"major_invisible_compiler", 0x07},
{"minor_fighter", 0x08},
{"major_fighter", 0x09},
{"minor_projectile_fighter", 0x0A},
{"major_projectile_fighter", 0x0B},
{"green_bob", 0x0C},
{"blue_bob", 0x0D},
{"security_bob", 0x0E},
{"explodabob", 0x0F},
{"minor_drone", 0x10},
{"major_drone", 0x11},
{"big_minor_drone", 0x12},
{"big_major_drone", 0x13},
{"possessed_drone", 0x14},
{"minor_cyborg", 0x15},
{"major_cyborg", 0x16},
{"minor_flame_cyborg", 0x17},
{"major_flame_cyborg", 0x18},
{"minor_enforcer", 0x19},
{"major_enforcer", 0x1A},
{"minor_hunter", 0x1B},
{"major_hunter", 0x1C},
{"minor_trooper", 0x1D},
{"major_trooper", 0x1E},
{"mega_cyborg", 0x1F},
{"mega_hunter", 0x20},
{"sewage_yeti", 0x21},
{"water_yeti", 0x22},
{"lava_yeti", 0x23},
{"minor_defender", 0x24},
{"major_defender", 0x25},
{"minor_juggernaut", 0x26},
{"major_juggernaut", 0x27},
{"tiny_pfhor", 0x28},
{"tiny_bob", 0x29},
{"tiny_yeti", 0x2A},
{"green_vacbob", 0x2B},
{"blue_vacbob", 0x2C},
{"security_vacbob", 0x2D},
{"explodavacbob", 0x2E},
{"explosion", 0x00},
{"staff", 0x01},
{"projectile", 0x02},
{"absorbed", 0x03},
{"flame", 0x04},
{"claws", 0x05},
{"alien_weapon", 0x06},
{"hulk_slap", 0x07},
{"compiler", 0x08},
{"fusion", 0x09},
{"hunter", 0x0A},
{"fists", 0x0B},
{"teleporter", 0x0C},
{"defender", 0x0D},
{"yeti_claws", 0x0E},
{"yeti_projectile", 0x0F},
{"crushing", 0x10},
{"lava", 0x11},
{"suffocation", 0x12},
{"goo", 0x13},
{"energy_drain", 0x14},
{"oxygen_drain", 0x15},
{"drone", 0x16},
{"shotgun", 0x17},
{"class_player", 0x00},
{"class_bob", 0x01},
{"class_madd", 0x02},
{"class_possessed_drone", 0x03},
{"class_defender", 0x04},
{"class_fighter", 0x05},
{"class_trooper", 0x06},
{"class_hunter", 0x07},
{"class_enforcer", 0x08},
{"class_juggernaut", 0x09},
{"class_drone", 0x0A},
{"class_compiler", 0x0B},
{"class_cyborg", 0x0C},
{"class_explodabob", 0x0D},
{"class_tick", 0x0E},
{"class_yeti", 0x0F},
{"_moving_forward", 0x00},
{"_moving_backward", 0x01},
{"_sidestepping_left", 0x02},
{"_sidestepping_right", 0x03},
{"_turning_left", 0x04},
{"_turning_right", 0x05},
{"_looking_up", 0x06},
{"_looking_down", 0x07},
{"_action_trigger_state", 0x08},
{"_left_trigger_state", 0x09},
{"_right_trigger_state", 0x0A},
{"_start_queue",0x0A},
{"_stop_queue",0x0B},
{"_reset_queue",0x0C},
