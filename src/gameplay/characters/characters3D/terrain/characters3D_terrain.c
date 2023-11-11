#ifndef zoxel_characters3D_terrain
#define zoxel_characters3D_terrain

#include "settings/settings.c"
// zoxel_component_defines
zox_component_byte(GenerateChunkEntities)
#define zox_chunk_entities_state_initial 0
#define zox_chunk_entities_state_triggered 1
#define zox_chunk_entities_state_spawned 2
// zoxel_prefab_includes
// zoxel_system_includes
#include "systems/characters3D_spawn_system.c"
#include "systems/chunk_characters3D_update_system.c"
#include "systems/chunk_entities_trigger_system.c"
// zoxel_fun_includes

void spawn_prefabs_characters3D_terrain(ecs_world_t *world) {
    zox_prefab_set(prefab_terrain_chunk_octree, GenerateChunkEntities, { zox_chunk_entities_state_initial })
}

zox_begin_module(Characters3DTerrain)
set_character_terrain_settings();
// zoxel_component_defines
zox_define_component(GenerateChunkEntities)
// zoxel_system_defines
zox_system_1(Characters3DSpawnSystem, main_thread_pipeline, [none] terrain.TerrainChunk, [in] ChunkOctree, [in] ChunkPosition, [in] RenderLod, [out] EntityLinks, [out] GenerateChunkEntities) // todo: spawn characters on thread instead
zox_system(ChunkEntitiesTriggerSystem, zox_pipeline_chunk_generation, [none] terrain.TerrainChunk, [in] ChunkDirty, [out] GenerateChunkEntities) // todo: use GenerateChunkEntities here instead of GenerateChunk
zox_system(ChunkCharactersUpdateSystem, zox_pipeline_chunk_generation, [none] terrain.TerrainChunk, [in] RenderLod, [in] EntityLinks, [out] GenerateChunkEntities)
zoxel_end_module(Characters3DTerrain)

#endif
