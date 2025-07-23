// #define zox_debug_chunk_link_system

void zox_log_chunk_removed(ecs_world_t *world,
    const ecs_entity_t e,
    const ecs_entity_t e2)
{
#ifdef zox_debug_chunk_link_system
    const int3 chunk_position = zox_get_value(e, ChunkPosition)
    zox_log("- chunk [%s] removed e [%s] [%ix%ix%i]", zox_get_name(e), zox_get_name(e2), chunk_position.x, chunk_position.y, chunk_position.z)
#endif
}

void zox_log_chunk_added(ecs_world_t *world,
    const ecs_entity_t e,
    const ecs_entity_t e2)
{
#ifdef zox_debug_chunk_link_system
    const int3 chunk_position = zox_get_value(e, ChunkPosition)
    zox_log("+ chunk [%s] added e [%s] [%ix%ix%i]", zox_get_name(e), zox_get_name(e2), chunk_position.x, chunk_position.y, chunk_position.z)
#endif
}

byte set_entity_chunk(ecs_world_t *world,
    const ecs_entity_t e,
    ChunkLink *chunkLink,
    const ecs_entity_t new_chunk)
{
    ecs_entity_t old_chunk = chunkLink->value;
    if (!zox_valid(new_chunk) || old_chunk == new_chunk) {
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
        zox_log_chunk_removed(world, new_chunk, e);
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
        zox_geter_value(e, RenderLod, byte, character_lod)
        const byte new_character_lod = distance_to_lod_npc(chunk_render_distance);
        if (character_lod != new_character_lod) {
            zox_set(e, RenderLod, { new_character_lod })
            zox_set(e, RenderLodDirty, { zox_dirty_trigger } )
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