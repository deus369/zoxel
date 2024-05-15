#ifndef _zox_players3D
#define _zox_players3D

#include "data/settings.c"
zox_declare_tag(Player3D)
zox_declare_tag(PlayerCharacter3D)
#include "prefabs/player_character3D.c"
#include "util/player_character3D.c"
#include "util/attach3D.c"
#include "systems/player3D_move_system.c"
#include "systems/player3D_rotate_system.c"
#include "systems/player3D_jump_system.c"

int get_label_player_character3D(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t character2D = zox_get_value(player, CharacterLink)
    if (!character2D || !zox_has(character2D, Position3D)) return buffer_index;
    const float3 position3D = zox_get_value(character2D, Position3D)
    buffer_index += snprintf(buffer + buffer_index, buffer_size, "player [%ix%ix%i]\n", (int) position3D.x, (int) position3D.y, (int) position3D.z);
    return buffer_index;
}

void spawn_prefabs_players3D(ecs_world_t *world) {
    spawn_prefab_player_character3D(world);
}

zox_begin_module(Players3D)
zox_define_tag(Player3D)
zox_define_tag(PlayerCharacter3D)
#ifdef zoxel_physics3D
zox_system(Player3DMoveSystem, zox_pip_player_movement, [in] DeviceLinks, [in] DeviceMode, [in] CharacterLink, [none] players.Player)
zox_system(Player3DRotateSystem, zox_pip_player_movement, [in] DeviceLinks, [in] DeviceMode, [in] CharacterLink, [in] CameraLink, [none] players.Player)
zox_system(Player3DJumpSystem, zox_pip_player_movement, [in] DeviceLinks, [in] DeviceMode, [in] CharacterLink, [none] players.Player)
#endif
zoxel_end_module(Players3D)

#endif
