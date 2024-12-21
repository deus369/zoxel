#ifndef zox_characters3D_terrain
#define zox_characters3D_terrain

#include "settings/settings.c"
#include "systems/characters3D_spawn_system.c"

void spawn_prefabs_characters3D_terrain(ecs_world_t *world) {
    set_character_terrain_settings();
}

zox_begin_module(Characters3DTerrain)
// todo: this kinda just spawns to be visible, perhaps keep low res characters onboard? in lower Lods SimuChunks!
zox_system_1(Characters3DSpawnSystem, zox_pip_mainthread, [in] ChunkLodDirty, [in] ChunkOctree, [in] ChunkPosition, [in] RenderDistance, [in] RenderDisabled, [out] EntityLinks, [none] terrain.TerrainChunk)
spawn_prefabs_characters3D_terrain(world);
zoxel_end_module(Characters3DTerrain)

#endif
