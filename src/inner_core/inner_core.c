#ifndef zoxel_inner_core
#define zoxel_inner_core

// --- Inner core ---
#include "animations/animations.c"
#include "audios/audios.c"
#include "physics/physics.c"
#include "textures/textures.c"
#include "tiles/tiles.c"
#include "voxels/voxels.c"

extern bool headless;

void update_inner_core()
{
    if (!headless)
    {
        texture_update_main_thread();  // uploads textures to gpu
    }
}

void close_inner_core()
{
    close_audio();
}

void InnerCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, InnerCore);
    ECS_IMPORT(world, Animations);
    ECS_IMPORT(world, Audios);
    ECS_IMPORT(world, Textures);
    ECS_IMPORT(world, Physics);
    ECS_IMPORT(world, Tiles);
    ECS_IMPORT(world, Voxels);
}
#endif