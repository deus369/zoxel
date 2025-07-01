ecs_entity_t prefab_chunk_streaming;

zox_increment_system_with_reset(ChunkLodDirty, chunk_lod_state_end)
zox_increment_system_with_reset(StreamDirty, zox_general_state_end)
#include "stream_point_system.c"
#include "chunk_lod_dirty_system.c"
#include "chunk_lod_system.c"
#include "chunk_neighbor_updated_system.c"
#include "chunk_frustum_system.c"
#include "stream_end_event_system.c"
#include "chunk_spawn_system.c"
#include "chunk_die_system.c"

void define_systems_streaming(ecs_world_t *world) {
    zox_filter(filter_cameras, [in] generic.Position3DBounds, [in] cameras.CameraPlanes, [none] cameras.Camera3D)
    zox_define_increment_system(ChunkLodDirty, EcsOnLoad)
    zox_define_increment_system(StreamDirty, EcsOnLoad)
    // main thread
    zox_system_1(StreamEndEventSystem, zox_pip_mainthread, [in] EventInput, [in] ChunkLinks, [out] StreamEndEvent)
    // multi threads
    zox_system(StreamPointSystem, EcsOnUpdate, [in] Position3D, [in] VoxLink, [out] StreamPoint, [out] StreamDirty, [none] Streamer)
    zox_system_ctx(ChunkFrustumSystem, EcsOnUpdate, filter_cameras, [in] Position3D, [in] ChunkSize, [in] VoxScale, [in] EntityLinks, [in] ChunkOctree, [out] RenderDisabled, [none] StreamedChunk)
    zox_filter(streamers2, [in] StreamPoint, [in] StreamDirty)
    zox_system_ctx(ChunkLodSystem, EcsOnUpdate, streamers2, [in] ChunkPosition, [out] RenderLod, [out] ChunkLodDirty, [out] RenderDistance, [none] StreamedChunk)
    zox_system(ChunkLodDirtySystem, EcsOnUpdate, [in] ChunkLodDirty, [out] GenerateChunk, [out] ChunkMeshDirty, [none] StreamedChunk)
    zox_system(ChunkNeighborUpdatedSystem, EcsPostUpdate, [in] ChunkNeighbors, [out] ChunkMeshDirty, [none] StreamedChunk)

    // streams
    zox_filter(streamers, [in] StreamPoint)
    zox_system_ctx_1(ChunkSpawnSystem, zox_pip_mainthread, streamers, [in] ChunkPosition, [in] VoxLink, [in] RenderDistance, [out] ChunkNeighbors, [none] StreamedChunk)
    zox_system(ChunkDieSystem, EcsOnStore, [in] VoxLink, [in] ChunkPosition, [in] RenderDistance, [in] ChunkLodDirty, [in] RenderLod, [none] StreamedChunk)
}