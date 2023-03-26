#define octree_random_spawn_chance 90

// todo: remove pool that didnt work out
// todo: rewrite algorithm, it's too slow atm for xyz chunks

typedef struct {
    int allocated;
    int used;
    ChunkOctree *pool;
} ChunkOctreePool;

//! Closes all solid nodes, as well as air nodes, after terrain system generates it.
void close_solid_nodes(ChunkOctree *node) {
    // for all children nodes
    //  only check higher nodes if closed children
    if (node->nodes != NULL) {
        for (unsigned char i = 0; i < octree_length; i++) {
            close_solid_nodes(&node->nodes[i]);
        }
    }
    if (node->nodes != NULL) {
        unsigned char all_solid = 1;
        for (unsigned char i = 0; i < octree_length; i++) {
            if (node->nodes[i].nodes != NULL || node->nodes[i].value == 0) {
                all_solid = 0;
                break;
            }
        }
        if (all_solid) {
            close_ChunkOctree(node);
        } else {
            unsigned char all_air = 1;
            for (unsigned char i = 0; i < octree_length; i++) {
                if (node->nodes[i].nodes != NULL || node->nodes[i].value != 0) {
                    all_air = 0;
                    break;
                }
            }
            if (all_air) {
                close_ChunkOctree(node);
            }
        }
    }
}

unsigned char set_octree_voxel(unsigned char voxel, unsigned char target_depth, ChunkOctree *node, int3 position, unsigned char depth) {
    // printf("    checking [%i]: %ix%ix%i\n", depth, position.x, position.y, position.z);
    if (depth == target_depth) {
        //printf("    - set voxel [%i] at depth [%i] [%ix%ix%i]\n", voxel, depth, position.x, position.y, position.z);
        node->value = voxel;
        return 0;
    }
    node->value = voxel;
    if (node->nodes == NULL) {
        // printf("node closed at [%i]: %ix%ix%i\n", depth, position.x, position.y, position.z);
        node->value = voxel;
        return 0;
    }
    unsigned char dividor = powers_of_two_byte[target_depth - depth - 1];   // starts at 16, ends at 1
    int3 node_position = (int3) { position.x / dividor, position.y / dividor, position.z / dividor };
    for (unsigned char i = 0; i < octree_length; i++) {
        int3 local_position = octree_positions[i];
        if (int3_equal(node_position, local_position)) {
            /*printf("        - child node: index [%i] depth [%i] dividor [%i] - position [%ix%ix%i] - node_position [%ix%ix%i]\n",
                i, depth, dividor,
                position.x, position.y, position.z,
                node_position.x, node_position.y, node_position.z);*/
            int3 new_position = (int3) { position.x % dividor, position.y % dividor, position.z % dividor };
            if (set_octree_voxel(voxel, target_depth, &node->nodes[i], new_position, depth + 1) == 0) {
                return 0;
            }
            break;
        }
    }
    /*printf("Failed to set position [%ix%ix%i] - node_position [%ix%ix%i] - depth %i:%i - %i\n",
        position.x, position.y, position.z,
        node_position.x, node_position.y, node_position.z,
        depth, target_depth, dividor);*/
    return 1;
}

//! Our function that creates a chunk.
void randomize_inner_nodes(ChunkOctree* chunk_octree, unsigned char depth) {
    chunk_octree->value = rand() % 2;
    // chance to dig deeper
    if (depth < max_octree_depth && chunk_octree->value && rand() % 100 <= octree_random_spawn_chance - depth * 12) {
        depth++;
        open_ChunkOctree(chunk_octree);
        for (int i = 0; i < octree_length; i++) {
            randomize_inner_nodes(&chunk_octree->nodes[i], depth);
        }
    }
}

void fill_octree(ChunkOctree* node, unsigned char voxel, unsigned char depth) {
    node->value = voxel;
    if (depth > 0) {
        depth--;
        open_ChunkOctree(node);
        for (int i = 0; i < octree_length; i++) {
            fill_octree(&node->nodes[i], voxel, depth);
        }
    }
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
}

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
            // calculates sub node position
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

