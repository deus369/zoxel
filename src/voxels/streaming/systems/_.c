
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
        [in] transforms3.d.Position3D,
        [in] voxels.VoxLink,
        [out] StreamPoint,
        [out] StreamDirty,
        [none] Streamer)
    zox_filter(filter_cameras,
        [in] generic.Position3DBounds,
        [in] cameras.CameraPlanes,
        [none] cameras.Camera3D)
    zox_system_ctx(ChunkFrustumSystem, EcsOnUpdate, filter_cameras,
        [in] transforms3.d.Position3D,
        [in] chunks.ChunkSize,
        [in] blocks.VoxScale,
        [in] generic.EntityLinks,
        [in] chunks.ChunkOctree,
        [in] chunks.NodeDepth,
        [out] rendering.RenderDisabled,
        [none] StreamedChunk)
    zox_filter(streamers2,
        [in] StreamPoint,
        [in] StreamDirty)
    zox_system_ctx(ChunkLodSystem, EcsOnUpdate, streamers2,
        [in] chunks.ChunkPosition,
        [out] rendering.RenderLod,
        [out] chunks.ChunkLodDirty,
        [out] rendering.RenderDistance,
        [none] StreamedChunk)
    zox_system(ChunkLodDirtySystem, EcsOnUpdate,
        [in] chunks.ChunkLodDirty,
        [in] rendering.RenderLod,
        [out] chunks.GenerateChunk,
        [out] chunks.ChunkMeshDirty,
        [none] StreamedChunk)
    zox_system(ChunkNeighborUpdatedSystem, EcsPostUpdate,
        [in] chunks.ChunkNeighbors,
        [out] chunks.ChunkMeshDirty,
        [none] StreamedChunk)
    // streams
    zox_system(ChunkDieSystem, EcsOnStore,
        [in] voxels.VoxLink,
        [in] chunks.ChunkPosition,
        [in] rendering.RenderDistance,
        [in] chunks.ChunkLodDirty,
        [in] rendering.RenderLod,
        [none] StreamedChunk)
    // main thread
    zox_system_1(StreamEndEventSystem, EcsPreStore,
        [in] generic.EventInput,
        [in] chunks.ChunkLinks,
        [out] StreamEndEvent)
    zox_filter(streamers,
        [in] StreamPoint)
    zox_system_ctx_1(ChunkSpawnSystem, EcsPreStore, streamers,
        [in] chunks.ChunkPosition,
        [in] voxels.VoxLink,
        [in] rendering.RenderDistance,
        [out] chunks.ChunkNeighbors,
        [none] StreamedChunk)
}