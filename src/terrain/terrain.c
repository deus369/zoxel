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

zox_declare_tag(FlatTerrain)
zox_declare_tag(FlatlandChunk)
zox_declare_tag(TerrainWorld)
zox_declare_tag(TerrainChunk)
zox_declare_tag(ChunkTerrain)
zox_component_entity(TerrainLink)
#include "data/data.c"
#include "prefabs/prefabs.c"
#include "util/util.c"
#include "systems/systems.c"

ecs_entity_t test_chunk_terrain = 0;
void test_spawn_chunk_terrain(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_h) {
        if (test_chunk_terrain) {
            zox_log("- deleting test chunk terrain\n")
            zox_delete(test_chunk_terrain)
            test_chunk_terrain = 0;
        } else {
            zox_log("+ spawning test chunk terrain\n")
            // spawn at here
            int3 chunk_position = int3_zero;
            const ecs_entity_t terrain = zox_get_value(local_realm, TerrainLink)
            if (!terrain) return;
            test_chunk_terrain = spawn_chunk_terrain(world, prefab_chunk_height, terrain, chunk_position, int3_zero, real_chunk_scale);
        }
    }
}

zox_begin_module(Terrain)
    add_to_arguments(process_arguments_terrain);
    zox_define_tag(FlatTerrain)
    zox_define_tag(FlatlandChunk)
    zox_define_tag(TerrainWorld)
    zox_define_tag(TerrainChunk)
    zox_define_tag(ChunkTerrain)
    zox_define_component_entity(TerrainLink)
    define_systems_terrain(world);
    spawn_prefabs_terrain(world);
    add_functions_key_down(test_spawn_chunk_terrain);
zox_end_module(Terrain)

#endif