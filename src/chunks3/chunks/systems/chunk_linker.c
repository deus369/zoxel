// #define zox_debug_chunk_link_system
static inline byte can_have_characters(ecs*, entity);

void zox_log_chunk_removed(ecs *world,
    const entity e,
    const entity e2)
{
#ifdef zox_debug_chunk_link_system
    const int3 chunk_position = zox_get_value(e, ChunkPosition)
    zox_log("- chunk [%s] removed e [%s] [%ix%ix%i]", zox_get_name(e), zox_get_name(e2), chunk_position.x, chunk_position.y, chunk_position.z)
#endif
}

void zox_log_chunk_added(ecs *world,
    const entity e,
    const entity e2)
{
#ifdef zox_debug_chunk_link_system
    const int3 chunk_position = zox_get_value(e, ChunkPosition)
    zox_log("+ chunk [%s] added e [%s] [%ix%ix%i]", zox_get_name(e), zox_get_name(e2), chunk_position.x, chunk_position.y, chunk_position.z)
#endif
}

byte set_entity_chunk(ecs *world,
    const entity e,
    ChunkLink *chunkLink,
    const entity new_chunk)
{
    entity old_chunk = chunkLink->value;
    if (!zox_valid(new_chunk) || old_chunk == new_chunk || !can_have_characters(world, new_chunk)) {
        return 0;
    }
    // remove entity from old chunk
    if (zox_valid(old_chunk)) {
        zox_get_muter(old_chunk, EntityLinks, entityLinks)
        remove_from_EntityLinks(entityLinks, e);
        zox_log_chunk_removed(world, old_chunk, e);
    }
    // add entity to new chunk
    zox_mut_begin(new_chunk, EntityLinks, entityLinks)
    if (add_to_EntityLinks(entityLinks, e)) {
        zox_mut_end(new_chunk, EntityLinks)
        zox_log_chunk_added(world, new_chunk, e);
    } else {
        zox_log_error("failed to add npc to chunk")
    }
    chunkLink->value = new_chunk;
    // now render distabled
    zox_geter_value(new_chunk, RenderDisabled, byte, chunk_render_disabled)
    zox_geter_value(new_chunk, RenderDistance, byte, chunk_render_distance)
    zox_geter_value(e, RenderDisabled, byte, character_render_disabled)
    if (character_render_disabled != chunk_render_disabled) {
        zox_set(e, RenderDisabled, { chunk_render_disabled })
    }
    // now lod
    // calculate_lods
    // zox_geter_value(e, NodeDepth, byte, node_depth)
    // todo: this should be used by system itself
    if (zox_has(e, RenderLod)) {
        zox_geter_value(e, RenderLod, byte, old_lod)
        const byte lod = distance_to_lod_npc(chunk_render_distance);
        if (old_lod != lod) {
            zox_set(e, RenderLod, { lod })
            zox_set(e, RenderLodDirty, { zox_dirty_trigger } )
        }
    }
    return 1;
}

void ChunkLinkSystem(iter *it) {
    // const byte depth = terrain_depth;
    // const int3 chunk_dimensions = int3_single(powers_of_two[depth]);
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(VoxLink)
    zox_sys_out(Position3D)
    zox_sys_out(ChunkPosition)
    zox_sys_out(ChunkLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(Position3D, position)
        zox_sys_o(ChunkPosition, chunkPosition)
        zox_sys_o(ChunkLink, chunkLink)
        if (!zox_valid(voxLink->value)) {
            continue; // these shouldn't be here
        }
        zox_geter_value(voxLink->value, VoxScale, float, terrain_scale);
        zox_geter_value(voxLink->value, NodeDepth, byte, node_depth);
        // const float3 real_position = position3D->value;
        const int3 new_chunk_position = real_position_to_chunk_position(
            position->value,
            powers_of_two[node_depth],
            terrain_scale);
        byte is_set = !chunkLink->value || (!int3_equals(new_chunk_position, chunkPosition->value));
        if (is_set) {
            zox_geter(voxLink->value, ChunkLinks, chunkLinks)
            const entity chunk = int3_hashmap_get(chunkLinks->value, new_chunk_position);
            if (set_entity_chunk(world, e, chunkLink, chunk)) {
                chunkPosition->value = new_chunk_position;
            }
        }
    }
} zox_declare_system(ChunkLinkSystem)