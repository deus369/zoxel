#ifndef zoxel_game
#define zoxel_game

#ifdef zoxel_ui
    #include "util/zoxel_ui.c"
#endif
#include "util/boot.c"

void ZoxelImport(ecs_world_t *world) {
    // zoxel_log("Importing [Zoxel Game]\n");
    ECS_MODULE(world, Zoxel);
    ECS_IMPORT(world, ZoxelEngine); // import engine
}
#endif