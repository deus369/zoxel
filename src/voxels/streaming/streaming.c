#ifndef zox_mod_streaming
#define zox_mod_streaming

zox_declare_tag(Streamer)
zox_declare_tag(StreamedChunk)
zox_component_int3(StreamPoint)
zox_component_byte(StreamDirty)
zox_function_component(StreamEndEvent, void, ecs_world_t*, const ecs_entity_t)
zox_increment_system_with_reset(ChunkLodDirty, chunk_lod_state_end)
zox_increment_system_with_reset(StreamDirty, zox_general_state_end)
#include "systems/stream_point_system.c"
#include "systems/chunk_lod_dirty_system.c"
#include "systems/chunk_stream_system.c"
#include "systems/chunk_lod_system.c"
#include "systems/chunk_frustum_system.c"
#include "systems/stream_end_event_system.c"

zox_begin_module(Streaming)
zox_define_tag(Streamer)
zox_define_tag(StreamedChunk)
zox_define_component_int3(StreamPoint)
zox_define_component_byte(StreamDirty)
zox_define_component(StreamEndEvent)
zox_filter(streamers, [in] StreamPoint, [in] StreamDirty)
zox_filter(streamers2, [in] StreamDirty, [in] StreamPoint)
zox_filter(filter_cameras, [in] generic.Position3DBounds, [in] cameras.CameraPlanes, [none] cameras.Camera3D)
zox_define_increment_system(ChunkLodDirty, EcsOnLoad)
zox_define_increment_system(StreamDirty, EcsOnLoad)
// main thread
zox_system_ctx_1(ChunkStreamSystem, zox_pip_mainthread, streamers, [in] ChunkPosition, [in] VoxLink, [in] RenderDistance, [in] RenderDisabled, [out] ChunkNeighbors, [none] StreamedChunk)
zox_system_1(StreamEndEventSystem, zox_pip_mainthread, [in] EventInput, [in] ChunkLinks, [out] StreamEndEvent)
// multi threads
zox_system(StreamPointSystem, EcsOnUpdate, [in] Position3D, [in] VoxLink, [out] StreamPoint, [out] StreamDirty, [none] Streamer)
zox_system(ChunkLodDirtySystem, EcsOnUpdate, [in] ChunkLodDirty, [in] ChunkNeighbors, [out] GenerateChunk, [out] ChunkMeshDirty, [none] StreamedChunk)
zox_system_ctx(ChunkFrustumSystem, EcsOnUpdate, filter_cameras, [in] Position3D, [in] ChunkSize, [in] VoxScale, [in] EntityLinks, [in] ChunkOctree, [out] RenderDisabled, [none] StreamedChunk)
zox_system_ctx(ChunkLodSystem, EcsOnUpdate, streamers2, [in] ChunkPosition, [out] RenderLod, [out] ChunkLodDirty, [out] RenderDistance, [none] StreamedChunk)

zoxel_end_module(Streaming)

#endif
