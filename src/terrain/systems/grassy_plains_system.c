byte optimize_generation_lods = 0;

// generates our terrain voxels
void GrassyPlainsSystem(ecs_iter_t *it) {
    uint update_count = 0;
    // for now while types are global
    const byte target_depth = terrain_depth;
    const uint seed = global_seed;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ChunkPosition)
    zox_sys_in(RenderLod)
    zox_sys_out(GenerateChunk)
    zox_sys_out(VoxelNode)
    zox_sys_out(NodeDepth)
    zox_sys_out(VoxelNodeDirty)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(ChunkPosition, chunkPosition)
        zox_sys_o(GenerateChunk, generateChunk)
        zox_sys_o(NodeDepth, nodeDepth)
        zox_sys_o(VoxelNode, voxelNode)
        zox_sys_o(VoxelNodeDirty, voxelNodeDirty)
        // todo: remember if has generated yet, keep a generated LOD state!
        //      - better yet just increase NodeDepth - and compare with terrain's one when increasing
        if (generateChunk->value != chunk_generate_state_update || is_opened_VoxelNode(voxelNode)) {
            continue;
        }
        byte node_depth = optimize_generation_lods ?  get_chunk_terrain_depth_from_lod(renderLod->value, target_depth) : target_depth;
        // zox_log("> [optimize_generation_lods:%i] - render_depth: %i", optimize_generation_lods,  render_depth)
        if (!node_depth) {
            continue;
        }
        nodeDepth->value = node_depth;
        const byte chunk_voxel_length = powers_of_two_byte[node_depth];
        const float2 map_size_f = (float2) { chunk_voxel_length, chunk_voxel_length };
        const SetVoxelTargetData datam_dirt = {
            .depth = node_depth,
            .voxel = zox_block_dirt,
            .effect_nodes = 1
        };
        const SetVoxelTargetData datam_stone = {
            .depth = node_depth,
            .voxel = zox_block_stone,
            .effect_nodes = 1
        };
        const SetVoxelTargetData datam_dirt_grass = {
            .depth = node_depth,
            .voxel = zox_block_grass,
            .effect_nodes = 1
        };
        const SetVoxelTargetData datam_sand = {
            .depth = node_depth,
            .voxel = zox_block_sand,
            .effect_nodes = 1
        };
        const SetVoxelTargetData setter_obsidian = {
            .depth = node_depth,
            .voxel = zox_block_obsidian,
            .effect_nodes = 1
        };
        const SetVoxelTargetData datam_grass = {
            .depth = node_depth,
            .voxel = zox_block_vox_grass,
            .effect_nodes = 1
        };
        const SetVoxelTargetData datam_flower = {
            .depth = node_depth,
            .voxel = zox_block_vox_flower,
            .effect_nodes = 1
        };
        const SetVoxelTargetData datam_rubble = {
            .depth = node_depth,
            .voxel = zox_block_dirt_rubble,
            .effect_nodes = 1
        };
        fill_new_octree(voxelNode, 0, node_depth);

        const float3 chunk_position_float3 = float3_from_int3(chunkPosition->value);
        const int chunk_position_y = (int) (chunk_position_float3.y * chunk_voxel_length);
        SetVoxelData data = {
            .node = voxelNode
        };
        byte3 voxel_position;
        for (voxel_position.x = 0; voxel_position.x < chunk_voxel_length; voxel_position.x++) {
            for (voxel_position.z = 0; voxel_position.z < chunk_voxel_length; voxel_position.z++) {
                const float nposition_x = noise_positiver2 + chunk_position_float3.x + (voxel_position.x / map_size_f.x);
                const float nposition_z = noise_positiver2 + chunk_position_float3.z + (voxel_position.z / map_size_f.y);

                const double mountain_amplifier = 2;
                const double mountain_noise = (perlin_terrain(
                    nposition_x,
                    nposition_z,
                    0.002,
                    seed,
                    3) + 1.0) / 2.0;
                const byte is_mountain = mountain_noise >= 0.6; // biome == zox_biome_mountain

                const double height_frequency = is_mountain ? terrain_frequency * mountain_amplifier : terrain_frequency;
                const double height_amplifier = is_mountain ? terrain_amplifier * mountain_amplifier : terrain_amplifier;
                const double perlin_value = height_amplifier * perlin_terrain(
                    nposition_x,
                    nposition_z,
                    height_frequency,
                    seed,
                    terrain_octaves);
                const int global_position_y = int_floorf(terrain_boost + -terrain_minus_amplifier + perlin_value);
                const int local_height_raw = global_position_y - chunk_position_y;
                const int local_height = int_min(chunk_voxel_length - 1, local_height_raw);
                byte did_place_grass_top = 0;
                if (local_height >= 0) {
                    for (voxel_position.y = 0; voxel_position.y <= local_height; voxel_position.y++) {
                        data.position = voxel_position;
                        // top blocks
                        if (voxel_position.y  == local_height_raw) {
                            if (is_mountain) {
                                set_voxel(&datam_stone, data);
                            } else {
                                if (global_position_y < sand_height) {
                                    set_voxel(&datam_sand, data);
                                } else if (global_position_y == sand_height) {
                                    set_voxel(&datam_dirt, data);
                                } else {
                                    const double place_value = (perlin_terrain(
                                        nposition_x,
                                        nposition_z,
                                        0.16,
                                        seed * 2,
                                        4) + 1.0) / 2.0;
                                    if (place_value <= 0.73) {
                                        set_voxel(&datam_dirt_grass, data);
                                        did_place_grass_top = 1;
                                    } else {
                                        set_voxel(&datam_dirt, data);   // reverse add dirt patches
                                    }
                                }
                            }
                        } else {
                            set_voxel(&datam_stone, data);
                        }
                    }
                }
                if (!disable_block_vox_generation &&
                    !is_mountain &&
                    did_place_grass_top &&
                    local_height_raw + 1 >= 0 &&
                    local_height_raw + 1 < chunk_voxel_length &&
                    global_position_y > sand_height) {
                    /*const double place_value = (perlin_terrain(
                        noise_position_x,
                        noise_position_z,
                        0.216,
                        seed * 16,
                        4) + 1.0) / 2.0;
                    const double place_value2 = (perlin_terrain(
                        noise_position_x,
                        noise_position_z,
                        0.616,
                        seed * 16,
                        6) + 1.0) / 2.0;*/
                    const byte place_grass = should_place_grass(nposition_x, nposition_z, seed); //  * 16
                    if (place_grass) {
                        voxel_position.y = local_height_raw + 1;
                        data.position = voxel_position;
                        set_voxel(&datam_grass, data);
                    }

                    // place_value + place_value2 * 0.1 <= 0.33) {

                    /*const int rando = rand() % 10000;
                    if (rando <= block_spawn_chance_grass + block_spawn_chance_flower + block_spawn_chance_rubble) {
                        voxel_position.y = local_height_raw + 1;
                        data.position = voxel_position;
                        if (rando <= block_spawn_chance_grass) {
                            set_voxel(&datam_grass, data);
                        }
                        else if (rando <= block_spawn_chance_grass + block_spawn_chance_flower) {
                            set_voxel(&datam_flower, data);
                        }
                        else if (rando <= block_spawn_chance_grass + block_spawn_chance_flower + block_spawn_chance_rubble) {
                            set_voxel(&datam_rubble, data);
                        }
                        // zox_log(" + flower spawned %f\n", perlin_value)
                    }*/
                }
                // obisidian bottom
                if (chunkPosition->value.y == -render_distance_y) {
                    voxel_position.y = 0;
                    const int obsidian_height = rand() % terrain_obsidian_height;
                    for (voxel_position.y = 0; voxel_position.y <= obsidian_height; voxel_position.y++) {
                        data.position = voxel_position;
                        data.position = voxel_position;
                        set_voxel(&setter_obsidian, data);
                    }
                }
            }
        }
        cleanup_nodes(world, voxelNode);
        update_count++;
        voxelNodeDirty->value = zox_dirty_trigger;
    }
    if (update_count > 0 && zox_log_terrain_generation) {
        zox_log(" - [%i] terrain [%i]", ecs_run_count, update_count)
    }
} zox_declare_system(GrassyPlainsSystem)