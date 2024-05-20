#include "terrain.c"
#include "terrain_chunk.c"
#include "terrain_chunk_octree.c"
ecs_entity_t prefab_terrain;
ecs_entity_t local_terrain; // todo: remove and just use Realm's TerrainLink
ecs_entity_t prefab_terrain_chunk_octree;
ecs_entity_t prefab_terrain_chunk;

void spawn_prefabs_terrain(ecs_world_t *world) {
    const int3 terrain_chunk_size = (int3) { default_chunk_length, 8 * default_chunk_length, default_chunk_length };
    prefab_terrain = spawn_prefab_terrain(world);
    prefab_terrain_chunk = spawn_prefab_terrain_chunk(world, terrain_chunk_size);
    prefab_terrain_chunk_octree = spawn_prefab_terrain_chunk_octree(world, terrain_chunk_size);
}
