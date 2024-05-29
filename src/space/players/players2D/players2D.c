#ifndef _zox_players2D
#define _zox_players2D

zox_declare_tag(Player2D)
zox_declare_tag(PlayerCharacter2D)
#include "prefabs/player_character2D.c"
#include "systems/player2D_move_system.c"

int get_label_player_character2D(ecs_world_t *world, const ecs_entity_t player, char buffer[], int buffer_size, int buffer_index) {
    const ecs_entity_t character2D = zox_get_value(player, CharacterLink)
    if (!character2D || !zox_has(character2D, Position2D)) return buffer_index;
    const float2 position2D = zox_get_value(character2D, Position2D)
    buffer_index += snprintf(buffer + buffer_index, buffer_size, "player [%ix%i]\n", (int) position2D.x, (int) position2D.y);
    return buffer_index;
}

void spawn_prefabs_players2D(ecs_world_t *world) {
    spawn_prefab_player_character2D(world);
}

zox_begin_module(Players2D)
zox_define_tag(Player2D)
zox_define_tag(PlayerCharacter2D)
zox_system(Player2DMoveSystem, zox_pip_player_movement, [in] DeviceLinks, [in] CharacterLink, [none] players.Player)
spawn_prefabs_players2D(world);
zoxel_end_module(Players2D)

#endif
