#ifndef zox_characters3D_terrain
#define zox_characters3D_terrain

#include "settings/settings.c"
zox_component_byte(GenerateChunkEntities)
#define zox_chunk_entities_state_initial 0
#define zox_chunk_entities_state_triggered 1
#define zox_chunk_entities_state_spawned 2
#include "systems/characters3D_spawn_system.c"
#include "systems/chunk_entities_trigger_system.c"
#include "systems/chunk_entities_lod_system.c"
#include "systems/chunk_lod_dirty_system.c"

void spawn_prefabs_characters3D_terrain(ecs_world_t *world) {
    set_character_terrain_settings();
    zox_prefab_set(prefab_terrain_chunk_octree, GenerateChunkEntities, { zox_chunk_entities_state_initial })
}

zox_begin_module(Characters3DTerrain)
zox_define_component(GenerateChunkEntities)
zox_system_1(Characters3DSpawnSystem, zox_pip_mainthread, [none] terrain.TerrainChunk, [in] ChunkOctree, [in] ChunkPosition, [in] RenderLod, [in] RenderDisabled, [out] EntityLinks, [out] GenerateChunkEntities)
zox_system(ChunkEntitiesTriggerSystem, zox_pip_pre_chunk_gen, [none] terrain.TerrainChunk, [in] ChunkDirty, [out] GenerateChunkEntities)
zox_system(ChunkLodDirtySystem, zox_pip_pre_chunk_gen, [in] ChunkDirty, [out] ChunkLodDirty, [none] terrain.TerrainChunk)
zox_system(ChunkEntitiesLodSystem, EcsOnUpdate, [in] RenderLod, [in] EntityLinks, [in] BlockSpawns, [out] ChunkLodDirty, [none] terrain.TerrainChunk)
zoxel_end_module(Characters3DTerrain)

#endif
