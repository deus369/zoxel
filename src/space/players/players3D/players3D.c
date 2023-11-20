#ifndef zoxel_players3D
#define zoxel_players3D

// zoxel_component_declares
zox_declare_tag(Player3D)
zox_declare_tag(PlayerCharacter3D)
// zoxel_prefab_includes
#include "prefabs/player_character3D.c"
// zoxel_util_includes
#include "util/player_character3D.c"
#include "util/attach3D.c"
// zoxel_system_includes
#include "systems/player3D_move_system.c"
#include "systems/player3D_rotate_system.c"
#include "systems/player3D_jump_system.c"

void spawn_prefabs_players3D(ecs_world_t *world) {
    spawn_prefab_player_character3D(world);
}

zox_begin_module(Players3D)
// zoxel_component_defines
zox_define_tag(Player3D)
zox_define_tag(PlayerCharacter3D)
// zoxel_system_defines
#ifdef zoxel_physics3D
zox_system(Player3DMoveSystem, EcsPreUpdate, [none] players.Player, [in] DeviceLinks, [in] DeviceMode, [in] CharacterLink)
zox_system(Player3DRotateSystem, EcsPreUpdate, [none] players.Player, [in] DeviceLinks, [in] CharacterLink, [in] CameraLink)
zox_system(Player3DJumpSystem, EcsPreUpdate, [none] players.Player, [in] DeviceLinks, [in] CharacterLink)
#endif
zoxel_end_module(Players3D)

#endif
