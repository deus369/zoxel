#ifndef zoxel_voxels
#define zoxel_voxels

bool disable_chunk_systems;
#include "core/core.c"
#include "terrain/terrain.c"
#include "vox/vox.c"

zoxel_begin_module(Voxels)
zoxel_import_module(VoxelsCore)
zoxel_import_module(Vox)
zoxel_import_module(Terrain)
zoxel_end_module(Voxels)

#endif