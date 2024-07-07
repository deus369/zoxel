#ifndef zox_mod_terrain
#define zox_mod_terrain

zox_declare_tag(FlatTerrain)
zox_declare_tag(FlatlandChunk)
zox_declare_tag(TerrainWorld)
zox_declare_tag(TerrainChunk)
zox_declare_tag(ChunkTerrain)
zox_declare_tag(Streamer)
zox_component_int3(StreamPoint)
zox_component_entity(TerrainLink)
zox_component_byte(StreamDirty)
#include "data/platform_settings.c"
#include "data/generation_settings.c"
#include "data/settings.c"
#include "data/terrain_statistics.c"
#include "data/chunk_textured_build_data.c"
#include "data/mesh_uvs_build_data.c"
#include "util/settings.c"
#include "util/chunk_util.c"
#include "util/prefab_util.c"
#include "util/octree_build_util.c"
#include "util/block_vox.c"
#include "util/debug_util.c"
#include "util/terrain_util.c"
#include "prefabs/prefabs.c"
#include "util/create_terrain.c"
#include "systems/terrain_chunk_system.c"
#include "systems/chunk_uvs_build_system.c"
#include "systems/stream_point_system.c"
#include "systems/terrain_lod_system.c"
#include "systems/chunk_octree_build_system.c"
#include "systems/terrain_chunks_render_system.c"
#include "systems/chunk_frustum_system.c"
#include "systems/chunk_bounds_debug_system.c"
#include "systems/block_vox_spawn_system.c"
#include "systems/block_vox_update_system.c"
#include "systems/chunk_flatland_system.c"
#include "systems/grassy_plains_system.c"
ctx2 terrain_lod_filter; // used for lod system

zox_begin_module(Terrain)
zox_define_tag(FlatTerrain)
zox_define_tag(FlatlandChunk)
zox_define_tag(TerrainWorld)
zox_define_tag(TerrainChunk)
zox_define_tag(ChunkTerrain)
zox_define_tag(Streamer)
zox_define_component_int3(StreamPoint)
zox_define_component_entity(TerrainLink)
zox_define_component_byte(StreamDirty)
// this updates our chunks Lods!!
zox_filter(terrain_chunks, [in] ChunkPosition, [in] ChunkNeighbors, [out] RenderLod, [out] ChunkDirty, [out] ChunkLodDirty, [none] TerrainChunk)
zox_filter(streamers, [in] StreamPoint)
zox_filter_combine(terrain_lod_filter, terrain_chunks, streamers)
zox_system_ctx(TerrainLodSystem, zox_pip_voxels_chunk_dirty, &terrain_lod_filter, [out] StreamDirty, [none] TerrainWorld) // zox_pip_voxels | zox_pip_voxels_chunk_dirty
// this begins streaming updates
zox_system(StreamPointSystem, zox_pip_voxels, [in] Position3D, [in] TerrainLink, [out] StreamPoint, [none] Streamer)
// this updates our chunks RenderDisabled's
zox_filter(cameras_query, [in] generic.Position3DBounds, [in] cameras.CameraPlanes, [none] cameras.Camera3D)
zox_system_ctx(ChunkFrustumSystem, zox_pip_voxels, cameras_query, [in] Position3D, [in] ChunkSize, [in] VoxScale, [in] EntityLinks, [in] BlockSpawns, [out] RenderDisabled, [none] TerrainChunk)
// Builds our Textured Chunks (Terrain) !
zox_filter(chunks_generating, [out] ChunkDirty)
if (!headless) zox_system_ctx(ChunkOctreeBuildSystem, zox_pip_voxels_chunk_clean, chunks_generating, [in] VoxLink,  [in] ChunkOctree, [in] RenderLod, [in] ChunkNeighbors, [in] VoxScale, [in] RenderDisabled, [out] ChunkDirty, [out] MeshIndicies, [out] MeshVertices, [out] MeshUVs, [out] MeshColorRGBs, [out] MeshDirty, [none] chunks.ChunkTextured)
// remember: needs zox_pip_voxels, zox_pip_mainthread is called when Dirty is cleaned
zox_system_1(BlockVoxSpawnSystem, zox_pip_voxels, [in] ChunkLodDirty, [in] ChunkOctree, [in] ChunkPosition, [in] VoxLink, [in] RenderLod, [in] RenderDisabled, [out] BlockSpawns, [none] TerrainChunk)
zox_system_1(BlockVoxUpdateSystem, zox_pip_voxels, [in] ChunkDirty, [in] ChunkOctree, [in] ChunkPosition, [in] VoxLink, [in] RenderLod, [in] RenderDisabled, [out] BlockSpawns, [none] TerrainChunk) //  todo: make ChunkDirty operate over a frame so other systems can hijack event
zox_render3D_system(TerrainChunksRenderSystem, [in] TransformMatrix, [in] MeshGPULink, [in] UvsGPULink, [in] ColorsGPULink, [in] MeshIndicies, [in] VoxLink, [in] RenderDisabled) // builds meshes
#ifdef zox_debug_chunk_bounds
zox_system_1(ChunkBoundsDrawSystem, zox_pip_mainthread, [in] Position3D, [in] ChunkSize, [in] VoxScale, [in] RenderDisabled, [none] TerrainChunk)
#endif
// generate terrain
zox_filter(generateTerrainChunkQuery, [none] TerrainChunk, [out] GenerateChunk)
zox_system(ChunkFlatlandSystem, zox_pip_voxels_chunk_dirty, [none] TerrainChunk, [in] ChunkPosition, [out] GenerateChunk, [out] ChunkDirty, [out] ChunkOctree, [none] FlatlandChunk)
zox_system_ctx(GrassyPlainsSystem, zox_pip_voxels_chunk_dirty, generateTerrainChunkQuery, [none] TerrainChunk, [in] ChunkPosition, [out] GenerateChunk, [out] ChunkDirty, [out] ChunkOctree, [none] !FlatlandChunk)
set_terrain_render_distance();
spawn_prefabs_terrain(world);
zoxel_end_module(Terrain)

#endif

// todo: don't generate mesh until render is enabled!
// todo: use ChunkOriginDistance instead of RenderLod for camera distance for TerrainChunks
// todo: delay BlockVoxSpawnSystem to main thread pipeline like character spawning, use same trigger? rest on load? make a resetsystem 2 for this - just  make reset defines use the pipeline
