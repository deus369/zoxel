const unsigned char terrain_min_height = 1;
const float terrain_noise = 6.0f;
const float terrain_frequency = 0.02f;

int int_floor(float input)
{
    return (int) floor(input);
}

float simplex_fun_int_1D(float3 point, int ix)
{
    float x = point.x - ix;
    float f = 1.0f - x * x;
    float f2 = f * f;
    float f3 = f * f2;
    return f3;
}

float simplex_fun_1D(float3 point, float frequency)
{
    point = float3_multiply_float(point, frequency);
    int ix = int_floor(point.x);
    float sample = simplex_fun_int_1D(point, ix);
    sample += simplex_fun_int_1D(point, ix + 1);
    return sample * 2.0f - 1.0f;
}

float trianglesToSquares = (sqrt(3.0f) - 1.0f) / 2.0f;
float squaresToTriangles = (3.0f - sqrt(3.0f)) / 6.0f;

float simplex_fun_int_2D(float3 point, int ix, int iy)
{
    float unskew = (ix + iy) * squaresToTriangles;
    float x = point.x - ix + unskew;
    float y = point.z - iy + unskew;
    float f = 0.5f - x * x - y * y;
    if (f > 0.0f)
    {
        float f2 = f * f;
        float f3 = f * f2;
        return f3;
    }
    return 0.0f;
}

float simplex_fun_2D(float3 point, float frequency)
{
    point = float3_multiply_float(point, frequency);
    float skew = (point.x + point.z) * trianglesToSquares;
    float sx = point.x + skew;
    float sy = point.z + skew;
    int ix = int_floor(sx);
    int iy = int_floor(sy);
    float sample = simplex_fun_int_2D(point, ix, iy);
    sample += simplex_fun_int_2D(point, ix + 1, iy + 1);
    if (sx - ix >= sy - iy)
    {
        sample += simplex_fun_int_2D(point, ix + 1, iy);
    }
    else {
        sample += simplex_fun_int_2D(point, ix, iy + 1);
    }
    // return sample * 2.0f - 1.0f;
    return sample * (8.0f * 2.0f) - 1.0f;
}

//! Our function that creates a chunk.
void GenerateChunkTerrain(Chunk* chunk, const int3 chunkSize, const int3 chunkPosition)
{
    // const int2 valueRange = { 0, 2 };   // < max
     // (chunkSize->value.y / 4) + rand() % ((int) (chunkSize->value.y * (3.0f / 4.0f)));
    int3 local_position;
    int3 global_position;
    int3 chunk_position_offset = int3_multiply_int3(chunkPosition, chunkSize);
    if (chunk_position_offset.x < 0)
    {
        chunk_position_offset.x += 1;
    }
    if (chunk_position_offset.z < 0)
    {
        chunk_position_offset.z += 1;
    }
    //printf("chunkPosition: [%ix%ix%i]\n", chunkPosition.x, chunkPosition.y, chunkPosition.z);
    //printf("chunk_position_offset: [%ix%ix%i]\n",
    //    chunk_position_offset.x, chunk_position_offset.y, chunk_position_offset.z);
    // precount our face data for initialization
    for (local_position.x = 0; local_position.x < chunkSize.x; local_position.x++)
    {
        for (local_position.z = 0; local_position.z < chunkSize.z; local_position.z++)
        {
            local_position.y = 0;
            global_position = int3_add_int3(local_position, chunk_position_offset);
            // printf("global_position [%ix%ix%i]\n", global_position.x, global_position.y, global_position.z);
            // printf("global_position: [%fx%fx%f]\n", global_position.x, global_position.y, global_position.z);
            int terrain_height2 = terrain_min_height +
                int_floor(terrain_noise * simplex_fun_2D(float3_from_int3(global_position), terrain_frequency));
            if (terrain_height2 < terrain_min_height)
            {
                terrain_height2 = terrain_min_height;
            }
            // unsigned char terrain_height2 = terrain_height + rand() % terrain_noise;
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
                /*if (k == 0 && l == 0)
                    chunk->value[array_index] = 1;
                else
                    chunk->value[array_index] = 0;*/
                // array_index++;
            }
        }
    }
}

void TerrainChunkSystem(ecs_iter_t *it)
{
    ecs_query_t *changeQuery = it->ctx;
    if (!changeQuery || !ecs_query_changed(changeQuery, NULL))
    {
        return;
    }
    ChunkDirty *entityDirtys = ecs_field(it, ChunkDirty, 2);
    Chunk *chunks = ecs_field(it, Chunk, 3);
    const ChunkSize *chunkSizes = ecs_field(it, ChunkSize, 4);
    const ChunkPosition *chunkPositions = ecs_field(it, ChunkPosition, 5);
    const GenerateChunk *generateChunks = ecs_field(it, GenerateChunk, 6);
    for (int i = 0; i < it->count; i++)
    {
        const GenerateChunk *generateChunk = &generateChunks[i];
        //! Only rebuild if GenerateChunk is set to true and EntityDirty is false.
        if (generateChunk->value == 0)
        {
            continue;
        }
        ChunkDirty *entityDirty = &entityDirtys[i];
        if (entityDirty->value != 0)
        {
            continue;
        }
        entityDirty->value = 1;
        Chunk *chunk = &chunks[i];
        const ChunkSize *chunkSize = &chunkSizes[i];
        const ChunkPosition *chunkPosition = &chunkPositions[i];
        re_initialize_memory_component(chunk, unsigned char, chunkSize->value.x * chunkSize->value.y * chunkSize->value.z);
        GenerateChunkTerrain(chunk, chunkSize->value, chunkPosition->value);
        // printf("Terrain Chunk Generated: [%lu] \n", (long int) it->entities[i]);
    }
}
ECS_SYSTEM_DECLARE(TerrainChunkSystem);