#ifndef zox_voxels_terrain
#define zox_voxels_terrain

#include "settings/settings.c"
zox_declare_tag(TerrainWorld)
zox_declare_tag(TerrainChunk)
zox_declare_tag(ChunkTerrain)
zox_declare_tag(Streamer)
zox_component_int3(StreamPoint)
zox_component_entity(TerrainLink)
zox_component_byte(StreamDirty)
#include "data/mesh_uvs_build_data.c"
#include "prefabs/terrain.c"
#include "prefabs/terrain_chunk.c"
#include "prefabs/terrain_chunk_octree.c"
#include "util/static_octree_build.c"
#include "systems/terrain_chunk_system.c"
#include "systems/chunk_uvs_build_system.c"
#include "systems/stream_point_system.c"
#include "systems/terrain_lod_system.c"
#include "octree_systems/chunk_octree_build_system.c"
#include "octree_systems/octree_terrain_chunk_system.c"
#include "octree_systems/terrain_chunks_render_system.c"
#include "systems/chunk_frustum_system.c"
#include "util/create_terrain.c"

int get_terrain_chunks_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(TerrainChunk));
}

void spawn_prefabs_terrain(ecs_world_t *world) {
    const int3 terrain_chunk_size = { default_chunk_length, 8 * default_chunk_length, default_chunk_length };
    spawn_prefab_terrain(world);
    spawn_prefab_terrain_chunk(world, terrain_chunk_size);
    spawn_prefab_terrain_chunk_octree(world, terrain_chunk_size);
}

ctx2 terrain_lod_filter;

zox_begin_module(Terrain)
set_terrain_render_distance();
zox_define_tag(TerrainWorld)
zox_define_tag(TerrainChunk)
zox_define_tag(ChunkTerrain)
zox_define_tag(Streamer)
zox_define_component_int3(StreamPoint)
zox_define_component_entity(TerrainLink)
zox_define_component_byte(StreamDirty)
zox_filter(generateTerrainChunkQuery, [none] TerrainChunk, [out] GenerateChunk)
zox_filter(chunks_generating, [in] GenerateChunk)
zox_filter(terrain_chunks, [none] TerrainChunk, [in] ChunkPosition, [in] ChunkNeighbors, [out] RenderLod, [out] ChunkDirty)
zox_filter(camera_planes, [in] cameras.CameraPlanes, [none] cameras.Camera3D)
zox_filter(streamers, [in] StreamPoint, [in] TerrainLink)
zox_filter_combine(terrain_lod_filter, terrain_chunks, streamers)
zox_system_ctx(TerrainChunkSystem, zox_pipeline_chunk_generation, generateTerrainChunkQuery, [none] TerrainChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] ChunkPosition, [out] GenerateChunk)
zox_system_ctx(OctreeTerrainChunkSystem, zox_pipeline_chunk_generation, generateTerrainChunkQuery, [none] TerrainChunk, [in] ChunkPosition, [out] GenerateChunk, [out] ChunkDirty, [out] ChunkOctree)
zox_system(StreamPointSystem, EcsPostUpdate, [in] Position3D, [in] TerrainLink, [out] StreamPoint, [none] Streamer)
zox_system_ctx(TerrainLodSystem, EcsPostUpdate, &terrain_lod_filter, [in] ChunkLinks, [out] StreamDirty, [none] TerrainWorld)
zox_system_ctx(ChunkFrustumSystem, EcsPostUpdate, camera_planes, [in] Position3D, [in] ChunkSize, [in] VoxScale, [out] RenderDisabled)
if (!headless) zox_system_ctx(ChunkOctreeBuildSystem, zox_pipeline_build_voxel_mesh, chunks_generating, [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] VoxLink, [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshColorRGBs, [out] MeshDirty, [in] VoxScale, [none] voxels.core.ChunkTextured)
zox_render3D_system(TerrainChunksRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] VoxLink, [in] RenderDisabled)
zoxel_end_module(Terrain)

#endif
