#include "character3_player.c"

void spawn_prefabs_players3D(ecs_world_t *world) {
    prefab_character3D_player = spawn_prefab_character3_player(world, prefab_character3D);
}
