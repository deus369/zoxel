#ifndef zoxel_players2D
#define zoxel_players2D

// zoxel_component_declares
zox_declare_tag(Player2D)
zox_declare_tag(PlayerCharacter2D)
// zoxel_prefab_includes
#include "prefabs/player_character2D.c"
// zoxel_util_includes
// zoxel_system_includes
#include "systems/player2D_move_system.c"

void spawn_prefabs_players2D(ecs_world_t *world) {
    spawn_prefab_player_character2D(world);
}

zox_begin_module(Players2D)
// zoxel_component_defines
zox_define_tag(Player2D)
zox_define_tag(PlayerCharacter2D)
// zoxel_system_defines
#ifdef zoxel_physics2D
    zox_system(Player2DMoveSystem, EcsPreUpdate, [none] players.Player, [in] DeviceLinks, [in] CharacterLink)
#endif
zoxel_end_module(Players2D)

#endif