zox_increment_system_with_reset(ChunkDirty, chunk_dirty_state_end)
zox_increment_system_with_reset(ChunkMeshDirty, chunk_dirty_state_end)
zox_increment_system_with_reset(GenerateChunk, chunk_generate_state_end)zox_increment_system_with_reset(ChunkLodDirty, chunk_lod_state_end)
#include "chunk_link_system.c"
#include "chunk_entities_lod_system.c"
#include "chunk_entities_trigger_system.c"
#include "chunk_debug_system.c"
#include "chunk_find_neighbor_system.c"

void define_systems_chunks(ecs_world_t *world) {
    zox_define_increment_system(ChunkDirty, EcsOnLoad)
    zox_define_increment_system(ChunkMeshDirty, EcsOnLoad)
    zox_define_increment_system(GenerateChunk, EcsOnLoad)
    zox_define_increment_system(ChunkLodDirty, EcsOnLoad)
    // _1 zox_pip_mainthread
    zox_system(ChunkLinkSystem, EcsOnUpdate, [in] voxels.VoxLink, [in] transforms3.d.Position3D, [out] chunks.ChunkPosition, [out] chunks.ChunkLink, [none] LinkChunk)
    // main thread
    zox_system_1(ChunkDebugSystem, zox_pip_mainthread, [in] transforms3.d.Position3D, [in] chunks.ChunkOctree, [in] rendering.RenderLod, [none] ChunkDebugger)
    // multithreads
    zox_system(ChunkEntitiesLodSystem, EcsOnUpdate, [in] chunks.ChunkLodDirty, [in] rendering.RenderDistance, [in] generic.EntityLinks)
    zox_system(ChunkFindNeighborSystem, EcsOnLoad, [in] chunks.ChunkPosition, [in] voxels.VoxLink, [in] rendering.RenderLod, [out] chunks.ChunkNeighbors, [none] ChunkTextured)
}