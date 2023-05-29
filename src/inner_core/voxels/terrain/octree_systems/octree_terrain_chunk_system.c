#define grass_spawn_chance 80
#define octree_random_spawn_chance 90
const int sand_height = -7;
// todo: rewrite algorithm, it's too slow atm for xyz chunks

void generate_terrain(ChunkOctree* chunk_octree, unsigned char depth, float3 position, float scale) {
    double octree_noise = perlin_terrain(position.x + noise_positiver2, position.z + noise_positiver2, terrain_frequency, terrain_seed, terrain_octaves);
    if (octree_noise < octree_min_height) {
        octree_noise = octree_min_height;
    }
    // octree_noise += octree_height_addition * octree_perlin_noise(position.x, position.y, position.z,
    //    octree_persistence, octree_frequency);
    if (position.y <= octree_noise) {
        chunk_octree->value = 1;
    } else {
        chunk_octree->value = 0;
    }
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
                if (chunk_octree->nodes[i].nodes != NULL || chunk_octree->nodes[i].value == 0) {
                    is_all_solid = 0;
                    break;
                }
            }
            if (is_all_solid) {
                close_ChunkOctree(chunk_octree);
            }
        #endif
    }
}

void OctreeTerrainChunkSystem(ecs_iter_t *it) {
    if (!ecs_query_changed(it->ctx, NULL)) return;
    #ifdef zoxel_time_octree_terrain_chunk_system
        begin_timing()
    #endif
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 2);
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 3);
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 4);
    ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 5);
    unsigned char target_depth = max_octree_depth; //  - 1;
    unsigned char chunk_voxel_length = powers_of_two_byte[target_depth];
    float2 map_size_f = (float2) { chunk_voxel_length, chunk_voxel_length };
    for (int i = 0; i < it->count; i++) {
        const GenerateChunk *generateChunk = &generateChunks[i];
        if (generateChunk->value == 0) continue;
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 0) continue;
        chunkDirty->value = 1;
        ChunkOctree *chunkOctree = &chunkOctrees[i];
        const ChunkPosition *chunkPosition = &chunkPositions[i];
        float3 chunk_position_float3 = float3_from_int3(chunkPosition->value);
        fill_octree(chunkOctree, 0, target_depth);
        const byte2 set_dirt = (byte2) { 1, target_depth };
        const byte2 set_grass = (byte2) { 2, target_depth };
        const byte2 set_sand = (byte2) { 3, target_depth };
        const byte2 set_stone = (byte2) { 4, target_depth };
        const byte2 set_obsidian = (byte2) { 5, target_depth };
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
                int global_position_y = (int) (chunk_position_float3.y * chunk_voxel_length);
                int local_height = (int) (global_height - global_position_y);
                if (local_height > 0) {
                    unsigned char chunk_below_max = local_height > chunk_voxel_length;
                    if (chunk_below_max) {
                        local_height = chunk_voxel_length;
                    }
                    for (voxel_position.y = 0; voxel_position.y < local_height; voxel_position.y++) {
                        byte3 node_position = voxel_position;
                        // if top voxel
                        if (!chunk_below_max && voxel_position.y == local_height - 1) {
                            if (global_position_y + voxel_position.y < sand_height) {
                                // zoxel_log(" > sand voxel created\n");
                                set_octree_voxel(chunkOctree, &node_position, &set_sand, 0);
                            } else {
                                int rando = rand() % 100;
                                if (rando < grass_spawn_chance) {
                                    set_octree_voxel(chunkOctree, &node_position, &set_grass, 0);
                                } else if (rando < grass_spawn_chance + 6) {
                                    set_octree_voxel(chunkOctree, &node_position, &set_stone, 0);
                                } else if (rando < grass_spawn_chance + 6 + 6) {
                                    set_octree_voxel(chunkOctree, &node_position, &set_obsidian, 0);
                                } else {
                                    set_octree_voxel(chunkOctree, &node_position, &set_dirt, 0);
                                }
                            }
                        } else {
                            set_octree_voxel(chunkOctree, &node_position, &set_dirt, 0);
                        }
                    }
                }
            }
        }
        // now close all solid ground nodes
        #ifdef voxels_close_octree_nodes
            close_solid_nodes(chunkOctree);
        #endif
        #ifdef zoxel_time_octree_terrain_chunk_system
            did_do_timing()
        #endif
    }
    #ifdef zoxel_time_octree_terrain_chunk_system
        end_timing("    - octree_terrain_chunk_system")
    #endif
}
zox_declare_system(OctreeTerrainChunkSystem)

