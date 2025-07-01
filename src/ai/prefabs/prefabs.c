#include "character3D_npc.c"

void spawn_prefabs_ai(ecs_world_t *world) {
    prefab_character3D_npc = spawn_prefab_character3D_npc(world, prefab_character3D);
    // link to terrain spawning
    prefab_character3D_terrain_spawning = prefab_character3D_npc;
}