#define octree_random_spawn_chance 90
#define octree_octaves 6
#define octree_persistence 0.5f
#define octree_frequency 0.5f
// #define octree_min_height 0.005f
#define octree_height_addition 0.4f
#define noise_positiver2 32000
// #define octree_terrain_frequency 0.001f
// #define octree_terrain_frequency 0.001f
// 3200 2147483647 / 2

//! Our function that creates a chunk.
void randomize_inner_nodes(ChunkOctree* chunk_octree, unsigned char depth)
{
    chunk_octree->value = rand() % 2;
    // chance to dig deeper
    if (depth < max_octree_depth && chunk_octree->value
        && rand() % 100 <= octree_random_spawn_chance - depth * 12)
    {
        depth++;
        open_ChunkOctree(chunk_octree);
        for (int i = 0; i < octree_length; i++)
        {
            randomize_inner_nodes(&chunk_octree->nodes[i], depth);
        }
    }
}

void fill_octree(ChunkOctree* chunk_octree, unsigned char voxel, unsigned char depth)
{
    chunk_octree->value = voxel;
    if (depth > 0)
    {
        depth--;
        open_ChunkOctree(chunk_octree);
        for (int i = 0; i < octree_length; i++)
        {
            fill_octree(&chunk_octree->nodes[i], voxel, depth);
        }
    }
    else
    {
        if (rand() % 1001 >= 999)
        {
            chunk_octree->value = 0;
        }
    }
}

void generate_terrain(ChunkOctree* chunk_octree, unsigned char depth, float3 position, float scale)
{
    double octree_noise = perlin_terrain(
        position.x + noise_positiver2, 
        position.z + noise_positiver2,
        terrain_frequency,
        terrain_seed, terrain_octaves);  //  * 16
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
    if (octree_noise < octree_min_height)
    {
        octree_noise = octree_min_height;
    }
    // octree_noise += octree_height_addition * octree_perlin_noise(position.x, position.y, position.z,
    //    octree_persistence, octree_frequency);
    if (position.y <= octree_noise)
    {
        chunk_octree->value = 1;
    }
    else
    {
        chunk_octree->value = 0;
    }
    if (depth < max_octree_depth && chunk_octree->value)
    {
        depth++;
        scale = scale * 0.5f;
        open_ChunkOctree(chunk_octree);
        for (unsigned char i = 0; i < octree_length; i++)
        {
            // calculates sub node position
            float3 node_position = float3_add(position,
                float3_multiply_float(float3_from_int3(octree_positions[i]), scale));
            generate_terrain(&chunk_octree->nodes[i], depth, node_position, scale);
        }
        // check all children
        #ifndef zoxel_disable_close_nodes
        unsigned char is_all_solid = 1;
        for (unsigned char i = 0; i < octree_length; i++)
        {
            if (chunk_octree->nodes[i].nodes != NULL || chunk_octree->nodes[i].value == 0)
            {
                is_all_solid = 0;
                break;
            }
        }
        if (is_all_solid)
        {
            close_ChunkOctree(chunk_octree);
        }
        #endif
    }
}

void OctreeTerrainChunkSystem(ecs_iter_t *it)
{
    if (disable_chunk_systems) return;
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    ChunkDirty *chunkDirtys = ecs_field(it, ChunkDirty, 2);
    ChunkOctree *chunkOctrees = ecs_field(it, ChunkOctree, 3);
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 5);
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 6);
    for (int i = 0; i < it->count; i++)
    {
        const GenerateChunk *generateChunk = &generateChunks[i];
        if (generateChunk->value == 0)
        {
            continue;
        }
        ChunkDirty *chunkDirty = &chunkDirtys[i];
        if (chunkDirty->value != 0)
        {
            continue;
        }
        chunkDirty->value = 1;
        ChunkOctree *chunkOctree = &chunkOctrees[i];
        const ChunkPosition *chunkPosition = &chunkPositions[i];
        // randomize_inner_nodes(chunkOctree, 0);
        // fill_octree(chunkOctree, 1, 4);
        generate_terrain(chunkOctree, 0, float3_from_int3(chunkPosition->value), 1.0f);
    }
}
zoxel_declare_system(OctreeTerrainChunkSystem)

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

double octree_noise(int x, int y, int z)
{
    int n = x + y * 57 + z * 113;
    n = (n << 13) ^ n;
    return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}


double octree_interpolate(double a, double b, double x)
{
    double ft = x * 3.1415927;
    double f = (1 - cos(ft)) * 0.5;
    return  a*(1-f) + b*f;
}

double octree_smooth_noise(double x, double y, double z)
{
    double corners = ( octree_noise(x-1, y-1, z-1) + octree_noise(x+1, y-1, z-1) + octree_noise(x-1, y+1, z-1) + octree_noise(x+1, y+1, z-1) +
                    octree_noise(x-1, y-1, z+1) + octree_noise(x+1, y-1, z+1) + octree_noise(x-1, y+1, z+1) + octree_noise(x+1, y+1, z+1) ) / 16;
    double sides   = ( octree_noise(x-1, y, z) + octree_noise(x+1, y, z) + octree_noise(x, y-1, z) + octree_noise(x, y+1, z) +
                    octree_noise(x, y, z-1) + octree_noise(x, y, z+1) ) / 8;
    double center  =  octree_noise(x, y, z) / 4;
    return corners + sides + center;
}


double octree_interpolated_noise(double x, double y, double z)
{
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

double octree_perlin_noise(double x, double y, double z, double persistence, double frequency)
{
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