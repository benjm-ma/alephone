/*
LUA_PLAYER.CPP

	Copyright (C) 2008 by Gregory Smith
 
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	This license is contained in the file "COPYING",
	which is included with this source code; it is available online at
	http://www.gnu.org/licenses/gpl.html

	Implements the Lua Player class
*/

#include "ActionQueues.h"
#include "lua_map.h"
#include "lua_monsters.h"
#include "lua_player.h"
#include "lua_templates.h"
#include "map.h"
#include "monsters.h"
#include "player.h"
#include "screen.h"
#include "SoundManager.h"
#include "ViewControl.h"

#ifdef HAVE_LUA

struct Lua_Action_Flags {
	short index;
	static const char *name;
	static bool valid(int index) { return Lua_Players::valid(index); }
	
	static const luaL_reg metatable[];
	static const luaL_reg index_table[];
	static const luaL_reg newindex_table[];
};

const char *Lua_Action_Flags::name = "action_flags";

extern ModifiableActionQueues *GetGameQueue();

template<uint32 flag> 
static int get_action_flag_T(lua_State *L)
{
	int player_index = L_Index<Lua_Action_Flags>(L, 1);

	if (GetGameQueue()->countActionFlags(player_index))
	{
		uint32 flags = GetGameQueue()->peekActionFlags(player_index, 0);
		lua_pushboolean(L, flags & flag);
	}
	else
	{
		return luaL_error(L, "action flags are only accessible in idle()");
	}

	return 1;
}

template<uint32 flag> 
static int set_action_flag_T(lua_State *L)
{
	if (!lua_isboolean(L, 2))
		return luaL_error(L, "action flags: incorrect argument type");
	
	int player_index = L_Index<Lua_Action_Flags>(L, 1);
	if (GetGameQueue()->countActionFlags(player_index))
	{
		if (lua_toboolean(L, 2))
		{
			GetGameQueue()->modifyActionFlags(player_index, flag, flag);
		}
		else
		{
			GetGameQueue()->modifyActionFlags(player_index, 0, flag);
		}
	}
	else
	{
		return luaL_error(L, "action flags are only acessible in idle()");
	}

	return 0;
}

static int set_microphone_action_flag(lua_State *L)
{
	if (!lua_isboolean(L, 2))
		return luaL_error(L, "action flags: incorrect argument type");

	if (lua_toboolean(L, 2))
		return luaL_error(L, "you can only disable the microphone button flag");

	int player_index = L_Index<Lua_Action_Flags>(L, 1);
	if (GetGameQueue()->countActionFlags(player_index))
	{
		GetGameQueue()->modifyActionFlags(player_index, 0, _microphone_button);
	}
	else
	{
		return luaL_error(L, "action flags are only accessible in idle()");
	}

	return 0;
}

const luaL_reg Lua_Action_Flags::index_table[] = {
	{"action_trigger", get_action_flag_T<_action_trigger_state>},
	{"cycle_weapons_backward", get_action_flag_T<_cycle_weapons_backward>},
	{"cycle_weapons_forward", get_action_flag_T<_cycle_weapons_forward>},
	{"left_trigger", get_action_flag_T<_left_trigger_state>},
	{"microphone_button", get_action_flag_T<_microphone_button>},
	{"right_trigger", get_action_flag_T<_right_trigger_state>},
	{"toggle_map", get_action_flag_T<_toggle_map>},
	{0, 0}
};

const luaL_reg Lua_Action_Flags::newindex_table[] = {
	{"action_trigger", set_action_flag_T<_action_trigger_state>},
	{"cycle_weapons_backward", set_action_flag_T<_cycle_weapons_backward>},
	{"cycle_weapons_forward", set_action_flag_T<_cycle_weapons_forward>},
	{"left_trigger", set_action_flag_T<_left_trigger_state>},
	{"microphone_button", set_microphone_action_flag},
	{"right_trigger", set_action_flag_T<_right_trigger_state>},
	{"toggle_map", set_action_flag_T<_toggle_map>},
	{0, 0}
};

