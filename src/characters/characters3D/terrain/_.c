#ifndef zox_characters3D_terrain
#define zox_characters3D_terrain

// #define zox_enable_log_spawning

#include "settings/_.c"
#include "util/_.c"
#include "systems/characters3D_spawn_system.c"

zox_begin_module(Characters3DTerrain)
    // todo: this kinda just spawns to be visible, perhaps keep low res characters onboard? in lower Lods SimuChunks!
    zox_system_1(Characters3DSpawnSystem, zox_pip_mainthread,
        [in] chunks.ChunkLodDirty,
        [in] chunks.VoxelNode,
        [in] chunks.NodeDepth,
        [in] chunks.ChunkPosition,
        [in] rendering.RenderDistance,
        [in] rendering.RenderDisabled,
        [in] voxels.VoxLink,
        [out] generic.EntityLinks,
        [none] terrain.TerrainChunk)
    // test function for npc spawning
    // add_hook_key_down(test_spawn_character_npc);
    add_hook_key_down(key_down_toggle_debug_character_bounds);
zox_end_module(Characters3DTerrain)

#endif
