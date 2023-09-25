int get_chunk_index(int i, int j, int rows) {
    return (i + rows + 1) * (rows + rows + 1) + (j + rows + 1);
}

// vertical_rows + vertical_rows +  - rows + rows + 1
int get_terrain_chunks_count(int rows, int slabs) {
    return (slabs + slabs + 1) * (rows + rows + 1) * (rows + rows + 1);
}

int get_chunk_index_2(int i, int j, int k, int rows, int vertical) {
    i += rows;
    j += vertical;
    k += rows;
    return i * (rows + rows + 1) + j * (rows + rows + 1) * (rows + rows + 1) + k;
}

ecs_entity_t create_terrain(ecs_world_t *world, int3 center_position) {
    ecs_defer_begin(world);
    //zoxel_log(" > spawning terrain [%lu] at [%ix%ix%i]\n", camera, camera_position.x, camera_position.y, camera_position.z);
    //zoxel_log("     - at [%fx%fx%f]\n", camera_position3D->value.x, camera_position3D->value.y, camera_position3D->value.z);
    #ifdef zox_time_create_terrain
        begin_timing_absolute()
    #endif
    #ifdef zox_disable_terrain_octrees
        terrain_vertical = 0;
    #endif
    ecs_entity_t tilemap = spawn_tilemap(world);
    int chunks_total_length = get_terrain_chunks_count(terrain_spawn_distance, terrain_vertical);
    ecs_entity_t terrain_world = spawn_terrain(world, prefab_terrain, tilemap, float3_zero, 1.0f);  // todo link world to chunks and vice versa
    ecs_entity_t chunks[chunks_total_length];
    int3 chunk_positions[chunks_total_length];
    for (int i = -terrain_spawn_distance; i <= terrain_spawn_distance; i++) {
        for (int k = -terrain_spawn_distance; k <= terrain_spawn_distance; k++) {
            for (int j = -terrain_vertical; j <= terrain_vertical; j++) {
                int3 chunk_position = (int3) { i, j, k };
                int index = get_chunk_index_2(i, j, k, terrain_spawn_distance, terrain_vertical);
                float3 real_chunk_position = float3_multiply_float(float3_from_int3(chunk_position), real_chunk_scale);
                #ifndef zox_disable_terrain_octrees
                    #ifndef zox_bulk_spawn_terrain
                        chunks[index] = spawn_terrain_chunk_octree(world, prefab_terrain_chunk_octree, terrain_world, center_position, chunk_position, real_chunk_position, 0.5f);
                    #endif
                    chunk_positions[index] = chunk_position;
                #else
                    chunks[index] = spawn_terrain_chunk(world, prefab_terrain_chunk, chunk_position, (float3) { i * real_chunk_scale, 0, k * real_chunk_scale }, 0.5f);
                #endif
            }
        }
    }
    #ifdef zox_bulk_spawn_terrain
        ChunkPosition *chunkPositions = malloc(sizeof(ChunkPosition) * chunks_total_length);
        Position3D *position3Ds = malloc(sizeof(Position3D) * chunks_total_length);
        RenderLod *renderLods = malloc(sizeof(RenderLod) * chunks_total_length);
        VoxLink *voxLinks = malloc(sizeof(VoxLink) * chunks_total_length);
        MeshGPULink *meshGPULinks = malloc(sizeof(MeshGPULink) * chunks_total_length);
        UvsGPULink *uvsGPULinks = malloc(sizeof(UvsGPULink) * chunks_total_length);
        ColorsGPULink *colorsGPULinks = malloc(sizeof(ColorsGPULink) * chunks_total_length);
        for (int i = 0; i < chunks_total_length; i++) {
            const int3 chunk_position = chunk_positions[i];
            chunkPositions[i].value = chunk_position;
            position3Ds[i].value = float3_multiply_float(float3_from_int3(chunk_position), real_chunk_scale);
            renderLods[i].value = get_chunk_division(int3_zero, chunk_position);
            voxLinks[i].value = terrain_world;
            if (!headless) {
                meshGPULinks[i].value = spawn_gpu_mesh_buffers();
                uvsGPULinks[i].value = spawn_gpu_generic_buffer();
                colorsGPULinks[i].value = spawn_gpu_generic_buffer();
            }
        }
        // const ecs_entity_t *particles2DArray = 
        const ecs_entity_t *entities = ecs_bulk_init(world, &(ecs_bulk_desc_t) {
            .count = chunks_total_length,
            .ids = {
                ecs_pair(EcsIsA, prefab_terrain_chunk_octree),
                ecs_id(ChunkPosition),
                ecs_id(Position3D),
                ecs_id(RenderLod),
                ecs_id(VoxLink),
                ecs_id(MeshGPULink),
                ecs_id(UvsGPULink),
                ecs_id(ColorsGPULink)
            },
            // provide data for each id
            .data = (void*[]) {       
                NULL,           // Prefab pair, what is it used for?
                chunkPositions,
                position3Ds,
                renderLods,
                voxLinks,
                meshGPULinks,
                uvsGPULinks,
                colorsGPULinks
            }
        });
        for (int i = 0; i < chunks_total_length; i++) chunks[i] = entities[i];
        free(chunkPositions);
        free(position3Ds);
        free(renderLods);
        free(voxLinks);
        free(meshGPULinks);
        free(uvsGPULinks);
        free(colorsGPULinks);
    #endif
    // now for all of them, set their neighbors
    for (int i = -terrain_spawn_distance; i <= terrain_spawn_distance; i++) {
        for (int k = -terrain_spawn_distance; k <= terrain_spawn_distance; k++) {
            for (int j = -terrain_vertical; j <= terrain_vertical; j++) {
                #ifndef zox_disable_terrain_octrees
                    set_chunk_neighbors_six_directions(world,
                        chunks[get_chunk_index_2(i, j, k, terrain_spawn_distance, terrain_vertical)],
                        i == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i - 1, j, k, terrain_spawn_distance, terrain_vertical)],
                        i == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i + 1, j, k, terrain_spawn_distance, terrain_vertical)],
                        j == -terrain_vertical ? 0 : chunks[get_chunk_index_2(i, j - 1, k, terrain_spawn_distance, terrain_vertical)],
                        j == terrain_vertical ? 0 : chunks[get_chunk_index_2(i, j + 1, k, terrain_spawn_distance, terrain_vertical)],
                        k == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k - 1, terrain_spawn_distance, terrain_vertical)],
                        k == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k + 1, terrain_spawn_distance, terrain_vertical)]);
                #else
                    set_chunk_neighbors(world,
                        chunks[get_chunk_index_2(i, j, k, terrain_spawn_distance, 0)],
                        i == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i - 1, j, k, terrain_spawn_distance, 0)],
                        i == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i + 1, j, k, terrain_spawn_distance, 0)],
                        k == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k - 1, terrain_spawn_distance, 0)],
                        k == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k + 1, terrain_spawn_distance, 0)]);
                #endif
            }
        }
    }
    ChunkLinks *chunkLinks = ecs_get_mut(world, terrain_world, ChunkLinks);
    chunkLinks->value = create_int3_hash_map(chunks_total_length);
    for (int i = 0; i < chunks_total_length; i++) int3_hash_map_add(chunkLinks->value, chunk_positions[i], chunks[i]);
    ecs_modified(world, terrain_world, ChunkLinks);
    #ifdef zox_time_create_terrain
        end_timing_absolute("    - create_terrain")
    #endif
    ecs_defer_end(world);
    return terrain_world;
}

