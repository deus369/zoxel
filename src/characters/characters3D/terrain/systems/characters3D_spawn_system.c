ecs_entity_t prefab_character3D_terrain_spawning;

void Characters3DSpawnSystem(ecs_iter_t *it) {
    const float3 bounds = (float3) { 0.25f, 0.5f, 0.25f };
    if (disable_npcs) {
        return;
    }
    zox_field_world()
    byte fi = 1;
    zox_field_in(ChunkLodDirty, chunkLodDirtys, fi++)
    zox_field_in(ChunkOctree, chunkOctrees, fi++)
    zox_field_in(NodeDepth, nodeDepths, fi++)
    zox_field_in(ChunkPosition, chunkPositions, fi++)
    zox_field_in(RenderDistance, renderDistances, fi++)
    zox_field_in(RenderDisabled, renderDisableds, fi++)
    zox_field_in(VoxLink, voxLinks, fi++)
    zox_field_out(EntityLinks, entityLinkss, fi++)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(ChunkLodDirty, chunkLodDirtys, chunkLodDirty)
        zox_field_i(ChunkOctree, chunkOctrees, chunkOctree)
        zox_field_i(NodeDepth, nodeDepths, nodeDepth)
        zox_field_i(RenderDistance, renderDistances, renderDistance)
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i(VoxLink, voxLinks, voxLink)
        zox_field_o(EntityLinks, entityLinkss, entityLinks)
        if (chunkLodDirty->value != chunk_lod_state_characters_spawn) {
            continue;
        }
        if (chunkOctree->nodes == NULL) {
            continue;   // if basically all air or solid, no need to spawn
        }
        // if already spawned, skip spawning, only update LODs
        if (entityLinks->length) {
            continue;
        }
        if (renderDistance->value > character_render_distance) {
            continue;
        }
        const byte depth = nodeDepth->value;
        int chunk_length = powers_of_two[depth];
        const byte vox_lod = get_voxes_lod_from_camera_distance(renderDistance->value);
        const int3 chunk_dimensions = (int3) { chunk_length, chunk_length, chunk_length };
        int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, chunk_dimensions);
        // find if chunk has any air position - free place to spawn - spawn characters in this chunk
        // zox_geter(voxLink->value, VoxScale, voxScale)
        // ecs_entity_t_array_d* entities = create_ecs_entity_t_array_d(initial_dynamic_array_size);
        zox_log_spawning("> chunk [%lu] at [%ix%ix%i]", e, chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z)
        for (byte j = 0; j < characters_per_chunk_count; j++) {
            // sometimes cannot find a position
            byte3 local_position;
            // many spawn checks
            for (byte k = 0; k < chunk_length; k++) {
                local_position = find_position_on_ground(chunkOctree, depth, NULL, 0);
                if (!byte3_equals(byte3_full, local_position)) {
                    break;
                }
            }
            if (byte3_equals(byte3_full, local_position)) {
                zox_log_spawning("! failed to spawn npc\n")
                continue;
            }

            float3 position = local_to_real_position_character(local_position, chunk_voxel_position, bounds, depth, 1); // voxScale->value);
            float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });
            int vox_index = rand() % npc_vox_index_count;
            const ecs_entity_t vox = string_hashmap_get(files_hashmap_voxes, new_string_data(npc_voxes[vox_index]));
            if (vox) {
                spawn_character3D_data spawn_data = {
                    .prefab = prefab_character3D_terrain_spawning,
                    .vox = vox,
                    .terrain = voxLink->value,
                    .terrain_chunk = e,
                    .position = position,
                    .rotation = rotation,
                    .lod = vox_lod,
                    .render_disabled = renderDisabled->value,
                };
                const ecs_entity_t character = spawn_character3D(world, spawn_data);
                // add_to_ecs_entity_t_array_d(entities, character);
                add_to_EntityLinks(entityLinks, character);
                zox_log_spawning("   + npc: %s at [%fx%fx%f] [%i of %i]",  zox_get_name(character), position.x, position.y, position.z, (j + 1), (characters_per_chunk_count))
            } else {
                zox_log("! vox not found for [%s]\n", npc_voxes[vox_index])
            }
        }
        // clear_memory_component(EntityLinks, entityLinks);
        // entityLinks->length = entities->size;
        // entityLinks->value = finalize_ecs_entity_t_array_d(entities);
        // on_memory_component_created(entityLinks, EntityLinks)
        if (entityLinks->length >= 1) {
            zox_log_spawning("  > total: %i", entityLinks->length)
        }
    }
} zox_declare_system(Characters3DSpawnSystem)