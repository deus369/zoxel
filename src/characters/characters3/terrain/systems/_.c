#include "characters3_spawn_system.c"
#include "characters3_despawn_system.c"

void define_systems_characters3_terrain(ecs_world_t* world) {
    zox_system(Characters3DespawnSystem, EcsOnStore,
        [in] rendering.RenderDistanceDirty,
        [in] rendering.RenderDistance,
        [out] CharactersSpawned,
        [out] generic.EntityLinks,
        [none] terrain.TerrainChunk)
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
}