void dispose_opengl_resources_terrain(ecs_world_t *world) {
    if (local_terrain == 0) return;
    const TilemapLink *tilemapLink = ecs_get(world, local_terrain, TilemapLink);
    dispose_material_resources(world, tilemapLink->value);
    const ChunkLinks *chunkLinks = ecs_get(world, local_terrain, ChunkLinks);
    for (int i = 0; i < chunkLinks->value->size; i++) {
        int3_hash_map_pair* pair = chunkLinks->value->data[i];
        while (pair != NULL) {
            ecs_entity_t terrain_chunk = pair->value;
            dispose_mesh_resources(world, terrain_chunk);
            pair = pair->next;
        }
    }
}

void restore_opengl_resources_terrain(ecs_world_t *world) {
    if (local_terrain == 0) return;
    const ChunkLinks *chunkLinks = ecs_get(world, local_terrain, ChunkLinks);
    for (int i = 0; i < chunkLinks->value->size; i++) {
        int3_hash_map_pair* pair = chunkLinks->value->data[i];
        while (pair != NULL) {
            ecs_entity_t terrain_chunk = pair->value;
            restore_mesh_resources(world, terrain_chunk);
            pair = pair->next;
        }
    }
    const TilemapLink *tilemapLink = ecs_get(world, local_terrain, TilemapLink);
    restore_material_resources(world, tilemapLink->value, get_shader3D_textured_value(world), 0);
    // zoxel_log(" > shader restore [%ix%i]\n", get_shader3D_textured_value(world).x, get_shader3D_textured_value(world).y);
}