#include "player.c"

void spawn_prefabs_players2(ecs_world_t *world) {
    zox_prefab_add(prefab_game, PlayerLinks)
    zox_prefab_set(prefab_player, PlayerPauseEvent, { 0 })
}