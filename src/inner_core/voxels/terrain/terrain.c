#ifndef zox_terrain
#define zox_terrain

// todo: use ChunkOriginDistance instead of RenderLod for camera distance for TerrainChunks
#include "data/settings.c"
zox_declare_tag(TerrainWorld)
zox_declare_tag(TerrainChunk)
zox_declare_tag(ChunkTerrain)
zox_declare_tag(Streamer)
zox_component_int3(StreamPoint)
zox_component_entity(TerrainLink)
zox_component_byte(StreamDirty)
#include "data/terrain_statistics.c"
#include "data/mesh_uvs_build_data.c"
#include "util/static_octree_build.c"
#include "util/chunk_util.c"
#include "util/prefab_util.c"
#include "util/octree_build_util.c"
#include "util/debug_util.c"
#include "prefabs/prefabs.c"
#include "systems/terrain_chunk_system.c"
#include "systems/chunk_uvs_build_system.c"
#include "systems/stream_point_system.c"
#include "systems/terrain_lod_system.c"
#include "octree_systems/chunk_octree_build_system.c"
#include "octree_systems/octree_terrain_chunk_system.c"
#include "octree_systems/terrain_chunks_render_system.c"
#include "systems/chunk_frustum_system.c"
#include "util/create_terrain.c"
#include "systems/chunk_bounds_debug_system.c"
#include "systems/block_vox_spawn_system.c"
// used for system
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
zox_filter(terrain_chunks, [in] ChunkPosition, [in] ChunkNeighbors, [out] RenderLod, [out] ChunkDirty, [out] ChunkLodDirty, [none] TerrainChunk)
zox_filter(cameras_query, [in] generic.Position3DBounds, [in] cameras.CameraPlanes, [none] cameras.Camera3D)
zox_filter(streamers, [in] StreamPoint, [in] TerrainLink)
zox_filter_combine(terrain_lod_filter, terrain_chunks, streamers)
// generate chunks
zox_system_ctx(OctreeTerrainChunkSystem, zox_pip_voxels_chunk_dirty, generateTerrainChunkQuery, [none] TerrainChunk, [in] ChunkPosition, [out] GenerateChunk, [out] ChunkDirty, [out] ChunkOctree)
zox_system_ctx(TerrainChunkSystem, zox_pip_voxels_chunk_dirty, generateTerrainChunkQuery, [none] TerrainChunk, [out] ChunkDirty, [out] ChunkData, [in] ChunkSize, [in] ChunkPosition, [out] GenerateChunk)
// streaming chunks
zox_system(StreamPointSystem, zox_pip_voxels, [in] Position3D, [in] TerrainLink, [out] StreamPoint, [none] Streamer)
zox_system_ctx(ChunkFrustumSystem, zox_pip_voxels, cameras_query, [in] Position3D, [in] ChunkSize, [in] VoxScale, [in] EntityLinks, [in] BlockSpawns, [out] RenderDisabled, [none] TerrainChunk)
zox_system_ctx(TerrainLodSystem, zox_pip_voxels, &terrain_lod_filter, [in] ChunkLinks, [out] StreamDirty, [none] TerrainWorld)
// build chunks
if (!headless) zox_system_ctx(ChunkOctreeBuildSystem, zox_pip_voxels_chunk_clean, chunks_generating, [out] ChunkDirty, [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] VoxLink, [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshColorRGBs, [out] MeshDirty, [in] VoxScale, [none] chunks.ChunkTextured)
// builds meshes
zox_render3D_system(TerrainChunksRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] VoxLink, [in] RenderDisabled)
// spawners
zox_system_1(BlockVoxSpawnSystem, zox_pip_voxels, [in] ChunkLodDirty, [in] ChunkOctree, [in] ChunkPosition, [in] ChunkSize, [in] VoxLink, [in] RenderLod, [in] RenderDisabled, [out] BlockSpawns, [none] TerrainChunk) // remember: needs zox_pip_voxels, zox_pip_mainthread is called when Dirty is cleaned
#ifdef zox_debug_chunk_bounds
zox_system_1(ChunkBoundsDebugSystem, zox_pip_mainthread, [in] Position3D, [in] ChunkSize, [in] VoxScale, [in] RenderDisabled, [none] TerrainChunk)
#endif
zoxel_end_module(Terrain)

#endif
