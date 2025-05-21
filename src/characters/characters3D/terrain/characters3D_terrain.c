#ifndef zox_characters3D_terrain
#define zox_characters3D_terrain

#include "settings/settings.c"
#include "util/log.c"
#include "util/debug.c"
#include "systems/characters3D_spawn_system.c"

zox_begin_module(Characters3DTerrain)
    set_character_terrain_settings();
    // todo: this kinda just spawns to be visible, perhaps keep low res characters onboard? in lower Lods SimuChunks!
    zox_system_1(Characters3DSpawnSystem, zox_pip_mainthread, [in] ChunkLodDirty, [in] ChunkOctree, [in] ChunkPosition, [in] RenderDistance, [in] RenderDisabled, [in] VoxLink, [out] EntityLinks, [none] terrain.TerrainChunk)
    // test function for npc spawning
    // add_hook_key_down(test_spawn_character_npc);
    add_hook_key_down(key_down_toggle_debug_character_bounds);
zox_end_module(Characters3DTerrain)

#endif
