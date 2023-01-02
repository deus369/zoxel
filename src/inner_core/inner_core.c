#ifndef zoxel_inner_core
#define zoxel_inner_core

#include "textures/textures.c"
#include "audios/audios.c"
#include "ui/ui.c"
#include "lines/lines.c"
#include "neural/neural.c"
#include "animations/animations.c"
#include "physics/physics.c"
#include "tiles/tiles.c"
#include "voxels/voxels.c"
#include "blueprints/blueprints.c"

void close_inner_core()
{
    close_audio();
}

void InnerCoreImport(ecs_world_t *world)
{
    zoxel_module(InnerCore)
    zoxel_import_module(Textures)
    zoxel_import_module(Audios)
    zoxel_import_module(UI)
    zoxel_import_module(Lines)
    zoxel_import_module(Neural)
    zoxel_import_module(Animations)
    zoxel_import_module(Physics)
    zoxel_import_module(Tiles)
    zoxel_import_module(Voxels)
    zoxel_import_module(Blueprints)
}
#endif