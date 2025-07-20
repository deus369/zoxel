
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
    zox_define_increment_system(StreamDirty, EcsOnLoad)
    zox_system(StreamPointSystem, EcsOnUpdate,
        [in] transforms3.Position3D,
        [in] chunks3.VoxLink,
        [out] StreamPoint,
        [out] StreamDirty,
        [none] Streamer)
    zox_filter(filter_cameras,
        [in] generic.Position3DBounds,
        [in] cameras.CameraPlanes,
        [none] cameras.Camera3D)
    zox_system_ctx(ChunkFrustumSystem, EcsOnUpdate, filter_cameras,
        [in] transforms3.Position3D,
        [in] chunks3.ChunkSize,
        [in] blocks.VoxScale,
        [in] generic.EntityLinks,
        [in] chunks3.VoxelNode,
        [in] chunks3.NodeDepth,
        [out] rendering.RenderDisabled,
        [none] StreamedChunk)
    zox_filter(streamers2,
        [in] StreamPoint,
        [in] StreamDirty)
    zox_system_ctx(ChunkLodSystem, EcsOnUpdate, streamers2,
        [in] chunks3.ChunkPosition,
        [out] rendering.RenderLod,
        [out] chunks3.ChunkLodDirty,
        [out] rendering.RenderDistance,
        [out] rendering.RenderDistanceDirty,
        [none] StreamedChunk)
    zox_system(ChunkLodDirtySystem, EcsOnUpdate,
        [in] chunks3.ChunkLodDirty,
        [in] rendering.RenderLod,
        [out] chunks3.GenerateChunk,
        [out] chunks3.ChunkMeshDirty,
        [none] StreamedChunk)
    zox_system(ChunkNeighborUpdatedSystem, EcsPostUpdate,
        [in] chunks3.ChunkNeighbors,
        [out] chunks3.ChunkMeshDirty,
        [none] StreamedChunk)
    // streams
    zox_system(ChunkDieSystem, EcsOnStore,
        [in] chunks3.VoxLink,
        [in] chunks3.ChunkPosition,
        [in] rendering.RenderDistance,
        [in] chunks3.ChunkLodDirty,
        [in] rendering.RenderLod,
        [none] StreamedChunk)
    // main thread
    zox_system_1(StreamEndEventSystem, EcsPreStore,
        [in] generic.EventInput,
        [in] chunks3.ChunkLinks,
        [out] StreamEndEvent)
    zox_filter(streamers,
        [in] StreamPoint)
    zox_system_ctx_1(ChunkSpawnSystem, EcsPreStore, streamers,
        [in] chunks3.ChunkPosition,
        [in] chunks3.VoxLink,
        [in] rendering.RenderDistance,
        [out] chunks3.ChunkNeighbors,
        [none] StreamedChunk)
}