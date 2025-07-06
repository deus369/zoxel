#include "player_character2D.c"

void spawn_prefabs_players2D(ecs_world_t *world) {
    prefab_player_character2D = spawn_prefab_player_character2D(world, prefab_character2D);
    prefab_start_game2D_player = prefab_player_character2D;
}