const luaL_reg Lua_Action_Flags::metatable[] = {
	{"__index", L_TableGet<Lua_Action_Flags>},
	{"__newindex", L_TableSet<Lua_Action_Flags>},
	{0, 0}
};

struct Lua_Side {
	short index;
	static bool valid(int index) { return true; }

	static const char *name;
	static const luaL_reg metatable[];
	static const luaL_reg index_table[];
	static const luaL_reg newindex_table[];
};

const char *Lua_Side::name = "side";

const luaL_reg Lua_Side::index_table[] = {
	{"index", L_TableIndex<Lua_Side>},
	{0, 0}
};

const luaL_reg Lua_Side::newindex_table[] = {
	{0, 0}
};

const luaL_reg Lua_Side::metatable[] = {
	{"__index", L_TableGet<Lua_Side>},
	{"__newindex", L_TableSet<Lua_Side>},
	{0, 0}
};

const char *Lua_Player::name = "player";

// methods

int Lua_Player_find_action_key_target(lua_State *L)
{
	// no arguments
	short target_type;
	short object_index = find_action_key_target(L_Index<Lua_Player>(L, 1), MAXIMUM_ACTIVATION_RANGE, &target_type);

	fprintf(stderr, "object index is %i\n", object_index);

	if (object_index != NONE)
	{
		switch (target_type)
		{
		case _target_is_platform:
			L_Push<Lua_Platform>(L, object_index);
			break;

		case _target_is_control_panel:
			L_Push<Lua_Side>(L, object_index);
			break;

		default:
			lua_pushnil(L);
			break;
		}
	}
	else
	{
		lua_pushnil(L);
	}

	return 1;
}

int Lua_Player_teleport(lua_State *L)
{
	if (!lua_isnumber(L, 2) && !L_Is<Lua_Polygon>(L, 2))
		return luaL_error(L, "teleport(): incorrect argument type");

	int destination = -1;
	if (lua_isnumber(L, 2))
		destination = static_cast<int>(lua_tonumber(L, 2));
	else 
		destination = L_Index<Lua_Polygon>(L, 2);

	int player_index = L_Index<Lua_Player>(L, 1);
	
	player_data *player = get_player_data(player_index);
	monster_data *monster = get_monster_data(player->monster_index);

	SET_PLAYER_TELEPORTING_STATUS(player, true);
	monster->action = _monster_is_teleporting;
	player->teleporting_phase = 0;
	player->delay_before_teleport = 0;

	player->teleporting_destination = destination;
	if (local_player_index == player_index)
		start_teleporting_effect(true);
	play_object_sound(player->object_index, Sound_TeleportOut());
	return 0;
}

int Lua_Player_teleport_to_level(lua_State *L)
{
	if (!lua_isnumber(L, 2))
		return luaL_error(L, "teleport_to_level(): incorrect argument type");

	int level = static_cast<int>(lua_tonumber(L, 2));
	int player_index = L_Index<Lua_Player>(L, 1);
	
	player_data *player = get_player_data(player_index);
	monster_data *monster = get_monster_data(player->monster_index);
	
	SET_PLAYER_TELEPORTING_STATUS(player, true);
	monster->action = _monster_is_teleporting;
	player->teleporting_phase = 0;
	player->delay_before_teleport = 0;

	player->teleporting_destination = -level - 1;
	if (View_DoInterlevelTeleportOutEffects()) {
		start_teleporting_effect(true);
		play_object_sound(player->object_index, Sound_TeleportOut());
	}
	return 0;
}

// get accessors

static int Lua_Player_get_action_flags(lua_State *L)
{
	L_Push<Lua_Action_Flags>(L, L_Index<Lua_Player>(L, 1));
	return 1;
}

static int Lua_Player_get_color(lua_State *L)
{
	lua_pushnumber(L, get_player_data(L_Index<Lua_Player>(L, 1))->color);
	return 1;
}

