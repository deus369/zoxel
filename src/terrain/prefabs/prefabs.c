ecs_entity_t local_terrain; // todo: remove and just use Realm's TerrainLink
#include "terrain.c"
#include "chunk_terrain.c"
ecs_entity_t prefab_terrain;
ecs_entity_t prefab_chunk_height;
ecs_entity_t prefab_terrain_chunk_flat;

void prefab_add_terrain_camera(ecs_world_t *world, const ecs_entity_t e) {
    zox_add_tag(e, Streamer)
    zox_prefab_set(e, StreamPoint, { int3_zero })
    zox_prefab_set(e, TerrainLink, { 0 })
    zox_prefab_set(e, VoxLink, { 0 })
}

void spawn_prefabs_terrain(ecs_world_t *world) {
    zox_prefab_set(prefab_realm, VoxelLinks, { 0, NULL })
    zox_prefab_set(prefab_realm, VoxelsDirty, { 0 })
    prefab_add_terrain_camera(world, prefab_camera_game);
    const int3 terrain_chunk_size = (int3) { default_chunk_length, 8 * default_chunk_length, default_chunk_length };
    prefab_chunk_height = spawn_prefab_terrain_chunk(world, prefab_chunk, terrain_chunk_size);
    prefab_terrain_chunk_flat = spawn_prefab_terrain_chunk(world, prefab_chunk, terrain_chunk_size);
    zox_add_tag(prefab_terrain_chunk_flat, FlatlandChunk)
    prefab_terrain = spawn_prefab_terrain(world);
}
