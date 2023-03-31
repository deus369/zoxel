#ifndef zoxel_voxels
#define zoxel_voxels

bool disable_chunk_systems;
zoxel_declare_tag(Chunk)
zoxel_declare_tag(NoiseChunk)
zoxel_component(ChunkPosition, int3)
zoxel_component(VoxelPosition, int3)
zoxel_component(VoxLink, ecs_entity_t)
zoxel_component(ChunkLink, ecs_entity_t)
#include "core/core_voxels.c"
#include "terrain/terrain.c"
#include "vox/vox.c"

zoxel_begin_module(Voxels)
zoxel_define_tag(Chunk)
zoxel_define_tag(NoiseChunk)
zoxel_define_component(ChunkPosition)
zoxel_define_component(VoxelPosition)
zoxel_define_component(VoxLink)
zoxel_define_component(ChunkLink)
zoxel_import_module(VoxelsCore)
zoxel_import_module(Vox)
zoxel_import_module(Terrain)
zoxel_end_module(Voxels)

#endif