void generate_terrain_height_map(ChunkOctree* chunk_octree, unsigned char depth,
    float3 position, int3 local_position, double* height_map, int2 map_size, ChunkOctreePool *pool) {
    int depth_left = max_octree_depth - depth;
    int division_left = powers_of_two[depth_left]; //  pow(2, depth_left);
    int2 map_position = (int2) { local_position.x * division_left, local_position.z * division_left };
    int height_map_index = int2_array_index(map_position, map_size);
    // int height_map_index = 0;
    double octree_noise = height_map[height_map_index];
    if (octree_noise < octree_min_height) {
        octree_noise = octree_min_height;
    }
    /*if (position.x >= 0 && position.x <= 1.0f
        && position.y >= 0 && position.y <= 1.0f
        && position.z >= 0 && position.z <= 1.0f)
    {
        printf("depth: %i - depth_left: %i\n", depth, depth_left);
        //printf("height_map_index: %i - division_left: %i \n",
        //    height_map_index, division_left);
        printf("    - position: %fx%f\n", position.x, position.z);
        printf("    - local_position: %ix%i\n", local_position.x, local_position.y);
        printf("    - map_position: %ix%i\n", map_position.x, map_position.y);
    }*/
    // octree_noise += octree_height_addition * octree_perlin_noise(position.x, position.y, position.z,
    //    octree_persistence, octree_frequency);
    if (position.y <= octree_noise) {
        chunk_octree->value = 1;
        if (depth < max_octree_depth) {
            depth++;
            #ifdef voxels_use_octree_pooling
                if (chunk_octree->nodes == NULL) {
                    if (pool->used + octree_length >= pool->allocated) {
                        printf("Used Max: %i\n", pool->used);
                        return;
                    }
                    chunk_octree->nodes = &pool->pool[pool->used];
                    pool->used += octree_length;
                    for (unsigned char i = 0; i < octree_length; i++) {
                        chunk_octree->nodes[i].nodes = NULL;
                        chunk_octree->nodes[i].value = 0;
                    }
                    // printf("Used: %i\n", pool->used);
                }
            #else
                open_ChunkOctree(chunk_octree);
            #endif
            for (unsigned char i = 0; i < octree_length; i++) {
                // calculates sub node position
                float3 node_position = float3_add(position, float3_multiply_float(octree_positions_float3s[i], octree_scales[depth]));
                int3 node_local_position = int3_add(octree_positions[i], int3_multiply_int(local_position, 2));
                generate_terrain_height_map(&chunk_octree->nodes[i], depth, node_position, node_local_position, height_map, map_size, pool);
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
}

void generate_height_map(double* height_map, float3 position, int2 map_size) {
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
}

void OctreeTerrainChunkSystem(ecs_iter_t *it) {
    if (disable_chunk_systems) return;
    if (!ecs_query_changed(it->ctx, NULL)) {
        return;
    }
    #ifdef zoxel_time_octree_terrain_chunk_system
        begin_timing()
    #endif
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 2);
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 3);
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 4);
    ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 5);
    //int max_size = pow(2, max_octree_depth + 1);
    //int2 map_size = (int2) { max_size, max_size };
    unsigned char is_table_dirty = 0;
    for (int i = 0; i < it->count; i++) {
        const GenerateChunk *generateChunk = &generateChunks[i];
        if (generateChunk->value == 1) {
            is_table_dirty = 1;
            break;
        }
    }
    if (is_table_dirty) {
        //printf("Initializing Pool.\n");
        // ChunkOctreePool *pool = malloc(sizeof(ChunkOctreePool));
        #ifdef voxels_use_octree_pooling
        //pool->allocated = 8 * 6 * 16 * 1024; // octree_length * octree_length * octree_length;    // 8x8x8 nodes
        //pool->pool = malloc(sizeof(ChunkOctree) * pool->allocated);
        //pool->used = 0;
        #endif
        unsigned char target_depth = max_octree_depth; //  - 1;
        unsigned char chunk_voxel_length = powers_of_two_byte[target_depth];
        float2 map_size_f = (float2) { chunk_voxel_length, chunk_voxel_length };
        // printf("chunk_voxel_length: %i\n", chunk_voxel_length);
        // double *height_map = malloc(sizeof(double) * map_size.x * map_size.y);
        for (int i = 0; i < it->count; i++) {
            const GenerateChunk *generateChunk = &generateChunks[i];
            if (generateChunk->value == 0) {
                continue;
            }
            ChunkDirty *chunkDirty = &chunkDirtys[i];
            if (chunkDirty->value != 0) {
                continue;
            }
            chunkDirty->value = 1;
            ChunkOctree *chunkOctree = &chunkOctrees[i];
            const ChunkPosition *chunkPosition = &chunkPositions[i];
            float3 chunk_position_float3 = float3_from_int3(chunkPosition->value);
            // fill_octree(chunkOctree, 1, target_depth);
            fill_octree(chunkOctree, 0, target_depth);
            // generate_height_map(height_map, chunk_position_float3, map_size);
            for (unsigned char i = 0; i < chunk_voxel_length; i++) {
                for (unsigned char k = 0; k < chunk_voxel_length; k++) {
                    // int2 map_position = (int2) { i, k };
                    // int height_map_index = int2_array_index(map_position, map_size);
                    // double height_d = height_map[height_map_index];
                    int height = int_floor(-terrain_minus_amplifier + terrain_amplifier * perlin_terrain(
                        noise_positiver2 + chunk_position_float3.x + (i / map_size_f.x), 
                        noise_positiver2 + chunk_position_float3.z + (k / map_size_f.y),
                        terrain_frequency, terrain_seed, terrain_octaves));
                    // int height = height_d;
                    // int height = (chunk_voxel_length / 2) - 1;
                    int j_start = height - (chunk_position_float3.y * chunk_voxel_length);
                    if (j_start < 0) {
                        j_start = -1;
                    }
                    if (j_start >= chunk_voxel_length) {
                        j_start = chunk_voxel_length - 1;
                    }
                    for (int j = j_start; j >= 0; j--) {
                        int3 voxel_position = (int3) { i, j, k };
                        if (set_octree_voxel(1, target_depth, chunkOctree, voxel_position, 0) == 1) {
                            // printf("Failed to set voxel: %ix%ix%i\n", voxel_position.x, voxel_position.y, voxel_position.z);
                            break;
                        }
                    }
                }
            }
            // now close all solid ground nodes
            #ifdef voxels_close_octree_nodes
                close_solid_nodes(chunkOctree);
            #endif
            // randomize_inner_nodes(chunkOctree, 0);
            // fill_octree(chunkOctree, 1, max_octree_depth - 1);
            // generate_terrain(chunkOctree, 0, chunk_position_float3, 1.0f);
            // try with a big pool
            /*
            generate_terrain_height_map(chunkOctree, 0,
                chunk_position_float3, int3_zero, // 1.0f,
                height_map, map_size, pool);*/
            
            // test timing
            //for (int j = 0; j < 4096 * 8; j++)
            //    if (rand() % 101 >= 99);
            //for (int j = 0; j < 4096; j++)
            //    if (rand() % 10001 >= 9999);
            #ifdef zoxel_time_octree_terrain_chunk_system
                did_do_timing()
            #endif
        }
        // #ifdef voxels_use_octree_pooling
        // printf("Used: %i out of Allocated: %i\n", pool->used, pool->allocated);
        // #endif
        // free(pool);
        // free(height_map);
    }
    #ifdef zoxel_time_octree_terrain_chunk_system
        end_timing("    - OctreeTerrainChunkSystem")
    #endif
}
zoxel_declare_system(OctreeTerrainChunkSystem)

