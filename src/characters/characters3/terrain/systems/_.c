#include "characters3_spawn.c"
#include "characters3_despawn.c"
#include "character3_spawn_zone.c"

void define_systems_characters3_terrain(ecs_world_t* world) {
    zox_system(Characters3SpawnZoneSystem, EcsPreUpdate,
        [in] rendering.RenderDistanceDirty,
        [in] rendering.RenderDistance,
        [out] CharacterSpawnZone)
    zox_system(Characters3DespawnSystem, EcsPostUpdate,
        [in] rendering.RenderDistanceDirty,
        [in] CharacterSpawnZone,
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
        [in] chunks3.ChunkNeighbors,
        [out] CharactersSpawned,
        [out] CharactersEverSpawned,
        [out] generic.EntityLinks,
        [none] terrain.TerrainChunk)
}