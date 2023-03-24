#ifndef zoxel_voxels
#define zoxel_voxels

bool disable_chunk_systems;

#include "core/core.c"
#include "terrain/terrain.c"
#include "vox/vox.c"

void VoxelsImport(ecs_world_t *world) {
    zoxel_log("         > importing voxels\n");
    zoxel_module(Voxels)
    zoxel_import_module(VoxelsCore)
    zoxel_import_module(Vox)
    zoxel_import_module(Terrain)
    zoxel_log("         > imported voxels\n");
}
#endif