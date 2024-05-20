void set_entity_chunk(ecs_world_t *world, const ecs_entity_t e, ChunkLink *chunkLink, const ecs_entity_t new_chunk) {
    ecs_entity_t old_chunk = chunkLink->value;
    if (old_chunk != new_chunk && new_chunk) {
        // set characters link to chunk
        if (!zox_alive(new_chunk)) chunkLink->value = 0;
        else chunkLink->value = new_chunk;
        // if player, dont link chunk to character
        if (zox_has(e, DisableReverseLinkChunk)) return;
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
