ecs_entity_t prefab_character3D_terrain_spawning;

// we need to check if chunk has generated yet - is there a component for this?

void Characters3SpawnSystem(ecs_iter_t *it) {
    if (disable_npcs) {
        return;
    }
    // todo: dynamically check bounds
    const float3 bounds = (float3) { 0.22f, 0.44f, 0.22f };
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RenderDistanceDirty)
    zox_sys_in(VoxelNode)
    zox_sys_in(NodeDepth)
    zox_sys_in(ChunkPosition)
    zox_sys_in(RenderDistance)
    zox_sys_in(RenderDisabled)
    zox_sys_in(VoxLink)
    zox_sys_out(CharactersSpawned)
    zox_sys_out(CharactersEverSpawned)
    zox_sys_out(EntityLinks)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(RenderDistanceDirty, renderDistanceDirty)
        zox_sys_i(VoxelNode, voxelNode)
        zox_sys_i(NodeDepth, nodeDepth)
        zox_sys_i(RenderDistance, renderDistance)
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(ChunkPosition, chunkPosition)
        zox_sys_i(VoxLink, voxLink)
        zox_sys_o(CharactersSpawned, charactersSpawned)
        zox_sys_o(CharactersEverSpawned, charactersEverSpawned)
        zox_sys_o(EntityLinks, entityLinks)

        const byte is_in_spawn_range = renderDistance->value <= terrain_lod_near;
        const byte is_first_spawn = is_in_spawn_range && !charactersEverSpawned->value;

        // if already spawned, skip spawning, only update LODs
        // if basically all air or solid, no need to spawn
        if (!has_children_VoxelNode(voxelNode)) {
            continue;
        }

        if (!is_first_spawn && renderDistanceDirty->value != zox_dirty_active) {
            continue;
        }

        if (charactersSpawned->value || !is_in_spawn_range) {
            // if (charactersSpawned->value) zox_log("- already_spawned [%i]", entityLinks->length)
            // if (!is_in_spawn_range) zox_log("- out of range")
            continue;
        }
        const byte depth = nodeDepth->value;
        int chunk_length = powers_of_two[depth];
        const byte lod = distance_to_lod_npc(renderDistance->value);
        // zox_log("lod [%i] dist [%i]", lod, renderDistance->value)
        const int3 chunk_dimensions = (int3) { chunk_length, chunk_length, chunk_length };
        int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, chunk_dimensions);

        for (byte j = 0; j < characters_per_chunk_count; j++) {
            // sometimes cannot find a position
            // many spawn checks
            byte3 local_position;
            for (byte k = 0; k < chunk_length; k++) {
                local_position = find_position_on_ground(voxelNode, depth, NULL, 0);
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
            if (!vox) {
                zox_log_error(" vox not found for [%s]", npc_voxes[vox_index])
                continue;
            }
            spawn_character3D_data spawn_data = {
                .prefab = prefab_character3D_terrain_spawning,
                .vox = vox,
                .terrain = voxLink->value,
                .terrain_chunk = e,
                .chunk_position = chunkPosition->value,
                .position = position,
                .rotation = rotation,
                .lod = lod,
                .render_disabled = renderDisabled->value,
            };
            const ecs_entity_t character = spawn_character3(world, spawn_data);
            if (disable_npc_movement) {
                zox_set(character, DisableMovement, { 1 })
            }

            add_to_EntityLinks(entityLinks, character);

            zox_log_spawning("   + npc: %s at [%fx%fx%f] [%i of %i]",  zox_get_name(character), position.x, position.y, position.z, (j + 1), (characters_per_chunk_count))
        }

        if (entityLinks->length >= 1) {
            zox_log_spawning("+ characters spawned [%i] at [%ix%ix%i]", entityLinks->length, chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z)
            // zox_log("+ [%lu] spawned [%i]", e, entityLinks->length)
        }

        charactersSpawned->value = 1;
        charactersEverSpawned->value = 1;
    }
} zox_declare_system(Characters3SpawnSystem)