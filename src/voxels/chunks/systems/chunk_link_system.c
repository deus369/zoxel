extern byte get_voxes_lod_from_camera_distance(byte distance_to_camera);

void set_entity_chunk(ecs_world_t *world, const ecs_entity_t e, ChunkLink *chunkLink, const ecs_entity_t new_chunk) {
    if (!zox_valid(new_chunk)) {
        return;
    }
    ecs_entity_t old_chunk = chunkLink->value;
    if (old_chunk != new_chunk) {
        // set characters link to chunk
        if (!zox_alive(new_chunk)) chunkLink->value = 0;
        else chunkLink->value = new_chunk;
        // if player, dont link chunk to character
        if (zox_has(e, DisableReverseLinkChunk)) return;
        // Set RenderLod and RenderDisabled based on chunk!
        if (new_chunk) {
            // now render distabled
            const byte chunk_render_disabled = zox_get_value(new_chunk, RenderDisabled)
            const byte character_render_disabled = zox_get_value(e, RenderDisabled)
            if (character_render_disabled != chunk_render_disabled) {
                zox_set(e, RenderDisabled, { chunk_render_disabled })
            }
            // now lod
            const byte chunk_render_lod = zox_get_value(new_chunk, RenderLod)
            const byte character_render_lod = zox_get_value(e, RenderLod)
            if (character_render_lod != chunk_render_lod) {
                zox_set(e, RenderLod, { chunk_render_lod })
            }
        }
        // remove entity from old chunk
        if (zox_valid(old_chunk)) {
            EntityLinks *entityLinks = zox_get_mut(old_chunk, EntityLinks)
            remove_from_memory_component(entityLinks, ecs_entity_t, e)
            zox_modified(old_chunk, EntityLinks)
            #ifdef zox_debug_chunk_link_system
            const int3 chunk_position = zox_get_value(old_chunk, ChunkPosition)
            zox_log(" > chunk [%lu] removed e [%" PRIu64 "] [%ix%ix%i]\n", old_chunk, e, chunk_position.x, chunk_position.y, chunk_position.z)
            #endif
        }
        // add entity to new chunk
        if (zox_valid(new_chunk)) {
            EntityLinks *entityLinks = zox_get_mut(new_chunk, EntityLinks)
            if (add_to_EntityLinks(entityLinks, e)) {
                zox_modified(new_chunk, EntityLinks)
            }
            #ifdef zox_debug_chunk_link_system
            const int3 chunk_position = zox_get_value(new_chunk, ChunkPosition)
            zox_log(" > chunk [%lu] added e [%" PRIu64 "] [%ix%ix%i] at length [%i]\n", new_chunk, e, chunk_position.x, chunk_position.y, chunk_position.z, entityLinks->length)
            #endif
        }
    }
}

void set_entity_terrain_chunk_position(ecs_world_t *world, const ecs_entity_t e, const VoxLink *voxLink, ChunkLink *chunkLink, ChunkPosition *chunkPosition, int3 chunk_position) {
    chunkPosition->value = chunk_position;
    const ChunkLinks *chunkLinks = zox_get(voxLink->value, ChunkLinks)
    const ecs_entity_t found_chunk = int3_hashmap_get(chunkLinks->value, chunk_position);
    set_entity_chunk(world, e, chunkLink, found_chunk);
}

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
        if (!chunkLink->value) {
            set_entity_terrain_chunk_position(world, e, voxLink, chunkLink, chunkPosition, new_chunk_position);
        } else if (!int3_equals(new_chunk_position, chunkPosition->value)) {
            set_entity_terrain_chunk_position(world, e, voxLink, chunkLink, chunkPosition, new_chunk_position);
        }
    }
} zox_declare_system(ChunkLinkSystem)