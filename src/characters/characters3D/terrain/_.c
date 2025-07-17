#ifndef zox_characters3D_terrain
#define zox_characters3D_terrain

// #define zox_enable_log_spawning

#include "settings/_.c"
#include "util/_.c"
#include "debug/_.c"
#include "systems/characters3D_spawn_system.c"

zox_begin_module(Characters3DTerrain)
    // todo: this kinda just spawns to be visible, perhaps keep low res characters onboard? in lower Lods SimuChunks!
    zox_system_1(Characters3DSpawnSystem, zox_pip_mainthread,
        [in] chunks3.ChunkLodDirty,
        [in] chunks3.VoxelNode,
        [in] chunks3.NodeDepth,
        [in] chunks3.ChunkPosition,
        [in] rendering.RenderDistance,
        [in] rendering.RenderDisabled,
        [in] chunks3.VoxLink,
        [out] generic.EntityLinks,
        [none] terrain.TerrainChunk)
zox_end_module(Characters3DTerrain)

#endif