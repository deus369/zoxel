ecs_entity_t prefab_character3D_terrain_spawning;

void Characters3DSpawnSystem(ecs_iter_t *it) {
    const float3 bounds = (float3) { 0.25f, 0.5f, 0.25f };  // used for positioning, we need to uhh spawn first and then place... one day
    if (disable_npcs) {
        return;
    }
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ChunkLodDirty)
    zox_sys_in(ChunkOctree)
    zox_sys_in(NodeDepth)
    zox_sys_in(ChunkPosition)
    zox_sys_in(RenderDistance)
    zox_sys_in(RenderDisabled)
    zox_sys_in(VoxLink)
    zox_sys_out(EntityLinks)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_sys_i(ChunkLodDirty, chunkLodDirty)
        zox_sys_i(ChunkOctree, chunkOctree)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(ChunkPosition, chunkPosition)
        zox_sys_i(VoxLink, voxLink)
        zox_sys_o(EntityLinks, entityLinks)
        // if already spawned, skip spawning, only update LODs
        // if basically all air or solid, no need to spawn
        if (chunkLodDirty->value != chunk_lod_state_characters_spawn || chunkOctree->nodes == NULL || entityLinks->length || renderDistance->value > character_render_distance) {
            continue;
        }
        const byte depth = nodeDepth->value;
        int chunk_length = powers_of_two[depth];
        const byte vox_lod = get_voxes_lod_from_camera_distance(renderDistance->value);
        const int3 chunk_dimensions = (int3) { chunk_length, chunk_length, chunk_length };
        int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, chunk_dimensions);
        zox_log_spawning("> chunk [%lu] at [%ix%ix%i]", e, chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z)
        for (byte j = 0; j < characters_per_chunk_count; j++) {
            // sometimes cannot find a position
            // many spawn checks
            byte3 local_position;
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
        if (entityLinks->length >= 1) {
            zox_log_spawning("  > total: %i", entityLinks->length)
        }
    }
} zox_declare_system(Characters3DSpawnSystem)