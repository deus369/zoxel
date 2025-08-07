#include "character2_player.c"
ecs_entity_t prefab_player_character2D;

void spawn_prefabs_players2D(ecs_world_t *world) {
    prefab_player_character2D = spawn_prefab_character2_player(world, prefab_character2D);
    prefab_game2_player = prefab_player_character2D;
}