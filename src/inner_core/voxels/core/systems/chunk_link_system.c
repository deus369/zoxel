// #define zoxel_debug_chunk_link_system

void set_entity_terrain_chunk_position(ecs_world_t *world, ChunkLink *chunkLink, ChunkPosition *chunkPosition, int3 chunk_position) {
    chunkPosition->value = chunk_position;
    const ChunkLinks *chunkLinks = ecs_get(world, main_terrain_world, ChunkLinks);
    chunkLink->value = int3_hash_map_get(chunkLinks->value, chunk_position);
    #ifdef zoxel_debug_chunk_link_system
        zoxel_log(" > set chunk [%lu] [%ix%ix%i]\n", chunkLink->value, chunk_position.x, chunk_position.y, chunk_position.z);
        zoxel_log("     > chunk position [%ix%ix%i]\n", chunk_position.x, chunk_position.y, chunk_position.z);
        // test
        const ChunkPosition *chunkPosition2 = ecs_get(world, chunkLink->value, ChunkPosition);
        zoxel_log("     > test chunk position [%ix%ix%i]\n", chunkPosition2->value.x, chunkPosition2->value.y, chunkPosition2->value.z);
    #endif
}

void ChunkLinkSystem(ecs_iter_t *it) {
    const int3 chunk_size = (int3) { 16, 16, 16 };
    const Position3D *position3Ds = ecs_field(it, Position3D, 2);
    ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 3);
    ChunkLink *chunkLinks = ecs_field(it, ChunkLink, 4);
    for (int i = 0; i < it->count; i++) {
        ChunkPosition *chunkPosition = &chunkPositions[i];
        ChunkLink *chunkLink = &chunkLinks[i];
        const Position3D *position3D = &position3Ds[i];
        int3 new_chunk_position = get_chunk_position(position3D->value, chunk_size);
        if (chunkLink->value == 0) {
            set_entity_terrain_chunk_position(world, chunkLink, chunkPosition, new_chunk_position);
        } else {
            if (!int3_equals(new_chunk_position, chunkPosition->value)) {
                set_entity_terrain_chunk_position(world, chunkLink, chunkPosition, new_chunk_position);
            }
            /*#ifdef zoxel_debug_chunk_link_system
                else {
                    zoxel_log(" - chunk position [%ix%ix%i]\n", new_chunk_position.x, new_chunk_position.y, new_chunk_position.z);
                }
            #endif*/
        }
    }
}
zoxel_declare_system(ChunkLinkSystem)