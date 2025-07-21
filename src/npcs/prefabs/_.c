#include "character3D_npc.c"

void spawn_prefabs_npcs(ecs_world_t *world) {
    prefab_character3_npc = spawn_prefab_character3_npc(world, prefab_character3);
    // link to terrain spawning
    prefab_character3_terrain_spawning = prefab_character3_npc;
}