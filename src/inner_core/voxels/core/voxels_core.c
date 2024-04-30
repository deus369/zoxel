#ifndef zoxel_voxels_core
#define zoxel_voxels_core

#define zox_pipeline_build_voxel_mesh EcsOnLoad // EcsPostUpdate
#include "settings/settings.c"
// zoxel_component_declares
zox_declare_tag(Voxel)
zox_declare_tag(ColorChunk)
zox_declare_tag(ChunkTextured)
zox_declare_tag(LinkChunk)
zox_component(ChunkSize, int3)
zox_component_byte(GenerateChunk)
zox_component_byte(ChunkDirty)
zox_memory_component(ChunkData, unsigned char)
zox_memory_component(ChunkNeighbors, ecs_entity_t)
zoxel_octree_component(ChunkOctree, unsigned char, 0)
zox_entities_component(VoxelLinks)
// zoxel_util_includes
#include "util/voxel_mesh_util.c"
#include "util/chunk_util.c"
#include "util/chunk_octree_util.c"
#include "util/chunk_build_util.c"
#include "util/voxel_util.c"
#include "util/vox_colors_util.c"
// zoxel_prefab_includes
#include "prefabs/voxel.c"
#include "prefabs/chunk.c"
#include "prefabs/noise_chunk.c"
// zoxel_fun_includes
#include "fun/test_noise_chunks.c"
// zoxel_system_includes
#include "systems/chunk_build_system.c"
#include "systems/chunk_link_system.c"

void spawn_prefabs_voxels_core(ecs_world_t *world) {
    spawn_prefab_voxel(world);
    spawn_prefab_chunk(world);
    spawn_prefab_noise_chunk(world);
}

zox_begin_module(VoxelsCore)
// zoxel_settings_defines
set_max_octree_length(max_octree_depth);
// zoxel_component_defines
zox_define_tag(Voxel)
zox_define_tag(ColorChunk)
zox_define_tag(ChunkTextured)
zox_define_tag(LinkChunk)
zox_define_component(ChunkDirty)
zox_define_component(ChunkSize)
zox_define_component(GenerateChunk)
zox_define_memory_component(ChunkData)
zox_define_memory_component(ChunkNeighbors)
zoxel_octree_component_define(ChunkOctree)
zox_define_entities_component(VoxelLinks)
// zoxel_system_defines
zox_system(ChunkLinkSystem, EcsOnUpdate, [none] LinkChunk, [in] VoxLink, [in] Position3D, [out] ChunkPosition, [out] ChunkLink) // EcsPostUpdate
zoxel_end_module(VoxelsCore)

#endif
