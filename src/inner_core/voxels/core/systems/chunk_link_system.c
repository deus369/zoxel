void set_entity_chunk(ecs_world_t *world, ecs_entity_t e, ChunkLink *chunkLink, ecs_entity_t new_chunk) {
    ecs_entity_t old_chunk = chunkLink->value;
    if (old_chunk != new_chunk) {
        chunkLink->value = new_chunk;
        // remove entity from old chunk
        if (old_chunk != 0) {
            EntityLinks *entityLinks = ecs_get_mut(world, old_chunk, EntityLinks);
            remove_from_memory_component(entityLinks, ecs_entity_t, e)
            ecs_modified(world, old_chunk, EntityLinks);
        }
        // add entity to new chunk
        if (new_chunk != 0) {
            EntityLinks *entityLinks2 = ecs_get_mut(world, new_chunk, EntityLinks);
            add_to_memory_component(entityLinks2, ecs_entity_t, e)
            ecs_modified(world, new_chunk, EntityLinks);
        }
        // zoxel_log(" > entity %lu moving chunks\n", e);
    }
}

void set_entity_terrain_chunk_position(ecs_world_t *world, ecs_entity_t e, const VoxLink *voxLink, ChunkLink *chunkLink, ChunkPosition *chunkPosition, int3 chunk_position) {
    chunkPosition->value = chunk_position;
    const ChunkLinks *chunkLinks = ecs_get(world, voxLink->value, ChunkLinks);
    set_entity_chunk(world, e, chunkLink, int3_hash_map_get(chunkLinks->value, chunk_position));
    #ifdef zoxel_debug_chunk_link_system
        zoxel_log(" > set chunk [%lu] [%ix%ix%i]\n", chunkLink->value, chunk_position.x, chunk_position.y, chunk_position.z);
        zoxel_log("     > chunk position [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z);
        // test
        const ChunkPosition *chunkPosition2 = ecs_get(world, chunkLink->value, ChunkPosition);
        zoxel_log("     > test chunk position [%ix%ix%i]\n", chunkPosition2->value.x, chunkPosition2->value.y, chunkPosition2->value.z);
    #endif
    #ifdef zoxel_debug_chunk_link_system_test
        const ChunkPosition *chunkPosition2 = ecs_get(world, chunkLink->value, ChunkPosition);
        if (!int3_equals(chunkPosition2->value, chunk_position)) {
            zoxel_log("     - chunk position is not equal to set one\n");
        }
    #endif
}

void ChunkLinkSystem(ecs_iter_t *it) {
    const VoxLink *voxLinks = ecs_field(it, VoxLink, 2);
    const Position3D *position3Ds = ecs_field(it, Position3D, 3);
    ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 4);
    ChunkLink *chunkLinks = ecs_field(it, ChunkLink, 5);
    for (int i = 0; i < it->count; i++) {
        const Position3D *position3D = &position3Ds[i];
        const VoxLink *voxLink = &voxLinks[i];
        ChunkPosition *chunkPosition = &chunkPositions[i];
        ChunkLink *chunkLink = &chunkLinks[i];
        float3 real_position = position3D->value;
        // real_position.y -= 0.25f;
        int3 new_chunk_position = get_chunk_position(real_position, default_chunk_size);
        if (chunkLink->value == 0) {
            set_entity_terrain_chunk_position(world, it->entities[i], voxLink, chunkLink, chunkPosition, new_chunk_position);
        } else {
            if (!int3_equals(new_chunk_position, chunkPosition->value)) {
                set_entity_terrain_chunk_position(world, it->entities[i], voxLink, chunkLink, chunkPosition, new_chunk_position);
            }
        }
    }
}
zox_declare_system(ChunkLinkSystem)

/*ecs_entity_t old_chunk = chunkLink->value;
chunkLink->value = int3_hash_map_get(chunkLinks->value, chunk_position);
if (old_chunk != chunkLink->value) {
    zoxel_log("entity %lu moving chunks\n", e);
    // remove entity from old chunk
    // add entity to new chunk
    EntityLinks *entityLinks = ecs_get_mut(world, old_chunk, EntityLinks);
    remove_from_memory_component(entityLinks, ecs_entity_t, e)
    ecs_modified(world, old_chunk, EntityLinks);
    EntityLinks *entityLinks2 = ecs_get_mut(world, chunkLink->value, EntityLinks);
    add_to_memory_component(entityLinks2, ecs_entity_t, e)
    ecs_modified(world, chunkLink->value, EntityLinks);
}*/