// use heightmap 16x16 - and just read this per value

  //  * 16
    /*if (octree_noise < 0.0)
    {
        octree_noise *= 100.0;
        // printf("    [%f]   ", octree_noise);
        printf("    [%f:%f]   ", octree_noise, position.y);
    }*/
    // octree_noise *= 0.01 * terrain_amplifier;
    // octree_noise += 0.33;
    // octree_noise *= 100.0;
    
    // octree_noise *= 2.0;
    // octree_noise -= 1.0;

    //octree_noise *= 4.0;
    /*octree_noise -= 0.2;
    octree_noise *= 8.0;
    octree_noise *= 4.0;*/
    // octree_noise += position.y * 0.1f;
    // printf("    [%f]   ", position.y);
    // printf("    [%f:%f]   ", position.x, position.z);
    // double octree_noise = (rand() % 101) / 100.0f;
    // double octree_noise = ((int)(100 * (position.x + 3200)) % 100) / 100.0f;
    /*for (int i = 0; i < 4; i++)
    {
        chunkOctree->nodes[i].value = 1;
    }
    for (int i = 0; i < 4; i++)
    {
        if (rand() % 100 >= 60)
        {
            chunkOctree->nodes[4 + i].value = 1;
        }
    }*/
    // srand(666);
    /*int3 local_position;
    int3 global_position;
    int3 chunk_position_offset = voxel_chunk_position_xz(chunkPosition, chunkSize);
    for (local_position.x = 0; local_position.x < chunkSize.x; local_position.x++)
    {
        for (local_position.z = 0; local_position.z < chunkSize.z; local_position.z++)
        {
            local_position.y = 0;
            global_position = int3_add(local_position, chunk_position_offset);
            // printf("global_position [%ix%ix%i]\n", global_position.x, global_position.y, global_position.z);
            // printf("global_position: [%fx%fx%f]\n", global_position.x, global_position.y, global_position.z);
            float2 noise_point = float2_from_int2((int2) { global_position.x, global_position.z });
            noise_point.x += 3200;
            noise_point.y += 3200;
            int terrain_height2 = terrain_min_height +
                // int_floor(terrain_amplifier * simplex_fun_2D(noise_point, terrain_frequency));
                // int_floor(terrain_amplifier * perlin_noise(noise_point.x, noise_point.y, terrain_frequency, seed));
                int_floor(terrain_amplifier * perlin_terrain(noise_point.x, noise_point.y,
                    terrain_frequency, terrain_seed, terrain_octaves));
                // int_floor(terrain_amplifier * generate_noise_2D(noise_point, terrain_frequency));
            if (terrain_height2 < terrain_min_height)
            {
                terrain_height2 = terrain_min_height;
            }
            // unsigned char terrain_height2 = terrain_height + rand() % terrain_height_amplifier;
            for (local_position.y = 0; local_position.y < chunkSize.y; local_position.y++)
            {
                int array_index = int3_array_index(local_position, chunkSize);
                if (local_position.y <= terrain_height2)
                {
                    chunk->value[array_index] = 1;
                }
                else
                {
                    chunk->value[array_index] = 0;
                }
                // valueRange.x + rand() % (valueRange.y - valueRange.x);
                // array_index++;
            }
        }
    }*/

