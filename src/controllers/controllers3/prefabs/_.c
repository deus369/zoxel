#include "character3_player.c"
ecs_entity_t prefab_character3_player;

void spawn_prefabs_players3D(ecs_world_t *world) {
    prefab_character3_player = spawn_prefab_character3_player(world, prefab_character3);
    prefabs_characters3[prefab_characters_count++] = prefab_character3_player;
}
