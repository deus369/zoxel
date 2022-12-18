#ifndef zoxel_inner_core
#define zoxel_inner_core

// --- Inner core ---
#include "textures/textures.c"
#include "audios/audios.c"
#include "ui/ui.c"
#include "lines/lines.c"
#include "neural/neural.c"
#include "animations/animations.c"
#include "physics/physics.c"
#include "tiles/tiles.c"
#include "voxels/voxels.c"

void close_inner_core()
{
    close_audio();
}

void InnerCoreImport(ecs_world_t *world)
{
    ECS_MODULE(world, InnerCore);
    ECS_IMPORT(world, Textures);
    ECS_IMPORT(world, Audios);
    ECS_IMPORT(world, UI);
    ECS_IMPORT(world, Lines);
    ECS_IMPORT(world, Neural);
    ECS_IMPORT(world, Animations);
    ECS_IMPORT(world, Physics);
    ECS_IMPORT(world, Tiles);
    ECS_IMPORT(world, Voxels);
}
#endif