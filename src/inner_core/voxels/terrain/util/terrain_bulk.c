
#ifdef zox_bulk_spawn_terrain
ecs_entity_t create_terrain_bulk(ecs_world_t *world, const ecs_entity_t prefab, const int3 center_position) {
    int chunks_total_length = calculate_terrain_chunks_count(terrain_spawn_distance, terrain_vertical);
    ecs_entity_t terrain_world = spawn_terrain(world, prefab_terrain, tilemap, float3_zero, 1);
    ecs_entity_t chunks[chunks_total_length];
    int3 chunk_positions[chunks_total_length];
    for (int i = -terrain_spawn_distance; i <= terrain_spawn_distance; i++) {
        for (int k = -terrain_spawn_distance; k <= terrain_spawn_distance; k++) {
            for (int j = -terrain_vertical; j <= terrain_vertical; j++) {
                int3 chunk_position = (int3) { i, j, k };
                chunk_positions[index] = chunk_position;
            }
        }
    }
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
        renderLods[i].value = get_camera_chunk_distance(int3_zero, chunk_position);
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
            ecs_pair(EcsIsA, prefab),
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
    // now for all of them, set their neighbors
    for (int i = -terrain_spawn_distance; i <= terrain_spawn_distance; i++) {
        for (int k = -terrain_spawn_distance; k <= terrain_spawn_distance; k++) {
            for (int j = -terrain_vertical; j <= terrain_vertical; j++) {
                set_chunk_neighbors_six_directions(world,
                    chunks[get_chunk_index_2(i, j, k, terrain_spawn_distance, terrain_vertical)],
                    i == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i - 1, j, k, terrain_spawn_distance, terrain_vertical)],
                    i == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i + 1, j, k, terrain_spawn_distance, terrain_vertical)],
                    j == -terrain_vertical ? 0 : chunks[get_chunk_index_2(i, j - 1, k, terrain_spawn_distance, terrain_vertical)],
                    j == terrain_vertical ? 0 : chunks[get_chunk_index_2(i, j + 1, k, terrain_spawn_distance, terrain_vertical)],
                    k == -terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k - 1, terrain_spawn_distance, terrain_vertical)],
                    k == terrain_spawn_distance ? 0 : chunks[get_chunk_index_2(i, j, k + 1, terrain_spawn_distance, terrain_vertical)]);
            }
        }
    }
    ChunkLinks *chunkLinks = zox_get_mut(terrain_world, ChunkLinks)
    chunkLinks->value = create_int3_hashmap(chunks_total_length);
    for (int i = 0; i < chunks_total_length; i++) int3_hashmap_add(chunkLinks->value, chunk_positions[i], chunks[i]);
    zox_modified(terrain_world, ChunkLinks)
    return terrain_world;
}
#endif
