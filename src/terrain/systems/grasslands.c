define_fun_stopwatch(time_grassy_plains, 0);

// FIXME(deus): This LOD+1 patch prevents chunk seems.
byte boost_generation_hack = 0; // 🔥 applied until truth is revealed

byte disable_biomes = 1;
byte disable_top_placements = 0;
byte disable_dirt_patches = 1;
byte disable_grass_placements = 0;

// place grass if max depth

// t for terrain
VoxelNode* set_voxelt(
    VoxelNode* node,
    byte target_depth,
    byte3 position,
    byte value,
    byte depth
) {
    byte depth_reached = depth == target_depth;
    if (!depth_reached && is_closed_VoxelNode(node)) {
        open_VoxelNode(node);
        VoxelNode* kids = get_children_VoxelNode(node);
        for (byte i = 0; i < octree_length; i++) {
            kids[i].value = 0; // node->value;
        }
    }
    // wait this overrides child nodes, rather than reevaluating them
    if (depth_reached || value) {
        node->value = value;
    }
    if (depth_reached || !has_children_VoxelNode(node)) {
        return node;
    }
    VoxelNode* kids = get_children_VoxelNode(node);

    const byte dividor = powers_of_two_byte[target_depth - depth - 1];
    //const byte3 node_position = position;
    //byte3_modulus_byte(&node_position, dividor);
    byte3 node_position = (byte3) {
        position.x / dividor,
        position.y / dividor,
        position.z / dividor
    };
    byte3_modulus_byte(&position, dividor);
    byte node_index = byte3_octree_array_index(node_position);

    node = &kids[node_index];
    depth++;

    return set_voxelt(
        node,
        target_depth,
        position,
        value,
        depth);
}

