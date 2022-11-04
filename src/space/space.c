#ifndef zoxel_space
#define zoxel_space

// --- Space ---
#include "players/players.c"
#include "realms/realms.c"

void SpaceImport(ecs_world_t *world)
{
    ECS_MODULE(world, Space);
    ECS_IMPORT(world, Players);
    // ECS_IMPORT(world, Realms);
}
#endif