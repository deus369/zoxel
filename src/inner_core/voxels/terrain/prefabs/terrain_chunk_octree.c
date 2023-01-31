ecs_entity_t prefab_terrain_chunk_octree;

void add_chunk_octree(ecs_world_t *world, ecs_entity_t prefab, int3 size)
{
    zoxel_add_tag(world, prefab, Chunk);
    zoxel_add(world, prefab, ChunkOctree);
    zoxel_set(world, prefab, ChunkSize, { size });
    zoxel_set(world, prefab, ChunkDirty, { 0 });
    zoxel_set(world, prefab, ChunkPosition, { { 0, 0, 0 } });
    zoxel_set(world, prefab, ChunkDivision, { 0 });
}

ecs_entity_t spawn_prefab_terrain_chunk_octree(ecs_world_t *world, int3 size)
{
    int2 texture_size = { 16, 16 };
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, ""); // , "prefab_cube");
    #ifdef zoxel_transforms3D
    add_transform3Ds(world, e);
    zoxel_set(world, e, Scale1D, { 0.05f });
    #endif
    zoxel_set(world, e, MeshDirty, { 0 });
    zoxel_set(world, e, Brightness, { 1.4f });
    // zoxel_set(world, e, EntityDirty, { 1 });    // replace with MeshDirty
    add_seed(world, e, 666);
    add_chunk_octree(world, e, chunk_size);
    add_generate_chunk(world, e);
    if (!headless)
    {
        zoxel_add(world, e, MeshIndicies);
        zoxel_add(world, e, MeshVertices);
        add_gpu_mesh(world, e);
        add_gpu_material(world, e);
    }
    // rest
    zoxel_set(world, e, ChunkSize, { size });
    zoxel_add_tag(world, e, TerrainChunk);
    zoxel_set(world, e, ChunkNeighbors, { 0, NULL });
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
    prefab_terrain_chunk_octree = e;
    return e;
}

ecs_entity_t spawn_terrain_chunk_octree(ecs_world_t *world, ecs_entity_t prefab,
    int3 chunk_position, float3 position, float scale)
{
    ecs_defer_begin(world);
    ecs_entity_t e = spawn_terrain_chunk(world, prefab, chunk_position, position, scale);
    set_unique_entity_name(world, e, "terrain_chunk_octree");
    // unsigned char distance = ((int_abs(chunk_position.x) + int_abs(chunk_position.z)) / 2);
    unsigned char distance = int_max(int_abs(chunk_position.x), int_abs(chunk_position.z));
    ecs_set(world, e, ChunkDivision, { distance });
    ecs_defer_end(world);
    return e;
}