/*double octree_noise(double x, double y, double z) {
    int X = (int)floor(x) & 255,                  // FIND UNIT CUBE THAT
        Y = (int)floor(y) & 255,                  // CONTAINS POINT.
        Z = (int)floor(z) & 255;
    x -= floor(x);                                // FIND RELATIVE X,Y,Z
    y -= floor(y);                                // OF POINT IN CUBE.
    z -= floor(z);
    double u = fade(x),                                // COMPUTE FADE CURVES
           v = fade(y),                                // FOR EACH OF X,Y,Z.
           w = fade(z);
    int A = p[X  ]+Y, AA = p[A]+Z, AB = p[A+1]+Z,      // HASH COORDINATES OF
        B = p[X+1]+Y, BA = p[B]+Z, BB = p[B+1]+Z;      // THE 8 CUBE CORNERS,
    return lerp(w, lerp(v, lerp(u, grad(p[AA  ], x  , y  , z   ),  // AND ADD
                                   grad(p[BA  ], x-1, y  , z   )), // BLENDED
                           lerp(u, grad(p[AB  ], x  , y-1, z   ),  // RESULTS
                                   grad(p[BB  ], x-1, y-1, z   ))),// FROM  8
                   lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),  // CORNERS
                                   grad(p[BA+1], x-1, y  , z-1 )), // OF CUBE
                           lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
                                   grad(p[BB+1], x-1, y-1, z-1 ))));
}*/
/*

double octree_noise(int x, int y, int z) {
    int n = x + y * 57 + z * 113;
    n = (n << 13) ^ n;
    return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}


double octree_interpolate(double a, double b, double x) {
    double ft = x * 3.1415927;
    double f = (1 - cos(ft)) * 0.5;
    return  a*(1-f) + b*f;
}

double octree_smooth_noise(double x, double y, double z) {
    double corners = ( octree_noise(x-1, y-1, z-1) + octree_noise(x+1, y-1, z-1) + octree_noise(x-1, y+1, z-1) + octree_noise(x+1, y+1, z-1) +
                    octree_noise(x-1, y-1, z+1) + octree_noise(x+1, y-1, z+1) + octree_noise(x-1, y+1, z+1) + octree_noise(x+1, y+1, z+1) ) / 16;
    double sides   = ( octree_noise(x-1, y, z) + octree_noise(x+1, y, z) + octree_noise(x, y-1, z) + octree_noise(x, y+1, z) +
                    octree_noise(x, y, z-1) + octree_noise(x, y, z+1) ) / 8;
    double center  =  octree_noise(x, y, z) / 4;
    return corners + sides + center;
}


double octree_interpolated_noise(double x, double y, double z) {
    int int_x = (int)x;
    int int_y = (int)y;
    int int_z = (int)z;
    double frac_x = x - int_x;
    double frac_y = y - int_y;
    double frac_z = z - int_z;
    double v1 = octree_smooth_noise(int_x, int_y, int_z);
    double v2 = octree_smooth_noise(int_x + 1, int_y, int_z);
    double v3 = octree_smooth_noise(int_x, int_y + 1, int_z);
    double v4 = octree_smooth_noise(int_x + 1, int_y + 1, int_z);
    double i1 = octree_interpolate(v1, v2, frac_x);
    double i2 = octree_interpolate(v3, v4, frac_x);
    double i3 = octree_interpolate(i1, i2, frac_y);
    v1 = octree_smooth_noise(int_x, int_y, int_z + 1);
    v2 = octree_smooth_noise(int_x + 1, int_y, int_z + 1);
    v3 = octree_smooth_noise(int_x, int_y + 1, int_z + 1);
    v4 = octree_smooth_noise(int_x + 1, int_y + 1, int_z + 1);
    i1 = octree_interpolate(v1, v2, frac_x);
    i2 = octree_interpolate(v3, v4, frac_x);
    i3 = octree_interpolate(i1, i2, frac_y);
    double i4 = x;
    i4 = octree_interpolate(i3, i4, frac_z);
    return i4;
}

double octree_perlin_noise(double x, double y, double z, double persistence, double frequency) {
    double total = 0;
    double p = persistence;
    double n = frequency;
    for (int i = 0; i < octree_octaves; i++)
    {
        double frequency = pow(2, i);
        double amplitude = pow(p, i);
        total = total + octree_interpolated_noise(x * frequency, y * frequency, z * frequency) * amplitude;
    }
    return (total + 1.0) / 2.0;
}*/

// #define octree_min_height 0.005f
// #define octree_height_addition 0.4f
// #define octree_terrain_frequency 0.001f
// #define octree_terrain_frequency 0.001f
// 3200 2147483647 / 2
// #define octree_octaves 6
// #define octree_persistence 0.5f
// #define octree_frequency 0.5f