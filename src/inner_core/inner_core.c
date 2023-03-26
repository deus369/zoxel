#ifndef zoxel_inner_core
#define zoxel_inner_core

#include "blueprints/blueprints.c"
#include "textures/textures.c"
#include "musics/musics.c"
#include "ui/ui.c"
#include "lines/lines.c"
#include "neural/neural.c"
#include "animations/animations.c"
#include "physics/physics.c"
#include "tiles/tiles.c"
#include "voxels/voxels.c"

zoxel_begin_module(InnerCore)
zoxel_import_module(Textures)
zoxel_import_module(Musics)
zoxel_import_module(UI)
zoxel_import_module(Lines)
zoxel_import_module(Neural)
zoxel_import_module(Animations)
zoxel_import_module(Tiles)
zoxel_import_module(Voxels)
zoxel_import_module(Physics)
zoxel_import_module(Blueprints)
zoxel_end_module(InnerCore)
#endif