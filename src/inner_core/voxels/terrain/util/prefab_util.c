void add_components_mesh_textured(ecs_world_t *world, const ecs_entity_t e) {
    if (headless) return;
    zox_add(e, MeshIndicies)
    zox_add(e, MeshVertices)
    zox_add(e, MeshUVs)
    zox_add(e, MeshColorRGBs)
    add_gpu_mesh(world, e);
    // add_gpu_material(world, e);
    add_gpu_uvs(world, e);
    add_gpu_texture(world, e);
    add_gpu_colors(world, e);
}

void set_chunk_neighbors(ecs_world_t *world, ecs_entity_t e, ecs_entity_t chunk_left, ecs_entity_t chunk_right, ecs_entity_t chunk_back, ecs_entity_t chunk_front) {
    ChunkNeighbors *chunkNeighbors = zox_get_mut(e, ChunkNeighbors)
    resize_memory_component(ChunkNeighbors, chunkNeighbors, ecs_entity_t, 4)
    chunkNeighbors->value[0] = chunk_left;
    chunkNeighbors->value[1] = chunk_right;
    chunkNeighbors->value[2] = chunk_back;
    chunkNeighbors->value[3] = chunk_front;
    zox_modified(e, ChunkNeighbors)
}

void set_chunk_neighbors_six_directions(ecs_world_t *world, ecs_entity_t e, ecs_entity_t chunk_left, ecs_entity_t chunk_right, ecs_entity_t chunk_down, ecs_entity_t chunk_up, ecs_entity_t chunk_back, ecs_entity_t chunk_front) {
    ChunkNeighbors *chunkNeighbors = zox_get_mut(e, ChunkNeighbors)
    resize_memory_component(ChunkNeighbors, chunkNeighbors, ecs_entity_t, 6)
    chunkNeighbors->value[0] = chunk_left;
    chunkNeighbors->value[1] = chunk_right;
    chunkNeighbors->value[2] = chunk_down;
    chunkNeighbors->value[3] = chunk_up;
    chunkNeighbors->value[4] = chunk_back;
    chunkNeighbors->value[5] = chunk_front;
    zox_modified(e, ChunkNeighbors)
}
