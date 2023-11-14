// #define zox_debug_chunk_link_system
// #define zox_debug_chunk_link_system_test

void set_entity_chunk(ecs_world_t *world, ecs_entity_t e, ChunkLink *chunkLink, ecs_entity_t new_chunk) {
    ecs_entity_t old_chunk = chunkLink->value;
    if (old_chunk != new_chunk && new_chunk) {
        chunkLink->value = new_chunk;
        // remove entity from old chunk
        if (old_chunk) {
            EntityLinks *entityLinks = zox_get_mut(old_chunk, EntityLinks)
            remove_from_memory_component(entityLinks, ecs_entity_t, e)
            zox_modified(old_chunk, EntityLinks)
#ifdef zox_debug_chunk_link_system
            const int3 chunk_position = zox_get_value(old_chunk, ChunkPosition)
            zox_log(" > chunk [%lu] removed e [%lu] [%ix%ix%i]\n", old_chunk, e, chunk_position.x, chunk_position.y, chunk_position.z)
#endif
        }
        // add entity to new chunk
        if (new_chunk) {
            EntityLinks *entityLinks = zox_get_mut(new_chunk, EntityLinks)
            // if (!entityLinks->value) zox_log(" > chunk [%lu] entityLinks is null\n", new_chunk)
            add_to_memory_component(entityLinks, ecs_entity_t, e)
            zox_modified(new_chunk, EntityLinks)
#ifdef zox_debug_chunk_link_system
            const int3 chunk_position = zox_get_value(new_chunk, ChunkPosition)
            zox_log(" > chunk [%lu] added e [%lu] [%ix%ix%i] at length [%i]\n", new_chunk, e, chunk_position.x, chunk_position.y, chunk_position.z, entityLinks->length)
#endif
        }
        // else zox_log("   > moving character into emptpy chunk, from [%lu]\n", old_chunk)
        // zoxel_log(" > entity %lu moving chunks\n", e);
    }
}

void set_entity_terrain_chunk_position(ecs_world_t *world, ecs_entity_t e, const VoxLink *voxLink, ChunkLink *chunkLink, ChunkPosition *chunkPosition, int3 chunk_position) {
    chunkPosition->value = chunk_position;
    const ChunkLinks *chunkLinks = zox_get(voxLink->value, ChunkLinks)
    ecs_entity_t found_chunk = int3_hash_map_get(chunkLinks->value, chunk_position);
    set_entity_chunk(world, e, chunkLink, found_chunk);
}

void ChunkLinkSystem(ecs_iter_t *it) {
    const VoxLink *voxLinks = ecs_field(it, VoxLink, 2);
    const Position3D *position3Ds = ecs_field(it, Position3D, 3);
    ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 4);
    ChunkLink *chunkLinks = ecs_field(it, ChunkLink, 5);
    // VoxelPosition *voxelPositions = ecs_field(it, VoxelPosition, 6);
    for (int i = 0; i < it->count; i++) {
        const VoxLink *voxLink = &voxLinks[i];
        if (!voxLink->value) continue;
        ecs_entity_t e = it->entities[i];
        const Position3D *position3D = &position3Ds[i];
        ChunkPosition *chunkPosition = &chunkPositions[i];
        ChunkLink *chunkLink = &chunkLinks[i];
        float3 real_position = position3D->value;
        int3 new_chunk_position = get_chunk_position(real_position, default_chunk_size);
        if (!chunkLink->value) set_entity_terrain_chunk_position(world, e, voxLink, chunkLink, chunkPosition, new_chunk_position);
        else if (!int3_equals(new_chunk_position, chunkPosition->value)) set_entity_terrain_chunk_position(world, e, voxLink, chunkLink, chunkPosition, new_chunk_position);
    }
} zox_declare_system(ChunkLinkSystem)

/*#ifdef zox_debug_chunk_link_system
    zox_log(" > set chunk [%lu] [%ix%ix%i]\n", chunkLink->value, chunk_position.x, chunk_position.y, chunk_position.z)
    zox_log("     > chunk position [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z)
    // test
    // const ChunkPosition *chunkPosition2 = zox_get(chunkLink->value, ChunkPosition)
    // zox_log("     > test chunk position [%ix%ix%i]\n", chunkPosition2->value.x, chunkPosition2->value.y, // chunkPosition2->value.z)
#endif
#ifdef zox_debug_chunk_link_system_test
    const ChunkPosition *chunkPosition2 = zox_get(chunkLink->value, ChunkPosition)
    if (!int3_equals(chunkPosition2->value, chunk_position)) zox_logg("     - chunk position is not equal to set one\n")
#endif*/
