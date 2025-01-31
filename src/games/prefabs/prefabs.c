ecs_entity_t prefab_game;
#include "game.c"

void spawn_prefabs_games(ecs_world_t *world) {
    prefab_game = spawn_prefab_game(world);
    zox_prefab_add(prefab_player, GameLink)
}
