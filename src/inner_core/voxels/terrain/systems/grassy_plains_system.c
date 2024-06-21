// generates our terrain voxels
void GrassyPlainsSystem(ecs_iter_t *it) {
#ifdef zox_disable_terrain_generation
    return;
#endif
    zox_change_check()
    const unsigned char target_depth = max_octree_depth;
    const unsigned char chunk_voxel_length = powers_of_two_byte[target_depth];
    const float2 map_size_f = (float2) { chunk_voxel_length, chunk_voxel_length };
    zox_field_in(ChunkPosition, chunkPositions, 2)
    zox_field_out(GenerateChunk, generateChunks, 3)
    zox_field_out(ChunkDirty, chunkDirtys, 4)
    zox_field_out(ChunkOctree, chunkOctrees, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateChunk, generateChunks, generateChunk)
        if (generateChunk->value != 1) continue;
        zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value) continue;
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        const float3 chunk_position_float3 = float3_from_int3(chunkPosition->value);
        const int chunk_position_y = (int) (chunk_position_float3.y * chunk_voxel_length);
        fill_new_octree(chunkOctree, 0, target_depth);
        const SetVoxelTargetData datam_dirt = { .depth = target_depth, .voxel = zox_block_dirt, .effect_nodes = 1 };
        const SetVoxelTargetData datam_grass = { .depth = target_depth, .voxel = zox_block_grass, .effect_nodes = 1 };
        const SetVoxelTargetData datam_flower = { .depth = target_depth, .voxel = zox_block_vox_grass, .effect_nodes = 1 };
        SetVoxelData data = { .node = chunkOctree };
        byte3 voxel_position;
        for (voxel_position.x = 0; voxel_position.x < chunk_voxel_length; voxel_position.x++) {
            for (voxel_position.z = 0; voxel_position.z < chunk_voxel_length; voxel_position.z++) {
                const double perlin_value = perlin_terrain(
                    noise_positiver2 + chunk_position_float3.x + (voxel_position.x / map_size_f.x),
                    noise_positiver2 + chunk_position_float3.z + (voxel_position.z / map_size_f.y),
                    terrain_frequency, terrain_seed, terrain_octaves);
                const int global_height = int_floor(terrain_boost + -terrain_minus_amplifier + terrain_amplifier * perlin_value);
                const int local_height_raw = global_height - chunk_position_y;
                const int local_height = int_min(chunk_voxel_length - 1, local_height_raw);
                if (local_height >= 0) {
                    for (voxel_position.y = 0; voxel_position.y <= local_height; voxel_position.y++) {
                        data.position = voxel_position;
                        if (voxel_position.y  == local_height_raw) set_voxel(&datam_grass, data);
                        else set_voxel(&datam_dirt, data);
                    }
                }
                if (local_height_raw + 1 >= 0 && local_height_raw + 1 < chunk_voxel_length) {
                    const int rando = rand() % 10000;
                    if (rando <= grass_vox_spawn_chance) {
                        voxel_position.y = local_height_raw + 1;
                        data.position = voxel_position;
                        set_voxel(&datam_flower, data);
                        // zox_log(" + flower spawned %f\n", perlin_value)
                    }
                }
            }
        }
#ifndef zox_disable_closing_octree_nodes
        close_same_nodes(chunkOctree);
