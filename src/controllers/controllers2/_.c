#ifndef zoxm_controllers2D
#define zoxm_controllers2D

// todo: movement should be done in one system, and we can use a Move float2 in our character - Movement2 and Movement3 - should be a float -1 to 1, and determine intention to move
#include "data/settings.c"
zox_tag(Player2D);
zox_tag(PlayerCharacter2D);
zoxc_float2(Movement2);
#include "prefabs/_.c"
#include "systems/controller2_move_system.c"
#include "util/label.c"

zox_begin_module(Controllers2)
    zox_define_tag(Player2D);
    zox_define_tag(PlayerCharacter2D);
    zox_define_component_float2(Movement2);
    zox_system(Controller2MoveSystem, EcsOnUpdate,
        [in] inputs.DeviceLinks,
        [in] characters.CharacterLink,
        [none] players.Player);
    add_hook_spawn_prefabs(spawn_prefabs_players2D);
zox_end_module(Controllers2)

#endif