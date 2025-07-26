
extern void on_spawned_character3_npc(ecs_world_t*, const ecs_entity_t);
// we need to check if chunk has generated yet - is there a component for this?

void Characters3SpawnSystem(ecs_iter_t *it) {
    if (disable_npcs || !character_spawn_rate) {
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
    zox_sys_in(ChunkNeighbors)
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
        zox_sys_i(ChunkNeighbors, chunkNeighbors)
        zox_sys_o(CharactersSpawned, charactersSpawned)
        zox_sys_o(CharactersEverSpawned, charactersEverSpawned)
        zox_sys_o(EntityLinks, entityLinks)

        const byte is_in_spawn_range = renderDistance->value <= terrain_lod_near;
        const byte is_first_spawn = is_in_spawn_range && !charactersEverSpawned->value;

        // if already spawned, skip spawning, only update LODs
        // if basically all air, no need to spawn
        if (!has_children_VoxelNode(voxelNode) && !voxelNode->value) {
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

        // getters
        ecs_entity_t terrain = voxLink->value;
        zox_geter_value(terrain, RealmLink, ecs_entity_t, realm)
        zox_geter(realm, CharacterLinks, characters)
        zox_geter_value(realm, CharactersChanceMax, byte, max_chance)
        const ecs_entity_t chunk_above = chunkNeighbors->value[direction_up];
        const VoxelNode* voxel_node_above = zox_valid(chunk_above) ? zox_gett(chunk_above, VoxelNode) : NULL;

        // calcs
        const byte depth = nodeDepth->value;
        const int chunk_length = powers_of_two[depth];
        const byte lod = distance_to_lod_npc(renderDistance->value);
        const int3 chunk_dimensions = int3_single(chunk_length);
        int3 chunk_voxel_position = get_chunk_voxel_position(chunkPosition->value, chunk_dimensions);
        byte found_position = 0;
        float3 position;


        for (byte j = 0; j < character_spawn_rate; j++) {

            // 1) Find a npc to place
            // find random from realm characters
            byte chance_current = 0;
            byte chance_rolled = rand() % max_chance;
            ecs_entity_t meta = 0;
            for (byte k = 0; k < characters->length; k++) {
                ecs_entity_t e2 = characters->value[k];
                zox_geter_value(e2, SpawnChance, byte, chance)
                chance_current += chance;
                if (chance_rolled <= chance_current) {
                    meta = e2;
                    break;
                }
            }
            if (!meta) {
                zox_log_error("failed to find a spawn character_meta")
                continue;
            }
            zox_geter_value2(meta, ModelLink, ecs_entity_t, model)
            zox_geter_value(meta, Character3PrefabLink, ecs_entity_t, prefab_character)
            if (!model || !prefab_character) {
                zox_log_error("failed to find a spawn character_meta")
                continue;
            }
            // if model group
            if (zox_has(model, ModelLinks)) {
                zox_geter(model, ModelLinks, models)
                if (models->length) {
                    model = models->value[rand() % models->length];
                }
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
                    local_position = find_random_position_on_ground(
                        voxelNode,
                        voxel_node_above,
                        depth);
                    if (!byte3_equals(byte3_full, local_position)) {
                        break;
                    }/* else {
                        zox_log_error("pos out of bounds [%ix%ix%i]", local_position.x, local_position.y, local_position.z)
                    }*/
                }
                if (byte3_equals(byte3_full, local_position)) {
                    zox_log_spawning("! failed to spawn npc")
                    continue;
                }
                position = local_to_real_position_character(local_position, chunk_voxel_position, bounds, depth, 1);
            }
            float4 rotation = quaternion_from_euler( (float3) { 0, (rand() % 361) * degreesToRadians, 0 });

            // 3) Finally we spawn and link
            // ecs_entity_t prefab_character = is_characters_instanced ? prefab_character3_instanced_npc : prefab_character3_npc;
            spawn_character3D_data spawn_data = {
                .prefab = prefab_character,
                .terrain = voxLink->value,
                .terrain_chunk = e,
                .chunk_position = chunkPosition->value,
                .position = position,
                .rotation = rotation,
                .lod = lod,
                .render_disabled = renderDisabled->value,
                .model = model,
                .scale = vox_model_scale,
            };
            const ecs_entity_t character = spawn_character3(world, spawn_data);
            on_spawned_character3_npc(world, character);
            add_to_EntityLinks(entityLinks, character);

            zox_log_spawning("+ npc: %s at [%fx%fx%f] [%i of %i]",  zox_get_name(character), position.x, position.y, position.z, (j + 1), (character_spawn_rate))
            // zox_log("+ spawned npc at [%ix%ix%i]", chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z)
            zox_stats_characters++;
        }

        if (entityLinks->length >= 1) {
            zox_log_spawning("+ characters spawned [%i] at [%ix%ix%i]", entityLinks->length, chunkPosition->value.x, chunkPosition->value.y, chunkPosition->value.z)
            // zox_log("+ [%lu] spawned [%i]", e, entityLinks->length)
            // zox_log("- spawned characters [%i] out of [%i]", entityLinks->length, zox_stats_characters)
        }

        charactersSpawned->value = 1;
        charactersEverSpawned->value = 1;
    }
} zox_declare_system(Characters3SpawnSystem)