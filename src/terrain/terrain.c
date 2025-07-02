/**
 *  Zox Terrain
 *
 *      - colored vox models
 *
 *      - todo: don't generate mesh until render is enabled!
 *      - todo: use ChunkOriginDistance instead of RenderLod for camera distance for TerrainChunks
  *      - todo: delay BlockVoxSpawnSystem to main thread pipeline like character spawning, use same trigger? rest on load? make a resetsystem 2 for this - just  make reset defines use the pipeline
 *
 * */
#if !defined(zox_mod_terrain) && defined(zox_mod_voxels)
#define zox_mod_terrain

#include "settings/_.c"
zox_declare_tag(FlatTerrain)
zox_declare_tag(FlatlandChunk)
zox_declare_tag(TerrainWorld)
zox_declare_tag(TerrainChunk)
zox_declare_tag(ChunkTerrain)
zox_component_entity(TerrainLink)
#include "data/_.c"
#include "prefabs/_.c"
#include "util/_.c"
#include "voxels/_.c"
#include "systems/_.c"

zox_begin_module(Terrain)
    add_hook_terminal_command(process_arguments_terrain);
    zox_define_tag(FlatTerrain)
    zox_define_tag(FlatlandChunk)
    zox_define_tag(TerrainWorld)
    zox_define_tag(TerrainChunk)
    zox_define_tag(ChunkTerrain)
    zox_define_component_entity(TerrainLink)
    define_systems_terrain(world);
    spawn_prefabs_terrain(world);
    // add_hook_key_down(test_spawn_chunk_terrain);
zox_end_module(Terrain)

#endif