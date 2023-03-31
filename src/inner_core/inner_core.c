#ifndef zoxel_inner_core
#define zoxel_inner_core

#include "textures/textures.c"
#include "musics/musics.c"
#include "animations/animations.c"
#include "ui/ui.c"
#include "lines/lines.c"
#include "blueprints/blueprints.c"
#include "genetics/genetics.c"
#include "neurals/neurals.c"
#include "tiles/tiles.c"
#include "voxels/voxels.c"
#include "physics/physics.c"

zoxel_begin_module(InnerCore)
zoxel_import_module(Textures)
zoxel_import_module(Musics)
zoxel_import_module(Animations)
zoxel_import_module(UI)
zoxel_import_module(Lines)
zoxel_import_module(Blueprints)
zoxel_import_module(Genetics)
zoxel_import_module(Neurals)
zoxel_import_module(Tiles)
zoxel_import_module(Voxels)
zoxel_import_module(Physics)
zoxel_end_module(InnerCore)

#endif