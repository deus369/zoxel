void add_generate_chunk(ecs *world, entity e) {
    zox_prefab_set(e, GenerateChunk, { 1 })
}

void add_noise_chunk(ecs *world, entity e) {
    zox_add_tag(e, NoiseChunk)
    zox_prefab_set(e, GenerateChunk, { 1 })
}

void prefab_add_mesh_basic(ecs *world, const entity e) {
    if (!headless) {
        zox_prefab_set(e, MeshIndicies, { 0, NULL });
        zox_prefab_set(e, MeshVertices, { 0, NULL });
        add_gpu_mesh(world, e);
    }
}

void add_components_mesh_textured(ecs *world, const entity e) {
    if (!headless) {
        zox_prefab_set(e, MeshUVs, { 0, NULL });
        zox_prefab_set(e, MeshColorRGBs, { 0, NULL });
        add_gpu_uvs(world, e);
        add_gpu_texture(world, e);
        add_gpu_colors(world, e);
    }
}

void prefab_add_chunk_colors(ecs *world, const entity e) {
    if (!headless) {
        zox_add_tag(e, ColorChunk)
        zox_prefab_set(e, ColorRGBs, { 0, NULL });
        zox_prefab_set(e, MeshColorRGBs, { 0, NULL });
    }
}

void add_components_mesh_colored(ecs *world, const entity e) {
    if (!headless) {
        prefab_add_chunk_colors(world, e);
        add_gpu_colors(world, e);
    }
}

void set_chunk_neighbors(ecs *world, entity e, entity chunk_left, entity chunk_right, entity chunk_back, entity chunk_front) {
    zox_get_muter(e, ChunkNeighbors, chunkNeighbors)
    // resize_memory_component(ChunkNeighbors, chunkNeighbors, entity, 4)
    chunkNeighbors->value[0] = chunk_left;
    chunkNeighbors->value[1] = chunk_right;
    chunkNeighbors->value[2] = chunk_back;
    chunkNeighbors->value[3] = chunk_front;
}

void set_chunk_neighbors_six_directions(ecs *world, entity e, entity chunk_left, entity chunk_right, entity chunk_down, entity chunk_up, entity chunk_back, entity chunk_front) {
    zox_get_muter(e, ChunkNeighbors, chunkNeighbors)
    // resize_memory_component(ChunkNeighbors, chunkNeighbors, entity, 6)
    chunkNeighbors->value[0] = chunk_left;
    chunkNeighbors->value[1] = chunk_right;
    chunkNeighbors->value[2] = chunk_down;
    chunkNeighbors->value[3] = chunk_up;
    chunkNeighbors->value[4] = chunk_back;
    chunkNeighbors->value[5] = chunk_front;
}