#ifndef zox_voxels_chunks
#define zox_voxels_chunks

// core to any voxel model is chunks
#include "data/settings.c"
zox_declare_tag(Chunk)
zox_declare_tag(NoiseChunk)
zox_component_int3(ChunkPosition)
zox_declare_tag(ColorChunk)
zox_declare_tag(ChunkTextured)
zox_declare_tag(LinkChunk)
zox_declare_tag(DisableReverseLinkChunk)
zox_component_int3(ChunkSize)
zox_component_byte(GenerateChunk)
zox_component_byte(ChunkDirty)
zox_component_byte(ChunkLodDirty)
zox_component_entity(VoxLink)
zox_memory_component(ChunkData, unsigned char)
zox_memory_component(ChunkNeighbors, ecs_entity_t)
zoxel_octree_component(ChunkOctree, unsigned char, 0)
zox_link_component(ChunkLink, ecs_entity_t, EntityLinks)
zox_hashmap_component(ChunkLinks, int3)
zox_hashmap_component(BlockSpawns, byte3)
#include "util/voxel_mesh_util.c"
#include "util/chunk_util.c"
#include "util/chunk_octree_util.c"
#include "util/chunk_build_util.c"
#include "util/voxel_util.c"
#include "util/vox_colors_util.c"
#include "util/link_util.c"
#include "util/label_util.c"
#include "prefabs/prefabs.c"
#include "systems/chunk_build_system.c"
#include "systems/chunk_link_system.c"

zox_begin_module(Chunks)
zox_define_tag(Chunk)
zox_define_tag(NoiseChunk)
zox_define_tag(ColorChunk)
zox_define_tag(ChunkTextured)
zox_define_tag(LinkChunk)
zox_define_tag(DisableReverseLinkChunk)
zox_define_component_entity(VoxLink)
zox_define_component_int3(ChunkPosition)
zox_define_component_byte(ChunkDirty)
zox_define_component_byte(ChunkLodDirty)
zox_define_component_int3(ChunkSize)
zox_define_component_byte(GenerateChunk)
zox_define_memory_component(ChunkData)
zox_define_memory_component(ChunkNeighbors)
zox_define_links_component(ChunkLink)
zoxel_octree_component_define(ChunkOctree)
zox_define_hashmap_component(ChunkLinks)
zox_define_hashmap_component(BlockSpawns)
zox_system(ChunkLinkSystem, zox_pip_voxels, [in] VoxLink, [in] Position3D, [out] ChunkPosition, [out] ChunkLink, [none] LinkChunk)
zoxel_end_module(Chunks)

#endif
