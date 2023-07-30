#ifndef zoxel_characters3D_terrain
#define zoxel_characters3D_terrain

#include "settings/settings.c"
// zoxel_component_defines
zox_byte_component(GenerateChunkEntities)
// zoxel_prefab_includes
// zoxel_system_includes
#include "systems/characters3D_spawn_system.c"
#include "systems/chunk_characters3D_update_system.c"
// zoxel_fun_includes

void spawn_prefabs_characters3D_terrain(ecs_world_t *world) {
    zox_set(prefab_terrain_chunk_octree, GenerateChunkEntities, { 0 })
}

zox_begin_module(Characters3DTerrain)
set_character_terrain_settings();
zox_define_component(GenerateChunkEntities)
// zoxel_system_defines
// todo: spawn characters on thread instead
// use GenerateChunkEntities here instead of GenerateChunk
zox_system_1(Characters3DSpawnSystem, main_thread_pipeline, [none] terrain.TerrainChunk, [in] ChunkOctree, [in] ChunkPosition, [in] RenderLod, [out] EntityLinks, [out] GenerateChunkEntities)
zox_system(ChunkCharactersTriggerSystem, EcsOnUpdate, [none] terrain.TerrainChunk, [in] ChunkDirty, [out] GenerateChunkEntities)
zox_system(ChunkCharactersUpdateSystem, EcsOnLoad, [none] terrain.TerrainChunk, [in] RenderLod, [in] EntityLinks, [out] GenerateChunkEntities)
// zoxel_component_defines
// zoxel_prefab_defines
zoxel_end_module(Characters3DTerrain)

#endif