static int Lua_Player_get_dead(lua_State *L)
{
	player_data *player = get_player_data(L_Index<Lua_Player>(L, 1));
	lua_pushboolean(L, (PLAYER_IS_DEAD(player) || PLAYER_IS_TOTALLY_DEAD(player)));
	return 1;
}

static int Lua_Player_get_energy(lua_State *L)
{
	lua_pushnumber(L, get_player_data(L_Index<Lua_Player>(L, 1))->suit_energy);
	return 1;
}

static int Lua_Player_get_monster(lua_State *L)
{
	L_Push<Lua_Monster>(L, get_player_data(L_Index<Lua_Player>(L, 1))->monster_index);
	return 1;
}

static int Lua_Player_get_name(lua_State *L)
{
	lua_pushstring(L, get_player_data(L_Index<Lua_Player>(L, 1))->name);
	return 1;
}

static int Lua_Player_get_oxygen(lua_State *L)
{
	lua_pushnumber(L, get_player_data(L_Index<Lua_Player>(L, 1))->suit_oxygen);
	return 1;
}

static int Lua_Player_get_polygon(lua_State *L)
{
	L_Push<Lua_Polygon>(L, get_player_data(L_Index<Lua_Player>(L, 1))->supporting_polygon_index);
	return 1;
}

static int Lua_Player_get_team(lua_State *L)
{
	lua_pushnumber(L, get_player_data(L_Index<Lua_Player>(L, 1))->team);
	return 1;
}

static int Lua_Player_get_teleport(lua_State *L)
{
	lua_pushcfunction(L, Lua_Player_teleport);
	return 1;
}

static int Lua_Player_get_teleport_to_level(lua_State *L)
{
	lua_pushcfunction(L, Lua_Player_teleport_to_level);
	return 1;
}

const luaL_reg Lua_Player::index_table[] = {
	{"action_flags", Lua_Player_get_action_flags},
	{"color", Lua_Player_get_color},
	{"dead", Lua_Player_get_dead},
	{"energy", Lua_Player_get_energy},
	{"find_action_key_target", L_TableFunction<Lua_Player_find_action_key_target>},
	{"index", L_TableIndex<Lua_Player>},
	{"juice", Lua_Player_get_energy},
	{"life", Lua_Player_get_energy},
	{"monster", Lua_Player_get_monster},\
	{"name", Lua_Player_get_name},
	{"oxygen", Lua_Player_get_oxygen},
	{"polygon", Lua_Player_get_polygon},
	{"team", Lua_Player_get_team},
	{"teleport", L_TableFunction<Lua_Player_teleport>},
	{"teleport_to_level", L_TableFunction<Lua_Player_teleport_to_level>},
	{0, 0}
};

extern void mark_shield_display_as_dirty();

static int Lua_Player_set_color(lua_State *L)
{
	if (!lua_isnumber(L, 2))
	{
		return luaL_error(L, "color: incorrect argument type");
	}
	

	int color = static_cast<int>(lua_tonumber(L, 2));
	if (color < 0 || color > NUMBER_OF_TEAM_COLORS)
	{
		luaL_error(L, "player.color: invalid color");
	}
	get_player_data(L_Index<Lua_Player>(L, 1))->color = color;
	
	return 0;
}

static int Lua_Player_set_energy(lua_State *L)
{
	if (!lua_isnumber(L, 2))
		return luaL_error(L, "energy: incorrect argument type");

	int energy = static_cast<int>(lua_tonumber(L, 2));
	if (energy > 3 * PLAYER_MAXIMUM_SUIT_ENERGY)
		energy = 3 * PLAYER_MAXIMUM_SUIT_ENERGY;

	get_player_data(L_Index<Lua_Player>(L, 1))->suit_energy = energy;
	mark_shield_display_as_dirty();

	return 0;
}

