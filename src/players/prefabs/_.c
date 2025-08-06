#include "player.c"
ecs_entity_t prefab_player;

void spawn_prefabs_players(ecs_world_t *world) {
    prefab_player = spawn_prefab_player(world);

    zox_prefab_set_device(PlayerLink, { 0 });
    if (prefab_game) {
        zox_prefab_add(prefab_game, PlayerLinks);
    }
}