// generates our terrain voxels
void GrassyPlainsSystem(ecs_iter_t *it) {
    zox_ts_begin(grassy_plains);
    // for now while types are global
    // const byte target_depth = terrain_depth;
    const uint seed = global_seed;  // todo: use terrains seed
    // zox_sys_world()
    // zox_log_terrain_generation = 1;
    // uint update_count = 0;
    // int stage_id = get_thread_index();
    // double time_start = get_time_ms();
    zox_sys_begin();
    zox_sys_in(ChunkPosition);
    zox_sys_in(RenderLod);
    zox_sys_in(RenderDistanceDirty);
    zox_sys_in(VoxelNodeLoaded);
    zox_sys_out(VoxelNode);
    zox_sys_out(NodeDepth);
    zox_sys_out(VoxelNodeDirty);
    byte any_dirty = 0;
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDistanceDirty, renderDistanceDirty)
        if (renderDistanceDirty->value == zox_dirty_active) {
            any_dirty = 1;
            break;
        }
    }
    if (!any_dirty) {
        zox_ts_end(grassy_plains, 5, zox_profile_system_grassy_plains);
        return;
    }

    startwatch(time_grassy_plains);


    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderLod, renderLod);
        zox_sys_i(ChunkPosition, chunkPosition);
        zox_sys_i(RenderDistanceDirty, renderDistanceDirty);
        zox_sys_i(VoxelNodeLoaded, loaded);
        zox_sys_o(NodeDepth, nodeDepth);
        zox_sys_o(VoxelNode, voxelNode);
        zox_sys_o(VoxelNodeDirty, voxelNodeDirty);
        // todo: remember if has generated yet, keep a generated LOD state!
        //      - better yet just increase NodeDepth - and compare with terrain's one when increasing
        if (loaded->value) zox_log_error("LOADED ALREADY??");
        if (renderDistanceDirty->value != zox_dirty_active || loaded->value) {
            continue;
        }

        byte depth = optimize_generation_lods ?  terrain_lod_to_node_depth(renderLod->value, terrain_depth) : terrain_depth;
        if (boost_generation_hack && depth < terrain_depth) {
            depth++;
        }
        // zox_log("render lod [%i] building to depth [%i]", renderLod->value, depth);

        // if already at that level
        if (nodeDepth->value >= depth) {
            continue;
        }
        nodeDepth->value = depth;
        byte is_max_depth = nodeDepth->value == terrain_depth;
        // if no depth, skip
        if (!nodeDepth->value) {
            continue;
        }
        const double terrain_amplifier = powers_of_two[nodeDepth->value] * render_distance_y;

        const byte chunk_voxel_length = powers_of_two_byte[nodeDepth->value];
        const float2 map_size_f = (float2) { chunk_voxel_length, chunk_voxel_length };
        const float3 chunk_position_float3 = float3_from_int3(chunkPosition->value);
        const int chunk_position_y = (int) (chunk_position_float3.y * chunk_voxel_length);
        byte3 voxel_position;
        // For each XZ position
        for (voxel_position.x = 0; voxel_position.x < chunk_voxel_length; voxel_position.x++) {
            for (voxel_position.z = 0; voxel_position.z < chunk_voxel_length; voxel_position.z++) {

                const float2 positionn = (float2) {
                    noise_positiver2 + chunk_position_float3.x + (voxel_position.x / map_size_f.x),
                    noise_positiver2 + chunk_position_float3.z + (voxel_position.z / map_size_f.y)
                };

                const double mountain_amplifier = 2;
                byte is_mountain = 0;
                if (!disable_biomes) {
                    const double mountain_noise = (perlin_terrain(
                        positionn.x,
                        positionn.y,
                        0.002,
                        seed,
                        3) + 1.0) / 2.0;
                        is_mountain = mountain_noise >= 0.6; // biome == zox_biome_mountain
                }

                // our height calc
                const double height_frequency = is_mountain ? terrain_frequency * mountain_amplifier : terrain_frequency;
                const double height_amplifier = is_mountain ? terrain_amplifier * mountain_amplifier : terrain_amplifier;
                double perlin_value = perlin_terrain(
                    positionn.x,
                    positionn.y,
                    height_frequency,
                    seed,
                    terrain_octaves);
                perlin_value *= height_amplifier;

                const int global_position_y = int_floorf(terrain_boost + -terrain_minus_amplifier + perlin_value);
                const int local_height_raw = global_position_y - chunk_position_y;
                const int local_height = int_min(chunk_voxel_length - 1, local_height_raw);

                byte did_place_grass_top = 0;
                // For each Y position
                if (local_height >= 0) {
                    for (voxel_position.y = 0; voxel_position.y <= local_height; voxel_position.y++) {
                        // top blocks
                        byte value;
                        if (chunkPosition->value.y == -render_distance_y && voxel_position.y == 0) {
                            value = zox_block_obsidian;
                        } else if (!disable_top_placements && voxel_position.y  == local_height_raw) {
                            if (is_mountain) {
                                value = zox_block_stone;
                            } else {
                                if (global_position_y < sand_height) {
                                    value = zox_block_sand;
                                } else if (global_position_y == sand_height) {
                                    value = zox_block_dirt;
                                } else {
                                    if (!disable_dirt_patches) {
                                        value = zox_block_grass;
                                        did_place_grass_top = 1;
                                    } else {
                                        const double place_value = (perlin_terrain(
                                            positionn.x,
                                            positionn.y,
                                            0.16,
                                            seed * 2,
                                            4) + 1.0) / 2.0;
                                        if (place_value <= 0.73) {
                                            value = zox_block_grass;
                                            did_place_grass_top = 1;
                                        } else {
                                            value = zox_block_dirt;
                                        }
                                    }
                                }
                            }
                        } else {
                            value = zox_block_stone;
                        }
                        set_voxelt(
                            voxelNode,
                            nodeDepth->value,
                            voxel_position,
                            value,
                            0);
                    }
                }
                if (!disable_grass_placements &&
                    !disable_block_vox_generation &&
                    !is_mountain &&
                    is_max_depth && // if max depth
                    did_place_grass_top &&
                    local_height_raw + 1 >= 0 &&
                    local_height_raw + 1 < chunk_voxel_length &&
                    global_position_y > sand_height
                ) {
                    const byte place_grass = should_place_grass(
                        positionn.x,
                        positionn.y,
                        seed);
                    if (place_grass) {
                        voxel_position.y = local_height_raw + 1;
                        set_voxelt(
                            voxelNode,
                            nodeDepth->value,
                            voxel_position,
                            zox_block_vox_grass,
                            0);
                    }
                }
            }
        }
        tapwatch(time_grassy_plains, "mass set_voxels");

        voxelNodeDirty->value = zox_dirty_trigger;
        /*chunkMeshDirty->value = chunk_dirty_state_trigger;
        for (byte axis = 0; axis < chunk_neighbors_length; axis++) {
            ecs_entity_t neighbor = neighbors->value[axis];
            if (zox_valid(neighbor)) {
                zox_set(neighbor, ChunkMeshDirty, { chunk_dirty_state_trigger })
            }
        }*/
    }
    endwatch(time_grassy_plains, "grassy_plains");
    zox_ts_end(grassy_plains, 5, zox_profile_system_grassy_plains);
} zox_declare_system(GrassyPlainsSystem)



/*const double place_value = (perlin_terrain(
    n oise_position_x, *
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

// obisidian bottom
/*if (chunkPosition->value.y == -render_distance_y) {
    voxel_position.y = 0;
    const int obsidian_height = rand() % terrain_obsidian_height;
    for (voxel_position.y = 0; voxel_position.y <= obsidian_height; voxel_position.y++) {
        // set_voxel(setter_obsidian, data);
        set_voxelt(
            voxelNode,
            node_depth,
            voxel_position,
            zox_block_obsidian,
            0);
    }
}*/