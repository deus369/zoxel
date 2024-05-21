#ifndef zox_characters3D_terrain
#define zox_characters3D_terrain

#include "settings/settings.c"
zox_component_byte(GenerateChunkEntities)
#include "systems/characters3D_spawn_system.c"
#include "systems/chunk_entities_trigger_system.c"

void spawn_prefabs_characters3D_terrain(ecs_world_t *world) {
    set_character_terrain_settings();
    zox_prefab_set(prefab_terrain_chunk_octree, GenerateChunkEntities, { zox_chunk_entities_state_initial })
}

zox_begin_module(Characters3DTerrain)
zox_define_component(GenerateChunkEntities)
zox_system_1(Characters3DSpawnSystem, zox_pip_mainthread, [none] terrain.TerrainChunk, [in] ChunkOctree, [in] ChunkPosition, [in] RenderLod, [in] RenderDisabled, [out] EntityLinks, [out] GenerateChunkEntities)
zox_system(ChunkEntitiesTriggerSystem, zox_pip_voxels, [in] ChunkLodDirty, [out] GenerateChunkEntities, [none] terrain.TerrainChunk)
zoxel_end_module(Characters3DTerrain)

#endif
