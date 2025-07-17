// #define zox_debug_chunk_link_system
// extern byte get_voxes_lod_from_camera_distance(byte distance_to_camera);

byte set_entity_chunk(ecs_world_t *world,
    const ecs_entity_t e,
    ChunkLink *chunkLink,
    const ecs_entity_t chunk)
{
    if (!zox_valid(chunk)) {
        return 0;
    }
    ecs_entity_t old_chunk = chunkLink->value;
    if (old_chunk == chunk) {
        return 0;
    }
    chunkLink->value = chunk;
    // remove entity from old chunk
    if (zox_valid(old_chunk)) {
        zox_get_muter(old_chunk, EntityLinks, entityLinks)
        remove_from_EntityLinks(entityLinks, e);
#ifdef zox_debug_chunk_link_system
        const int3 chunk_position = zox_get_value(old_chunk, ChunkPosition)
        zox_log(" > chunk [%s] removed e [%s] [%ix%ix%i]\n", zox_get_name(old_chunk), zox_get_name(e), chunk_position.x, chunk_position.y, chunk_position.z)
#endif
    }
    // add entity to new chunk
    if (zox_valid(chunk)) {
        zox_mut_begin(chunk, EntityLinks, entityLinks)
        if (add_to_EntityLinks(entityLinks, e)) {
            zox_mut_end(chunk, EntityLinks)
        }
#ifdef zox_debug_chunk_link_system
        const int3 chunk_position = zox_get_value(chunk, ChunkPosition)
        zox_log(" > chunk [%s] added e [%s] [%ix%ix%i] at length [%i]\n", zox_get_name(chunk), zox_get_name(e), chunk_position.x, chunk_position.y, chunk_position.z, entityLinks->length)
#endif
    }
    // zox_log("[set_entity_chunk] setting character [%lu] chunk: %lu", e, chunk)
    // Set RenderLod and RenderDisabled based on chunk!
    if (chunk) {
        // now render distabled
        const byte chunk_render_disabled = zox_get_value(chunk, RenderDisabled)
        const byte character_render_disabled = zox_get_value(e, RenderDisabled)
        if (character_render_disabled != chunk_render_disabled) {
            zox_set(e, RenderDisabled, { chunk_render_disabled })
        }
        // now lod
        const byte chunk_render_lod = zox_get_value(chunk, RenderLod)

        // calculate_lods
        zox_geter_value(chunk, RenderDistance, byte, chunk_render_distance)
        zox_geter_value(e, NodeDepth, byte, node_depth)
        const byte new_lod = distance_to_lod_npc(chunk_render_distance);

        zox_geter_value(e, RenderLod, byte, lod)
        if (lod != new_lod) {
            zox_set(e, RenderLod, { new_lod })
        }
    }
    return 1;
}

void set_entity_terrain_chunk_position(ecs_world_t *world,
    const ecs_entity_t e,
    const VoxLink *voxLink,
    ChunkLink *chunkLink,
    ChunkPosition *chunkPosition,
    int3 chunk_position)
{
    zox_geter(voxLink->value, ChunkLinks, chunkLinks)
    const ecs_entity_t chunk = int3_hashmap_get(chunkLinks->value, chunk_position);
    if (set_entity_chunk(world, e, chunkLink, chunk)) {
        chunkPosition->value = chunk_position;
    }
}

void ChunkLinkSystem(ecs_iter_t *it) {
    const byte depth = terrain_depth;
    const int3 chunk_dimensions = int3_single(powers_of_two[depth]);
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(VoxLink)
    zox_sys_out(Position3D)
    zox_sys_out(ChunkPosition)
    zox_sys_out(ChunkLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(Position3D, position3D)
        zox_sys_o(ChunkPosition, chunkPosition)
        zox_sys_o(ChunkLink, chunkLink)
        if (!zox_valid(voxLink->value)) {
            continue; // these shouldn't be here
        }
        const float3 real_position = position3D->value;
        const int3 new_chunk_position = real_position_to_chunk_position(real_position, chunk_dimensions, depth);
        if (!chunkLink->value) {
            set_entity_terrain_chunk_position(world, e, voxLink, chunkLink, chunkPosition, new_chunk_position);
        } else if (!int3_equals(new_chunk_position, chunkPosition->value)) {
            set_entity_terrain_chunk_position(world, e, voxLink, chunkLink, chunkPosition, new_chunk_position);
        }
    }
} zox_declare_system(ChunkLinkSystem)