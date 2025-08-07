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

ecs_entity_t spawn_terrain(
    ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t tilemap,
    const float3 position,
    const byte depth,
    const float scale
) {
    zox_instance(prefab);
    zox_name("terrain");
    zox_set(e, Position3D, { position });
    zox_set(e, VoxScale, { scale });
    zox_set(e, NodeDepth, { depth });
    // zox_set(e, Scale1D, { scale })
    if (tilemap) {
        zox_set(e, TilemapLink, { tilemap });
        // did tilemap have a voxlink previously
        zox_set(tilemap, VoxLink, { e })    // link tilemap to terrain
    }
    local_terrain = e;
    return e;
}

// todo: pass in through struct
ecs_entity_t spawn_terrain_streaming(
    ecs_world_t *world,
    const ecs_entity_t realm,
    const int3 center_position,
    const int3 size,
    const ecs_entity_t prefab_terrain,
    const ecs_entity_t prefab_chunk
) {
    // const int3 chunk_position = int3_zero;
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

    float terrain_scale = 0.5f; // 0.5f | 1
    ecs_entity_t e = spawn_terrain(
        world,
        prefab_terrain,
        tilemap,
        float3_zero,
        terrain_depth,
        terrain_scale);
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