#endif
        generateChunk->value = 0;
        chunkDirty->value = 1;
    }
    /*for (int i = 0; i < it->count; i++) {
        zox_field_o(GenerateChunk, generateChunks, generateChunk)
        if (generateChunk->value != 1) continue;
        zox_field_o(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value) continue;
        zox_field_i(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_o(ChunkOctree, chunkOctrees, chunkOctree)
        const float3 chunk_position_float3 = float3_from_int3(chunkPosition->value);
        const int chunk_position_y = (int) (chunk_position_float3.y * chunk_voxel_length);
        fill_new_octree(chunkOctree, 0, target_depth);
        const byte2 set_dirt = (byte2) { zox_block_dirt, target_depth };
        const byte2 set_grass = (byte2) { zox_block_grass, target_depth };
        const byte2 set_sand = (byte2) { zox_block_sand, target_depth };
        const byte2 set_stone = (byte2) { zox_block_stone, target_depth };
        const byte2 set_grass_vox = (byte2) { zox_block_vox_grass, target_depth };
        const byte2 set_vox_dirt = (byte2) { zox_block_dirt_vox, target_depth };
        const byte2 set_dirt_rubble = (byte2) { zox_block_dirt_rubble, target_depth };
        byte3 voxel_position;
        for (voxel_position.x = 0; voxel_position.x < chunk_voxel_length; voxel_position.x++) {
            for (voxel_position.z = 0; voxel_position.z < chunk_voxel_length; voxel_position.z++) {
                int global_height = int_floor(terrain_boost + -terrain_minus_amplifier + terrain_amplifier * perlin_terrain(
                    noise_positiver2 + chunk_position_float3.x + (voxel_position.x / map_size_f.x),
                    noise_positiver2 + chunk_position_float3.z + (voxel_position.z / map_size_f.y),
                    terrain_frequency, terrain_seed, terrain_octaves));
                if (global_height < lowest_voxel_height) global_height = lowest_voxel_height;
                // now for grass_vox on top
                // remember: to add structures like that, a noise roof over ttop of certain areas would be cool
                const unsigned char is_mountain = global_height >= mountain_height;
                const unsigned char is_sand = global_height <= sand_height;
                const unsigned char is_grasslands = !is_sand && !is_mountain;
                int rando = rand() % 10000;
                if (is_grasslands) {
                    if (rando <= stone_top_spawn_chance) {
                        set_terrain_block(world, chunkOctree, voxel_position, chunk_position_y, chunk_voxel_length, set_stone, global_height);
                    } else {
                        rando += stone_top_spawn_chance;
                        if (rando <= grass_vox_spawn_chance) {
                            set_terrain_block(world, chunkOctree, voxel_position, chunk_position_y, chunk_voxel_length, set_grass_vox, global_height);
                        } else {
                            rando += grass_vox_spawn_chance;
                            if (rando <= vox_dirt_spawn_chance) {
                                set_terrain_block(world, chunkOctree, voxel_position, chunk_position_y, chunk_voxel_length, set_vox_dirt, global_height);
                            } else {
                                rando += vox_dirt_spawn_chance;
                                if (rando <= vox_spawn_chance_dirt_rubble) {
                                    set_terrain_block(world, chunkOctree, voxel_position, chunk_position_y, chunk_voxel_length, set_dirt_rubble, global_height);
                                }
                            }
                        }
                    }
                } else if (is_mountain) {
                    if (rando <= stone_top_spawn_chance * 4) {
                        set_terrain_block(world, chunkOctree, voxel_position, chunk_position_y, chunk_voxel_length, set_stone, global_height);
                    } else {
                        rando += stone_top_spawn_chance;
                        if (rando <= vox_dirt_spawn_chance * 4) {
                            set_terrain_block(world, chunkOctree, voxel_position, chunk_position_y, chunk_voxel_length, set_vox_dirt, global_height);
                        } else {
                            rando += vox_dirt_spawn_chance;
                            if (rando <= vox_spawn_chance_dirt_rubble * 4) {
                                set_terrain_block(world, chunkOctree, voxel_position, chunk_position_y, chunk_voxel_length, set_dirt_rubble, global_height);
                            }
                        }
                    }
                }

                int local_height = int_min(chunk_voxel_length, global_height - chunk_position_y); // gets either grass point or chunk_voxel_length
                if (local_height > 0) {
                    const unsigned char chunk_below_max = local_height > chunk_voxel_length;
                    if (chunk_below_max) local_height = chunk_voxel_length;
                    // this moves through y positions of chunk
                    for (voxel_position.y = 0; voxel_position.y < local_height; voxel_position.y++) {
                        byte3 node_position = voxel_position;
                        // if top voxel
                        if (!chunk_below_max && voxel_position.y == local_height - 1) {
                            const int current_position_y = chunk_position_y + voxel_position.y;
                            if (current_position_y < sand_height) {
                                set_octree_voxel(chunkOctree, &node_position, &set_sand, 0);
                            } else if (current_position_y >= mountain_height) {
                                if (rand() % 100 <= 94) set_octree_voxel(chunkOctree, &node_position, &set_stone, 0);
                                else set_octree_voxel(chunkOctree, &node_position, &set_dirt, 0);
                            } else {
                                if (rand() % 100 <= grass_spawn_chance) set_octree_voxel(chunkOctree, &node_position, &set_grass, 0);
                                else set_octree_voxel(chunkOctree, &node_position, &set_dirt, 0);
                            }
                        } else {
                            set_octree_voxel(chunkOctree, &node_position, &set_dirt, 0);
                        }
                    }
                }
            }
        }
#ifndef zox_disable_closing_octree_nodes
        close_same_nodes(chunkOctree);
#endif
        // close_solid_nodes(chunkOctree);
        generateChunk->value = 0;
        chunkDirty->value = 1;
    }*/
} zox_declare_system(GrassyPlainsSystem)


// const byte2 set_stone = (byte2) { 4, target_depth };
// const byte2 set_obsidian = (byte2) { 5, target_depth };
// set_octree_voxel(chunkOctree, &node_position, &set_obsidian, 0);
// set_octree_voxel(chunkOctree, &node_position, &set_dirt, 0);
// if (rand() % 100 > 30)
/*int rando = rand() % 100;
if (rando < grass_spawn_chance) {
    set_octree_voxel(chunkOctree, &node_position, &set_grass, 0);
} else if (rando < grass_spawn_chance + 6) {
    set_octree_voxel(chunkOctree, &node_position, &set_stone, 0);
} else if (rando < grass_spawn_chance + 6 + 6) {
    set_octree_voxel(chunkOctree, &node_position, &set_obsidian, 0);
} else {
    set_octree_voxel(chunkOctree, &node_position, &set_dirt, 0);
}*/
