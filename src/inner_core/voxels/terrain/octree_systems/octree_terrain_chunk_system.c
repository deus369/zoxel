void generate_terrain(ChunkOctree* chunk_octree, unsigned char depth, float3 position, float scale) {
    double octree_noise = perlin_terrain(position.x + noise_positiver2, position.z + noise_positiver2, terrain_frequency, terrain_seed, terrain_octaves);
    if (octree_noise < octree_min_height) octree_noise = octree_min_height;
    // octree_noise += octree_height_addition * octree_perlin_noise(position.x, position.y, position.z, octree_persistence, octree_frequency);
    if (position.y <= octree_noise) chunk_octree->value = 1;
    else chunk_octree->value = 0;
    if (depth < max_octree_depth && chunk_octree->value) {
        depth++;
        scale = scale * 0.5f;
        open_ChunkOctree(chunk_octree);
        for (unsigned char i = 0; i < octree_length; i++) {
            float3 node_position = float3_add(position, float3_multiply_float(float3_from_int3(octree_positions[i]), scale));
            generate_terrain(&chunk_octree->nodes[i], depth, node_position, scale);
        }
        // check all children
#ifndef zoxel_disable_close_nodes
        unsigned char is_all_solid = 1;
        for (unsigned char i = 0; i < octree_length; i++) {
            if (chunk_octree->nodes[i].nodes != NULL || !chunk_octree->nodes[i].value) {
                is_all_solid = 0;
                break;
            }
        }
        if (is_all_solid) close_ChunkOctree(chunk_octree);
#endif
    }
}

void set_terrain_block(ecs_world_t *world, ChunkOctree *chunkOctree, const byte3 voxel_position, const int chunk_position_y, const unsigned char chunk_voxel_length, const byte2 set_voxel, const int global_place_y) {
    const int local_place_y = global_place_y - chunk_position_y;
    const unsigned char place_in_bounds = local_place_y >= 0 && local_place_y < chunk_voxel_length;
    if (place_in_bounds) {
        byte3 node_position = voxel_position;
        node_position.y = local_place_y;
        set_octree_voxel(chunkOctree, &node_position, &set_voxel, 0); // testing
    }
}

// generates our terrain voxels
void OctreeTerrainChunkSystem(ecs_iter_t *it) {
    zox_change_check()
#ifdef zoxel_time_octree_terrain_chunk_system
    begin_timing()
#endif
    const unsigned char target_depth = max_octree_depth;
    const unsigned char chunk_voxel_length = powers_of_two_byte[target_depth];
    const float2 map_size_f = (float2) { chunk_voxel_length, chunk_voxel_length };
    zox_field_in(ChunkPosition, chunkPositions, 2)
    zox_field_out(GenerateChunk, generateChunks, 3)
    zox_field_out(ChunkDirty, chunkDirtys, 4)
    zox_field_out(ChunkOctree, chunkOctrees, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(GenerateChunk, generateChunks, generateChunk)
        if (generateChunk->value != 1) continue;
        zox_field_i_out(ChunkDirty, chunkDirtys, chunkDirty)
        if (chunkDirty->value) continue;
        zox_field_i_in(ChunkPosition, chunkPositions, chunkPosition)
        zox_field_i_out(ChunkOctree, chunkOctrees, chunkOctree)
        const float3 chunk_position_float3 = float3_from_int3(chunkPosition->value);
        const int chunk_position_y = (int) (chunk_position_float3.y * chunk_voxel_length);
        fill_new_octree(chunkOctree, 0, target_depth);
        const byte2 set_dirt = (byte2) { zox_block_dirt, target_depth };
        const byte2 set_grass = (byte2) { zox_block_grass, target_depth };
        const byte2 set_sand = (byte2) { zox_block_sand, target_depth };
        const byte2 set_stone = (byte2) { zox_block_stone, target_depth };
        const byte2 set_grass_vox = (byte2) { zox_block_grass_vox, target_depth };
        byte3 voxel_position;
        for (voxel_position.x = 0; voxel_position.x < chunk_voxel_length; voxel_position.x++) {
            for (voxel_position.z = 0; voxel_position.z < chunk_voxel_length; voxel_position.z++) {
#ifdef zoxel_is_flat_height
                int global_height = int_floor(terrain_amplifier * flat_height_level);
#else
                int global_height = int_floor(terrain_boost + -terrain_minus_amplifier + terrain_amplifier * perlin_terrain(
                    noise_positiver2 + chunk_position_float3.x + (voxel_position.x / map_size_f.x),
                    noise_positiver2 + chunk_position_float3.z + (voxel_position.z / map_size_f.y),
                    terrain_frequency, terrain_seed, terrain_octaves));
                if (global_height < lowest_voxel_height) global_height = lowest_voxel_height;
#endif
                // now for grass_vox on top
                // remember: to add structures like that, a noise roof over ttop of certain areas would be cool
                if (rand() % 10000 <= stone_top_spawn_chance) {
                    set_terrain_block(world, chunkOctree, voxel_position, chunk_position_y, chunk_voxel_length, set_stone, global_height);
                } else if (rand() % 10000 <= grass_vox_spawn_chance) {
                    set_terrain_block(world, chunkOctree, voxel_position, chunk_position_y, chunk_voxel_length, set_grass_vox, global_height);
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
#ifdef zoxel_time_octree_terrain_chunk_system
        did_do_timing()
#endif
        generateChunk->value = 0;
        chunkDirty->value = 1;
        /*if (zox_has(e, GenerateChunkEntities)) {
            zox_set(e, GenerateChunkEntities, { zox_chunk_entities_state_triggered })
        }*/
    }
#ifdef zoxel_time_octree_terrain_chunk_system
    end_timing("    - octree_terrain_chunk_system")
#endif
} zox_declare_system(OctreeTerrainChunkSystem)


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

// testing
/*fill_new_octree(chunkOctree, 1, target_depth); // 1
generateChunk->value = 0;
chunkDirty->value = 1;
return;*/
