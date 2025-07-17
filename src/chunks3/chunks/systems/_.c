zox_increment_system_with_reset(ChunkDirty, chunk_dirty_state_end)
zox_increment_system_with_reset(ChunkMeshDirty, chunk_dirty_state_end)
zox_increment_system_with_reset(GenerateChunk, chunk_generate_state_end)
zox_increment_system_with_reset(ChunkLodDirty, chunk_lod_state_end)
#include "chunk_link_system.c"
#include "chunk_entities_lod_system.c"
#include "chunk_debug_system.c"
#include "chunk_find_neighbor_system.c"

void define_systems_chunks(ecs_world_t *world) {
    zox_define_increment_system(ChunkDirty, EcsOnLoad)
    zox_define_increment_system(ChunkMeshDirty, EcsOnLoad)
    zox_define_increment_system(GenerateChunk, EcsOnLoad)
    zox_define_increment_system(ChunkLodDirty, EcsOnLoad)
    zox_system(ChunkLinkSystem, EcsOnUpdate,
        [in] chunks3.VoxLink,
        [in] transforms3.Position3D,
        [out] chunks3.ChunkPosition,
        [out] chunks3.ChunkLink,
        [none] LinkChunk)
    zox_system(ChunkEntitiesLodSystem, EcsOnUpdate,
        [in] chunks3.ChunkLodDirty,
        [in] rendering.RenderDistance,
        [in] generic.EntityLinks)
    zox_system(ChunkFindNeighborSystem, EcsOnLoad,
        [in] chunks3.ChunkPosition,
        [in] chunks3.VoxLink,
        [in] rendering.RenderLod,
        [out] chunks3.ChunkNeighbors,
        [none] ChunkTextured)
    // main thread
    zox_system_1(ChunkDebugSystem, zox_pip_mainthread,
        [in] transforms3.Position3D,
        [in] chunks3.VoxelNode,
        [in] chunks3.NodeDepth,
        [in] rendering.RenderDistance,
        [none] ChunkDebugger)
}