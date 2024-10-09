#include "terrain.c"
#include "terrain_chunk.c"
#include "terrain_chunk_octree.c"
ecs_entity_t prefab_terrain;
ecs_entity_t local_terrain; // todo: remove and just use Realm's TerrainLink
// ecs_entity_t prefab_terrain_chunk;
ecs_entity_t prefab_chunk_height;
ecs_entity_t prefab_terrain_chunk_flat;

void prefab_add_terrain_camera(ecs_world_t *world, const ecs_entity_t e) {
    zox_add_tag(e, Streamer)
    zox_prefab_set(e, StreamPoint, { int3_zero })
    zox_prefab_set(e, TerrainLink, { 0 })
    zox_prefab_set(e, VoxLink, { 0 })
}

void spawn_prefabs_terrain(ecs_world_t *world) {
    prefab_add_terrain_camera(world, prefab_camera_game);
    const int3 terrain_chunk_size = (int3) { default_chunk_length, 8 * default_chunk_length, default_chunk_length };
    prefab_terrain = spawn_prefab_terrain(world);
    // prefab_terrain_chunk = spawn_prefab_terrain_chunk(world, terrain_chunk_size);
    prefab_chunk_height = spawn_prefab_terrain_chunk_octree(world, prefab_chunk, terrain_chunk_size);
    prefab_terrain_chunk_flat = spawn_prefab_terrain_chunk_octree(world, prefab_chunk, terrain_chunk_size);
    zox_add_tag(prefab_terrain_chunk_flat, FlatlandChunk)
}
