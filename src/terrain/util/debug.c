int get_terrain_chunks_count(ecs_world_t *world) {
    return zox_count_entities(world, ecs_id(TerrainChunk));
}

ecs_entity_t test_chunk_terrain = 0;

// h
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
