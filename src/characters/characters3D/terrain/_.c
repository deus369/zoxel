#ifndef zox_characters3D_terrain
#define zox_characters3D_terrain

// #define zox_enable_log_spawning

#include "settings/_.c"
zox_component_byte(CharactersSpawned)
zox_component_byte(CharactersEverSpawned)
#include "util/_.c"
#include "debug/_.c"
#include "systems/characters3_spawn_system.c"
#include "systems/characters3_despawn_system.c"

zox_begin_module(Characters3DTerrain)
    zox_define_component_byte(CharactersSpawned)
    zox_define_component_byte(CharactersEverSpawned)
    if (prefab_chunk_height) {
        zox_prefab_set(prefab_chunk_height, CharactersSpawned, { 0 })
        zox_prefab_set(prefab_chunk_height, CharactersEverSpawned, { 0 })
    }
    zox_system(Characters3DespawnSystem, EcsOnStore,
        [in] rendering.RenderDistanceDirty,
        [in] rendering.RenderDistance,
        [out] CharactersSpawned,
        [out] generic.EntityLinks,
        [none] terrain.TerrainChunk)
    // todo: this kinda just spawns to be visible, perhaps keep low res characters onboard? in lower Lods SimuChunks!
    zox_system_1(Characters3SpawnSystem, zox_pip_mainthread,
        [in] rendering.RenderDistanceDirty,
        [in] chunks3.VoxelNode,
        [in] chunks3.NodeDepth,
        [in] chunks3.ChunkPosition,
        [in] rendering.RenderDistance,
        [in] rendering.RenderDisabled,
        [in] chunks3.VoxLink,
        [out] CharactersSpawned,
        [out] CharactersEverSpawned,
        [out] generic.EntityLinks,
        [none] terrain.TerrainChunk)
zox_end_module(Characters3DTerrain)

#endif