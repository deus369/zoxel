ecs_entity_t terrain_chunk_prefab;

ecs_entity_t spawn_prefab_terrain_chunk(ecs_world_t *world, int3 size)
{
    int2 texture_size = { 16, 16 };
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, voxel_prefab);
    set_unique_entity_name(world, e, "prefab_terrain_chunk");
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "prefab_terrain_chunk");
    zoxel_set(world, e, ChunkSize, { size });
    zoxel_add_tag(world, e, TerrainChunk);
    zoxel_set(world, e, ChunkNeighbors, { 0, NULL});
    add_texture(world, e, texture_size);
    add_noise_texture(world, e);
    zoxel_add_tag(world, e, DirtTexture);
    if (!headless)
    {
        zoxel_add(world, e, MeshUVs);
        add_gpu_uvs(world, e);
        add_gpu_texture(world, e);
    }
    ecs_defer_end(world);
    terrain_chunk_prefab = e;
    return e;
}

ecs_entity_t spawn_terrain_chunk(ecs_world_t *world, ecs_entity_t prefab,
    int3 chunk_position, float3 position, float scale)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    set_unique_entity_name(world, e, "terrain_chunk");
    ecs_set(world, e, ChunkPosition, { chunk_position });
    ecs_set(world, e, Position, { position });
    ecs_set(world, e, Scale1D, { scale });
    if (!headless)
    {
        spawn_gpu_mesh(world, e);
        spawn_gpu_material(world, e, shader3D_textured);
        spawn_gpu_uvs(world, e);
        spawn_gpu_texture(world, e);
    }
    ecs_defer_end(world);
    return e;
}

void set_chunk_neighbors(ecs_world_t *world, ecs_entity_t e,
    ecs_entity_t chunk_left, ecs_entity_t chunk_right, ecs_entity_t chunk_back, ecs_entity_t chunk_front)
{
    ChunkNeighbors chunkNeighbors = { };
    initialize_memory_component_non_pointer(chunkNeighbors, ecs_entity_t, 4);
    chunkNeighbors.value[0] = chunk_left;
    chunkNeighbors.value[1] = chunk_right;
    chunkNeighbors.value[2] = chunk_back;
    chunkNeighbors.value[3] = chunk_front;
    ecs_set(world, e, ChunkNeighbors, { chunkNeighbors.length, chunkNeighbors.value });
}

//ecs_entity_t chunk_down,
//ecs_entity_t chunk_up,
//chunkNeighbors.value[2] = chunk_down;
//chunkNeighbors.value[3] = chunk_up;