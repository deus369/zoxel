#ifndef zoxel_voxels_terrain
#define zoxel_voxels_terrain

// long int render_terrain_chunks_system_id;
#define zox_pipeline_chunk_generation EcsPostLoad // EcsOnLoad EcsOnUpdate
#include "settings/settings.c"
// zoxel_component_declares
zox_declare_tag(TerrainWorld)
zox_declare_tag(TerrainChunk)
zox_declare_tag(ChunkTerrain)
zox_declare_tag(Streamer)
zox_component(StreamPoint, int3)
// zoxel_prefab_includes
#include "prefabs/terrain.c"
#include "prefabs/terrain_chunk.c"
#include "prefabs/terrain_chunk_octree.c"
// zoxel_util_includes
#include "util/static_octree_build.c"
// zoxel_system_declares
#include "systems/terrain_chunk_system.c"
#include "systems/chunk_uvs_build_system.c"
#include "systems/stream_point_system.c"
#include "octree_systems/chunk_octree_build_system.c"
#include "octree_systems/octree_terrain_chunk_system.c"
#include "octree_systems/terrain_chunks_render_system.c"
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

zox_begin_module(Terrain)
set_terrain_render_distance();
// zoxel_component_defines
zox_define_tag(TerrainWorld)
zox_define_tag(TerrainChunk)
zox_define_tag(ChunkTerrain)
zox_define_tag(Streamer)
zox_define_component(StreamPoint)
// zoxel_filter_defines
zox_filter(generateTerrainChunkQuery, [none] TerrainChunk, [out] GenerateChunk)
zox_filter(chunks_generating, [in] GenerateChunk)
zox_filter(terrain_chunks_query, [none] TerrainChunk, [in] ChunkPosition, [in] ChunkNeighbors, [out] RenderLod, [out] ChunkDirty)
// zoxel_system_defines
zox_system_ctx(TerrainChunkSystem, zox_pipeline_chunk_generation, generateTerrainChunkQuery, [none] TerrainChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] ChunkPosition, [out] GenerateChunk)
zox_system_ctx(OctreeTerrainChunkSystem, zox_pipeline_chunk_generation, generateTerrainChunkQuery, [none] TerrainChunk, [in] ChunkPosition, [out] GenerateChunk, [out] ChunkDirty, [out] ChunkOctree)
zox_system_ctx(StreamPointSystem, EcsPostUpdate, terrain_chunks_query, [none] Streamer, [in] Position3D, [out] StreamPoint)
if (!headless) zox_system_ctx(ChunkOctreeBuildSystem, zox_pipeline_build_voxel_mesh, chunks_generating, [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] VoxLink, [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshColorRGBs, [out] MeshDirty, [none] voxels.core.ChunkTextured)
zox_render3D_system(TerrainChunksRenderSystem, [in] Position3D, [in] Rotation3D, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] VoxLink)
zoxel_end_module(Terrain)

#endif
