#ifndef zox_mod_controllers2D
#define zox_mod_controllers2D

#include "data/settings.c"
zox_declare_tag(Player2D)
zox_declare_tag(PlayerCharacter2D)
#include "prefabs/_.c"
#include "systems/player2D_move_system.c"
#include "util/label.c"

zox_begin_module(Controllers2D)
    zox_define_tag(Player2D)
    zox_define_tag(PlayerCharacter2D)
    zox_system(Player2DMoveSystem, zox_pip_player_movement, [in] DeviceLinks, [in] CharacterLink, [none] players.Player)
    spawn_prefabs_players2D(world);
zox_end_module(Controllers2D)

#endif