// fill_octree(chunkOctree, 1, target_depth);
// generate_height_map(height_map, chunk_position_float3, map_size);
// randomize_inner_nodes(chunkOctree, 0);
// fill_octree(chunkOctree, 1, max_octree_depth - 1);
// generate_terrain(chunkOctree, 0, chunk_position_float3, 1.0f);
// try with a big pool
// generate_terrain_height_map(chunkOctree, 0, chunk_position_float3, int3_zero, height_map, map_size);

/*typedef struct {
    int allocated;
    int used;
    ChunkOctree *pool;
} ChunkOctreePool;*/
    /*else
    {
        if (rand() % 10001 >= 9999)
        {
            if (voxel == 0)
            {
                node->value = 1;
            }
            else
            {
                node->value = 0;
            }
        }
    }*/
/*void generate_height_map(double* height_map, float3 position, int2 map_size) {
    int2 map_position;
    for (map_position.x = 0; map_position.x < map_size.x; map_position.x++) {
        for (map_position.y = 0; map_position.y < map_size.y; map_position.y++) {
            #ifdef voxels_flat_land
                height_map[int2_array_index(map_position, map_size)] = 0.5;
            #else
                height_map[int2_array_index(map_position, map_size)] = perlin_terrain(
                    position.x + noise_positiver2 + (map_position.x / ((float) map_size.x)), 
                    position.z + noise_positiver2 + (map_position.y / ((float) map_size.y)),
                    terrain_frequency,
                    terrain_seed, terrain_octaves);
            #endif
        }
    }
}*/

//! Our function that creates a chunk.
/*void randomize_inner_nodes(ChunkOctree* chunk_octree, unsigned char depth) {
    chunk_octree->value = rand() % 2;
    // chance to dig deeper
    if (depth < max_octree_depth && chunk_octree->value && rand() % 100 <= octree_random_spawn_chance - depth * 12) {
        depth++;
        open_ChunkOctree(chunk_octree);
        for (int i = 0; i < octree_length; i++) {
            randomize_inner_nodes(&chunk_octree->nodes[i], depth);
        }
    }
}*/
    // octree_noise += octree_height_addition * octree_perlin_noise(position.x, position.y, position.z,
    //    octree_persistence, octree_frequency);

/*void generate_terrain_height_map(ChunkOctree* chunk_octree, unsigned char depth,
    float3 position, int3 local_position, double* height_map, int2 map_size) {
    int depth_left = max_octree_depth - depth;
    int division_left = powers_of_two[depth_left]; //  pow(2, depth_left);
    int2 map_position = (int2) { local_position.x * division_left, local_position.z * division_left };
    int height_map_index = int2_array_index(map_position, map_size);
    // int height_map_index = 0;
    double octree_noise = height_map[height_map_index];
    if (octree_noise < octree_min_height) {
        octree_noise = octree_min_height;
    }
    if (position.y <= octree_noise) {
        chunk_octree->value = 1;
        if (depth < max_octree_depth) {
            depth++;
            for (unsigned char i = 0; i < octree_length; i++) {
                float3 node_position = float3_add(position, float3_multiply_float(octree_positions_float3s[i], octree_scales[depth]));
                int3 node_local_position = int3_add(octree_positions[i], int3_multiply_int(local_position, 2));
                generate_terrain_height_map(&chunk_octree->nodes[i], depth, node_position, node_local_position, height_map, map_size);
            }
            // check all children
            #ifndef zoxel_disable_close_nodes
                unsigned char is_all_solid = 1;
                for (unsigned char i = 0; i < octree_length; i++) {
                    if (chunk_octree->nodes[i].nodes != NULL || chunk_octree->nodes[i].value == 0) {
                        is_all_solid = 0;
                        break;
                    }
                }
                if (is_all_solid) {
                    close_ChunkOctree(chunk_octree);
                }
            #endif
        }
    } else {
        chunk_octree->value = 0;
    }
}*/