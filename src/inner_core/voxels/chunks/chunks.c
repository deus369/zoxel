#ifndef zox_mod_voxels_chunks
#define zox_mod_voxels_chunks

zox_declare_tag(Chunk)
zox_declare_tag(NoiseChunk)
zox_component_int3(ChunkPosition)
zox_declare_tag(ColorChunk)
zox_declare_tag(ChunkTextured)
zox_declare_tag(LinkChunk)
zox_declare_tag(DisableReverseLinkChunk)
zox_component_int3(ChunkSize)
zox_component_byte(ChunkDirty)
zox_component_byte(ChunkLodDirty)
zox_component_byte(GenerateChunk)
zox_memory_component(ChunkData, unsigned char)
zox_memory_component(ChunkNeighbors, ecs_entity_t)
zox_link_component(ChunkLink, ecs_entity_t, EntityLinks)
zox_hashmap_component(ChunkLinks, int3)
zox_hashmap_component(BlockSpawns, byte3)
zoxel_octree_component(ChunkOctree, unsigned char, 0)
#include "data/settings.c"
#include "data/raycast_voxel_data.c"
#include "data/color_settings.c"
#include "data/trigger_states.c"
#include "data/chunk_dirty_state.c"
#include "data/chunk_lod_state.c"
#include "util/voxel_mesh_util.c"
#include "util/chunk_util.c"
#include "util/chunk_octree_util.c"
#include "util/octree_set_util.c"
#include "util/chunk_build_util.c"
#include "util/voxel_util.c"
#include "util/vox_colors_util.c"
#include "util/link_util.c"
#include "util/label_util.c"
#include "util/raycast_single_vox.c"
#include "util/raycast.c"
#include "util/place_util.c"
#include "util/settings.c"
#include "prefabs/prefabs.c"
zox_increment_system_with_reset(ChunkLodDirty, chunk_lod_state_end)
#include "systems/chunk_build_system.c"
#include "systems/chunk_link_system.c"
#include "systems/chunk_entities_lod_system.c"
#include "systems/chunk_blocks_lod_system.c"
#include "systems/chunk_entities_trigger_system.c"

zox_begin_module(Chunks)
zox_define_tag(Chunk)
zox_define_tag(NoiseChunk)
zox_define_tag(ColorChunk)
zox_define_tag(ChunkTextured)
zox_define_tag(LinkChunk)
zox_define_tag(DisableReverseLinkChunk)
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
zox_define_component(RaycastVoxelData)
zox_system(ChunkLinkSystem, zox_pip_voxels, [in] VoxLink, [in] Position3D, [out] ChunkPosition, [out] ChunkLink, [none] LinkChunk)
zox_system(ChunkEntitiesLodSystem, zox_pip_voxels, [in] ChunkLodDirty, [in] RenderLod, [in] EntityLinks)
zox_system(ChunkBlocksLodSystem, zox_pip_voxels, [in] ChunkLodDirty, [in] RenderLod, [in] BlockSpawns)
zox_define_increment_system(ChunkLodDirty, EcsOnLoad)
spawn_prefabs_chunks(world);
zoxel_end_module(Chunks)

#endif
