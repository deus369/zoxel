#include "player_character3D.c"

void spawn_prefabs_players3D(ecs_world_t *world) {
    prefab_character3D_player = spawn_prefab_player_character3D(world, prefab_character3D);
}
