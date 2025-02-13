#ifndef zox_mod_voxels_chunks
#define zox_mod_voxels_chunks

zox_declare_tag(Chunk)
zox_declare_tag(NoiseChunk)
zox_declare_tag(ChunkDebugger)
zox_declare_tag(ColorChunk)
zox_declare_tag(ChunkTextured)
zox_declare_tag(LinkChunk)
zox_declare_tag(DisableReverseLinkChunk)
zox_component_byte(ChunkDirty)
zox_component_byte(ChunkMeshDirty)
zox_component_byte(ChunkLodDirty)
zox_component_byte(GenerateChunk)
zox_component_int3(ChunkPosition)
zox_component_int3(ChunkSize)
zox_component_byte(OctreeDepth)
zox_memory_component(ChunkNeighbors, ecs_entity_t)
zox_link_component(ChunkLink, ecs_entity_t, EntityLinks)
zox_hashmap_component(ChunkLinks, int3)
zox_component_byte(BlocksSpawned)
zoxel_octree_component(ChunkOctree, unsigned char, 0)
#include "data/settings.c"
#include "data/raycast_voxel_data.c"
#include "data/color_settings.c"
#include "data/trigger_states.c"
#include "data/chunk_dirty_state.c"
#include "data/chunk_lod_state.c"
#include "data/chunk_generate_states.c"
#include "util/chunk_lod.c"
#include "util/prefab_util.c"
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
#include "util/user_update.c"
#include "util/place_util.c"
#include "util/settings.c"
#include "prefabs/prefabs.c"
zox_increment_system_with_reset(ChunkDirty, chunk_dirty_state_end)
zox_increment_system_with_reset(ChunkMeshDirty, chunk_dirty_state_end)
zox_increment_system_with_reset(GenerateChunk, chunk_generate_state_end)
#include "systems/chunk_build_system.c"
#include "systems/chunk_link_system.c"
#include "systems/chunk_entities_lod_system.c"
#include "systems/chunk_blocks_lod_system.c"
#include "systems/chunk_entities_trigger_system.c"
#include "systems/chunk_debug_system.c"
#include "systems/chunk_find_neighbor_system.c"

zox_begin_module(Chunks)
    zox_define_tag(Chunk)
    zox_define_tag(NoiseChunk)
    zox_define_tag(ColorChunk)
    zox_define_tag(ChunkTextured)
    zox_define_tag(LinkChunk)
    zox_define_tag(DisableReverseLinkChunk)
    zox_define_tag(ChunkDebugger)
    zox_define_component_int3(ChunkPosition)
    zox_define_component_byte(ChunkDirty)
    zox_define_component_byte(ChunkMeshDirty)
    zox_define_component_byte(ChunkLodDirty)
    zox_define_component_int3(ChunkSize)
    zox_define_component_byte(GenerateChunk)
    zox_define_memory_component(ChunkNeighbors)
    zox_define_links_component(ChunkLink)
    zox_define_component_byte(OctreeDepth)
    zoxel_octree_component_define(ChunkOctree)
    zox_define_hashmap_component(ChunkLinks)
    zox_define_component_byte(BlocksSpawned)
    zox_define_component(RaycastVoxelData)
    zox_define_increment_system(ChunkDirty, EcsOnLoad)
    zox_define_increment_system(ChunkMeshDirty, EcsOnLoad)
    zox_define_increment_system(GenerateChunk, EcsOnLoad)
    // main thread
    zox_system_1(ChunkLinkSystem, zox_pip_mainthread, [in] VoxLink, [in] Position3D, [out] ChunkPosition, [out] ChunkLink, [none] LinkChunk)
    zox_system_1(ChunkDebugSystem, zox_pip_mainthread, [in] Position3D, [in] ChunkOctree, [in] RenderLod, [none] ChunkDebugger)
    // multithreads
    zox_system(ChunkEntitiesLodSystem, EcsOnUpdate, [in] ChunkLodDirty, [in] RenderDistance, [in] EntityLinks)
    zox_system(ChunkFindNeighborSystem, EcsOnLoad, [in] ChunkPosition, [in] VoxLink, [in] RenderLod, [out] ChunkNeighbors, [none] ChunkTextured)
    spawn_prefabs_chunks(world);
zox_end_module(Chunks)

#endif