static int Lua_Player_set_oxygen(lua_State *L)
{
	if (!lua_isnumber(L, 2))
		return luaL_error(L, "oxygen: incorrect argument type");
	
	int oxygen = static_cast<int>(lua_tonumber(L, 2));
	if (oxygen > PLAYER_MAXIMUM_SUIT_OXYGEN)
		oxygen = PLAYER_MAXIMUM_SUIT_OXYGEN;

	get_player_data(L_Index<Lua_Player>(L, 1))->suit_oxygen = oxygen;
	mark_shield_display_as_dirty();

	return 0;
}

static int Lua_Player_set_team(lua_State *L)
{
	if (!lua_isnumber(L, 2))
		return luaL_error(L, "team: incorrect argument type");

	int team = static_cast<int>(lua_tonumber(L, 2));
	if (team < 0 || team >= NUMBER_OF_TEAM_COLORS)
	{
		luaL_error(L, "player.team: invalid team");
	}
	get_player_data(L_Index<Lua_Player>(L, 1))->team = team;

	return 0;
}

const luaL_reg Lua_Player::newindex_table[] = {
	{"color", Lua_Player_set_color},
	{"energy", Lua_Player_set_energy},
	{"juice", Lua_Player_set_energy},
	{"life", Lua_Player_set_energy},
	{"oxygen", Lua_Player_set_oxygen},
	{"team", Lua_Player_set_team},
	{0, 0}
};

static int Lua_Player_tostring(lua_State *L)
{
	lua_pushfstring(L, "Player %d", L_Index<Lua_Player>(L, 1));
	return 1;
}

const luaL_reg Lua_Player::metatable[] = {
	{"__index", L_TableGet<Lua_Player>},
	{"__newindex", L_TableSet<Lua_Player>},
	{"__tostring", Lua_Player_tostring},
	{0, 0}
};

const char* Lua_Players::name = "Players";

const luaL_reg Lua_Players::methods[] = {
	{0, 0}
};

const luaL_reg Lua_Players::metatable[] = {
	{"__index", L_GlobalIndex<Lua_Players, Lua_Player>},
	{"__newindex", L_GlobalNewindex<Lua_Players>},
	{"__len", L_GlobalLength<Lua_Players>},
	{"__call", L_GlobalCall<Lua_Players, Lua_Player>},
	{0, 0}
};

static int Lua_Player_load_compatibility(lua_State *L);

int Lua_Player_register (lua_State *L)
{
	L_Register<Lua_Action_Flags>(L);
	L_Register<Lua_Player>(L);
	L_Register<Lua_Side>(L);

	L_GlobalRegister<Lua_Players>(L);
	
	Lua_Player_load_compatibility(L);
	
	return 0;
}

static const char *compatibility_script = ""
	"function get_life(player) return Players[player].energy end\n"
	"function get_oxygen(player) return Players[player].oxygen end\n"
	"function get_player_color(player) return Players[player].color end\n"
	"function get_player_name(player) return Players[player].name end\n"
	"function get_player_polygon(player) return Players[player].polygon.index end\n"
	"function get_player_team(player) return Players[player].team end\n"
	"function set_life(player, shield) Players[player].energy = shield end\n"
	"function number_of_players() return # Players end\n"
	"function player_is_dead(player) return Players[player].dead end\n"
	"function player_to_monster_index(player) return Players[player].monster.index end\n"
	"function set_oxygen(player, oxygen) Players[player].oxygen = oxygen end\n"
	"function set_player_color(player, color) Players[player].color = color end\n"
	"function set_player_team(player, team) Players[player].team = team end\n"
	"function teleport_player(player, polygon) Players[player]:teleport(polygon) end\n"
	"function teleport_player_to_level(player, level) Players[player]:teleport_to_level(level) end\n"
	;

static int Lua_Player_load_compatibility(lua_State *L)
{
	luaL_loadbuffer(L, compatibility_script, strlen(compatibility_script), "player_compatibility");
	lua_pcall(L, 0, 0, 0);
};

#endif