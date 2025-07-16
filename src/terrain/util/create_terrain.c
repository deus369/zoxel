int get_chunk_index(int i, int j, int rows) {
    return (i + rows + 1) * (rows + rows + 1) + (j + rows + 1);
}
// vertical_rows + vertical_rows +  - rows + rows + 1
int calculate_terrain_chunks_count(int rows, int slabs) {
    return (slabs + slabs + 1) * (rows + rows + 1) * (rows + rows + 1);
}

int get_chunk_index_2(int i, int j, int k, int rows, int vertical) {
    i += rows;
    j += vertical;
    k += rows;
    return i * (rows + rows + 1) + j * (rows + rows + 1) * (rows + rows + 1) + k;
}

int get_chunk_index_3(int3 position, int rows, int vertical) {
    position.x += rows;
    position.y += vertical;
    position.z += rows;
    return position.x * (rows + rows + 1) + position.y  * (rows + rows + 1) * (rows + rows + 1) + position.z;
}

// todo: pass in through struct
ecs_entity_t spawn_terrain_streaming(ecs_world_t *world,
    const ecs_entity_t realm,
    const int3 center_position,
    const int3 size,
    const ecs_entity_t prefab_terrain,
    const ecs_entity_t prefab_chunk)
{
    const int3 chunk_position = int3_zero;
    if (!zox_has(realm, TilemapLink)) {
        zox_log_error("! realm has no TilemapLink [%lu]", realm)
        return 0;
    }
    zox_geter_value(realm, TilemapLink, ecs_entity_t, tilemap)
    if (zox_valid(tilemap) && zox_has(tilemap, RealmLink)) {
        zox_set(tilemap, RealmLink, { realm })
    } else {
        zox_log_error("invalid tilemap: %lu", tilemap)
    }
    ecs_entity_t e = spawn_terrain(world, prefab_terrain, tilemap, float3_zero, 1);
    /*const ecs_entity_t chunk = spawn_chunk_terrain(world,
        prefab_chunk,
        e,
        center_position,
        chunk_position,
        real_chunk_scale);*/

    ChunkLinks *chunkLinks = &((ChunkLinks) { NULL });
    chunkLinks->value = create_int3_hashmap(2048);
    // int3_hashmap_add(chunkLinks->value, chunk_position, chunk);
    zox_set(e, ChunkLinks, { chunkLinks->value })

    return e;
}

ecs_entity_t create_terrain(ecs_world_t *world, const ecs_entity_t realm, const int3 center_position, const int3 size, const ecs_entity_t prefab_terrain, const ecs_entity_t prefab_chunk) {
    // zox_log(" + terrain size [%ix%ix%i]\n", size.x, size.y, size.z)
    // spawn_terrain_grid(world, real_chunk_scale);
    if (!zox_has(realm, TilemapLink)) {
        zox_log(" ! realm lacking a TilemapLink.\n")
        return 0;
    }
    const ecs_entity_t tilemap = zox_get_value(realm, TilemapLink)
    if (tilemap) {
        zox_set(tilemap, RealmLink, { realm })
    }
    int chunks_total_length = calculate_terrain_chunks_count(size.x, size.y);
    ecs_entity_t terrain_world = spawn_terrain(world, prefab_terrain, tilemap, float3_zero, 1);
    ecs_entity_t chunks[chunks_total_length];
    int3 chunk_positions[chunks_total_length];
    int3 chunk_position = int3_zero;
    for (chunk_position.x = -size.x; chunk_position.x <= size.x; chunk_position.x++) {
        for (chunk_position.z = -size.z; chunk_position.z <= size.z; chunk_position.z++) {
            for (chunk_position.y = -size.y; chunk_position.y <= size.y; chunk_position.y++) {
                const int index = get_chunk_index_3(chunk_position, size.x, size.y);
                if (index < 0 || index >= chunks_total_length) continue;
                const ecs_entity_t chunk = spawn_chunk_terrain(world, prefab_chunk, terrain_world, center_position, chunk_position, real_chunk_scale);
                chunk_positions[index] = chunk_position;
                chunks[index] = chunk;
            }
        }
    }
    // now for all of them, set their neighbors
    for (int i = -size.x; i <= size.x; i++) {
        for (int k = -size.z; k <= size.z; k++) {
            for (int j = -size.y; j <= size.y; j++) {
                set_chunk_neighbors_six_directions(world,
                    chunks[get_chunk_index_2(i, j, k, size.x, size.y)],
                    i == -size.x ? 0 : chunks[get_chunk_index_2(i - 1, j, k, size.x, size.y)],
                    i == size.x ? 0 : chunks[get_chunk_index_2(i + 1, j, k, size.x, size.y)],
                    j == -size.y ? 0 : chunks[get_chunk_index_2(i, j - 1, k, size.x, size.y)],
                    j == size.y ? 0 : chunks[get_chunk_index_2(i, j + 1, k, size.x, size.y)],
                    k == -size.z ? 0 : chunks[get_chunk_index_2(i, j, k - 1, size.x, size.y)],
                    k == size.z ? 0 : chunks[get_chunk_index_2(i, j, k + 1, size.x, size.y)]);
            }
        }
    }
    zox_get_muter(terrain_world, ChunkLinks, chunkLinks)
    chunkLinks->value = create_int3_hashmap(chunks_total_length);
    for (int i = 0; i < chunks_total_length; i++) int3_hashmap_add(chunkLinks->value, chunk_positions[i], chunks[i]);
#ifdef zox_time_create_terrain
    end_timing_absolute("    - create_terrain")
#endif
    return terrain_world;
}

/*
    #ifdef zox_disable_terrain_octrees
        terrain_vertical = 0;
    #endif
    set_chunk_neighbors(world,
        chunks[get_chunk_index_2(i, j, k, terrain_spawn_distance, 0)],
        i == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i - 1, j, k, terrain_spawn_distance, 0)],
        i == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i + 1, j, k, terrain_spawn_distance, 0)],
        k == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k - 1, terrain_spawn_distance, 0)],
        k == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k + 1, terrain_spawn_distance, 0)]);
                #else
                    chunks[index] = spawn_chunk_terrain(world, prefab_terrain_chunk, chunk_position, (float3) { i * real_chunk_scale, 0, k * real_chunk_scale }, 0.5f);
                #endif
*/
