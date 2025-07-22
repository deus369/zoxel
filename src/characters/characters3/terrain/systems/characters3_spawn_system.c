extern ecs_entity_t prefab_character3_npc;
extern ecs_entity_t prefab_character3_instanced_npc;
extern void on_spawned_character3_npc(ecs_world_t*, const ecs_entity_t);
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
        const int3 chunk_dimensions = (int3) { chunk_length, chunk_length, chunk_length };
        int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, chunk_dimensions);
        ecs_entity_t terrain = voxLink->value;
        zox_geter_value(terrain, RealmLink, ecs_entity_t, realm)
        zox_geter(realm, CharacterLinks, characters)
        zox_geter_value(realm, CharactersChanceMax, byte, max_chance)
        byte found_position = 0;
        float3 position;
        for (byte j = 0; j < character_spawn_rate; j++) {

            // 1) Find a npc to place
            // find random from realm characters
            byte chance_current = 0;
            byte chance_rolled = rand() % max_chance;
            ecs_entity_t vox = 0;
            for (byte k = 0; k < characters->length; k++) {
                ecs_entity_t meta = characters->value[k];
                zox_geter_value(meta, SpawnChance, byte, chance)
                chance_current += chance;
                if (chance_rolled <= chance_current) {
                    vox = zox_get_value(meta, ModelLink)
                    break;
                }
            }
            if (!vox) {
                zox_log_error("failed to find a spawn character_meta")
                continue;
            }

            // 2) find a place for our new npc
            // sometimes cannot find a position
            // many spawn checks
            if (!found_position) {
                if (disable_npc_positioner) {
                    found_position = 1;
                }
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
                position = local_to_real_position_character(local_position, chunk_voxel_position, bounds, depth, 1);
            }
            float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });

            // 3) Finally we spawn and link
            spawn_character3D_data spawn_data = {
                .prefab = is_testing_instancing ? prefab_character3_instanced_npc : prefab_character3_npc,
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
            on_spawned_character3_npc(world, character);
            add_to_EntityLinks(entityLinks, character);

            if (is_testing_instancing) {
                zox_geter_value(vox, VoxScale, float, meta_vox_scale)
                zox_geter_value(vox, ChunkSize, int3, meta_chunk_size)
                float3 meta_bounds = calculate_vox_bounds(meta_chunk_size, meta_vox_scale);
                zox_set(character, Bounds3D, { meta_bounds })
                // zox_set(character, Scale1D, { 2 * vox_model_scale })
                // zox_log("vox_model_scale: %f - %f", vox_model_scale, meta_vox_scale)
            }

            zox_log_spawning("   + npc: %s at [%fx%fx%f] [%i of %i]",  zox_get_name(character), position.x, position.y, position.z, (j + 1), (character_spawn_rate))
        }

        if (entityLinks->length >= 1) {
            zox_log_spawning("+ characters spawned [%i] at [%ix%ix%i]", entityLinks->length, chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z)
            // zox_log("+ [%lu] spawned [%i]", e, entityLinks->length)
        }

        charactersSpawned->value = 1;
        charactersEverSpawned->value = 1;
    }
} zox_declare_system(Characters3SpawnSystem)