#ifndef zoxel_characters3D_terrain
#define zoxel_characters3D_terrain

// zoxel_component_includes
#include "settings/settings.c"
// zoxel_prefab_includes
// zoxel_system_includes
#include "systems/characters3D_spawn_system.c"
// zoxel_fun_includes

zoxel_begin_module(Characters3DTerrain)
set_character_terrain_settings();
// zoxel_system_defines
// todo: make multithread by spawning mesh outside this system
zoxel_system(Characters3DSpawnSystem, EcsPostUpdate, [none] terrain.TerrainChunk, [in] GenerateChunk, [in] ChunkOctree, [in] ChunkPosition)
// zoxel_component_defines
// zoxel_prefab_defines
zoxel_end_module(Characters3DTerrain)

#endif