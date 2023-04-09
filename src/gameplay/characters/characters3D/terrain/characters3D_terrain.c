#ifndef zoxel_characters3D_terrain
#define zoxel_characters3D_terrain

#define characters_per_chunk_count 2

// zoxel_component_includes
// zoxel_prefab_includes
// zoxel_system_includes
#include "systems/characters3D_spawn_system.c"
// zoxel_fun_includes

zoxel_begin_module(Characters3DTerrain)
// zoxel_system_defines
// todo: make multithread by spawning mesh outside this system
zoxel_system_1(Characters3DSpawnSystem, EcsPostUpdate, [none] terrain.TerrainChunk, [in] GenerateChunk, [in] ChunkOctree, [in] ChunkPosition)
// zoxel_component_defines
// zoxel_prefab_defines
zoxel_end_module(Characters3DTerrain)

#endif