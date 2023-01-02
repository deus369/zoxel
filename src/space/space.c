#ifndef zoxel_space
#define zoxel_space

#include "players/players.c"
#include "realms/realms.c"
#include "games/games.c"

void SpaceImport(ecs_world_t *world)
{
    zoxel_module(Space)
    if (!headless)
    {
        zoxel_import_module(Players)
    }
    zoxel_import_module(Realms)
    zoxel_import_module(Games)
}
#endif