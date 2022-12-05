#ifndef zoxel_game
#define zoxel_game

// --- util ---
#include "util/ui.c"
#include "util/boot.c"

void ZoxelImport(ecs_world_t *world)
{
    // zoxel_log("Importing [Zoxel Game]\n");
    ECS_MODULE(world, Zoxel);
    ECS_IMPORT(world, ZoxelEngine); // import engine
    boot_zoxel_game(world);        // spawn game entities
}
#endif