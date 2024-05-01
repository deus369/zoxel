// #define zox_debug_chunk_link_system
// #define zox_debug_chunk_link_system_test

void set_entity_chunk(ecs_world_t *world, const ecs_entity_t e, ChunkLink *chunkLink, const ecs_entity_t new_chunk) {
    ecs_entity_t old_chunk = chunkLink->value;
    if (old_chunk != new_chunk && new_chunk) {
        if (!zox_alive(new_chunk)) chunkLink->value = 0;
        else chunkLink->value = new_chunk;
        // remove entity from old chunk
        if (old_chunk && zox_alive(old_chunk)) {
            EntityLinks *entityLinks = zox_get_mut(old_chunk, EntityLinks)
            remove_from_memory_component(entityLinks, ecs_entity_t, e)
            zox_modified(old_chunk, EntityLinks)
#ifdef zox_debug_chunk_link_system
            const int3 chunk_position = zox_get_value(old_chunk, ChunkPosition)
            zox_log(" > chunk [%lu] removed e [%lu] [%ix%ix%i]\n", old_chunk, e, chunk_position.x, chunk_position.y, chunk_position.z)
#endif
        }
        // add entity to new chunk
        if (new_chunk && zox_alive(new_chunk)) {
            EntityLinks *entityLinks = zox_get_mut(new_chunk, EntityLinks)
            if (!entityLinks) return;
            if (add_to_EntityLinks(entityLinks, e)) zox_modified(new_chunk, EntityLinks)
#ifdef zox_debug_chunk_link_system
            const int3 chunk_position = zox_get_value(new_chunk, ChunkPosition)
            zox_log(" > chunk [%lu] added e [%lu] [%ix%ix%i] at length [%i]\n", new_chunk, e, chunk_position.x, chunk_position.y, chunk_position.z, entityLinks->length)
#endif
        }
    }
}

void set_entity_terrain_chunk_position(ecs_world_t *world, const ecs_entity_t e, const VoxLink *voxLink, ChunkLink *chunkLink, ChunkPosition *chunkPosition, int3 chunk_position) {
    chunkPosition->value = chunk_position;
    const ChunkLinks *chunkLinks = zox_get(voxLink->value, ChunkLinks)
    const ecs_entity_t found_chunk = int3_hash_map_get(chunkLinks->value, chunk_position);
    set_entity_chunk(world, e, chunkLink, found_chunk);
}

void ChunkLinkSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(VoxLink, voxLinks, 2)
    zox_field_out(Position3D, position3Ds, 3)
    zox_field_out(ChunkPosition, chunkPositions, 4)
    zox_field_out(ChunkLink, chunkLinks, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        if (!zox_alive(voxLink->value)) continue; // these shouldn't be here
        zox_field_e()
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_out(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i_out(ChunkLink, chunkLinks, chunkLink)
        const float3 real_position = position3D->value;
        const int3 new_chunk_position = get_chunk_position(real_position, default_chunk_size);
        if (!chunkLink->value) set_entity_terrain_chunk_position(world, e, voxLink, chunkLink, chunkPosition, new_chunk_position);
        else if (!int3_equals(new_chunk_position, chunkPosition->value)) set_entity_terrain_chunk_position(world, e, voxLink, chunkLink, chunkPosition, new_chunk_position);
    }
} zox_declare_system(ChunkLinkSystem)
