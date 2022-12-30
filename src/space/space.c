#ifndef zoxel_space
#define zoxel_space

// --- Space ---
#include "players/players.c"
#include "realms/realms.c"
#include "games/games.c"

void SpaceImport(ecs_world_t *world)
{
    ECS_MODULE(world, Space);
    if (!headless)
    {
        ECS_IMPORT(world, Players);
    }
    ECS_IMPORT(world, Realms);
    ECS_IMPORT(world, Games);
}
#endif