#ifndef zoxel_players3D
#define zoxel_players3D

zox_declare_tag(Player3D)
zox_declare_tag(PlayerCharacter3D)
#include "prefabs/player_character3D.c"
#include "util/player_character3D.c"
#include "util/attach3D.c"
#include "systems/player3D_move_system.c"
#include "systems/player3D_rotate_system.c"
#include "systems/player3D_jump_system.c"

void spawn_prefabs_players3D(ecs_world_t *world) {
    spawn_player_character3D_prefab(world);
}

zox_begin_module(Players3D)
zox_define_tag(Player3D)
zox_define_tag(PlayerCharacter3D)
#ifdef zoxel_physics3D
    zox_filter(player_characters, [none] PlayerCharacter3D, [out] Acceleration3D, [in] Velocity3D, [in] physics.DisableMovement, [in] Rotation3D)
    zox_filter(player_characters2, [none] PlayerCharacter3D, [out] Alpha3D, [in] Omega3D, [in] physics.DisableMovement)
    zox_system_ctx(Player3DMoveSystem, EcsPreUpdate, player_characters, [none] players.Player, [in] DeviceLinks, [in] CharacterLink)
    zox_system_ctx(Player3DRotateSystem, EcsPreUpdate, player_characters2, [none] players.Player, [in] DeviceLinks)
    zox_system(Player3DJumpSystem, EcsPreUpdate, [none] players.Player, [in] DeviceLinks, [in] CharacterLink)
#endif
zoxel_end_module(Players3D)

#endif