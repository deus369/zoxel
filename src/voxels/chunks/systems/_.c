zox_increment_system_with_reset(ChunkDirty, chunk_dirty_state_end)
zox_increment_system_with_reset(ChunkMeshDirty, chunk_dirty_state_end)
zox_increment_system_with_reset(GenerateChunk, chunk_generate_state_end)
#include "chunk_link_system.c"
#include "chunk_entities_lod_system.c"
#include "chunk_entities_trigger_system.c"
#include "chunk_debug_system.c"
#include "chunk_find_neighbor_system.c"

void zox_define_systems_chunks(ecs_world_t *world) {
    zox_define_increment_system(ChunkDirty, EcsOnLoad)
    zox_define_increment_system(ChunkMeshDirty, EcsOnLoad)
    zox_define_increment_system(GenerateChunk, EcsOnLoad)
    // main thread
    zox_system_1(ChunkLinkSystem, zox_pip_mainthread, [in] VoxLink, [in] Position3D, [out] ChunkPosition, [out] ChunkLink, [none] LinkChunk)
    zox_system_1(ChunkDebugSystem, zox_pip_mainthread, [in] Position3D, [in] ChunkOctree, [in] RenderLod, [none] ChunkDebugger)
    // multithreads
    zox_system(ChunkEntitiesLodSystem, EcsOnUpdate, [in] ChunkLodDirty, [in] RenderDistance, [in] EntityLinks)
    zox_system(ChunkFindNeighborSystem, EcsOnLoad, [in] ChunkPosition, [in] VoxLink, [in] RenderLod, [out] ChunkNeighbors, [none] ChunkTextured)
}