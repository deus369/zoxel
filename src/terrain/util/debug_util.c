int get_terrain_chunks_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(TerrainChunk));
}
