void ChunkLinkSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(VoxLink, voxLinks, 1)
    zox_field_out(Position3D, position3Ds, 2)
    zox_field_out(ChunkPosition, chunkPositions, 3)
    zox_field_out(ChunkLink, chunkLinks, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value || !zox_alive(voxLink->value)) {
            continue; // these shouldn't be here
        }
        zox_field_e()
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_o(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_o(ChunkLink, chunkLinks, chunkLink)
        const float3 real_position = position3D->value;
        const int3 new_chunk_position = real_position_to_chunk_position(real_position, default_chunk_size);
        if (!chunkLink->value) set_entity_terrain_chunk_position(world, e, voxLink, chunkLink, chunkPosition, new_chunk_position);
        else if (!int3_equals(new_chunk_position, chunkPosition->value)) set_entity_terrain_chunk_position(world, e, voxLink, chunkLink, chunkPosition, new_chunk_position);
    }
} zox_declare_system(ChunkLinkSystem)