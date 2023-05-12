ecs_entity_t prefab_terrain_chunk_octree;

ecs_entity_t spawn_prefab_terrain_chunk_octree(ecs_world_t *world, int3 size) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, ""); // , "prefab_cube");
    zoxel_add_tag(e, TerrainChunk);
    #ifdef zoxel_transforms3D
        add_transform3Ds(world, e);
        zoxel_set(world, e, Scale1D, { 0.05f });
    #endif
    zoxel_set(world, e, MeshDirty, { 0 });
    zoxel_set(world, e, Brightness, { 1.4f });
    add_seed(world, e, 666);
    add_chunk_octree(world, e, size); // default_chunk_size);
    add_generate_chunk(world, e);
    // zoxel_set(world, e, ChunkSize, { size });
    if (!headless) {
        zoxel_add(world, e, MeshIndicies);
        zoxel_add(world, e, MeshVertices);
        zoxel_add(world, e, MeshUVs);
        zoxel_add(world, e, MeshColorRGBs);
        zoxel_add(world, e, ColorsGPULink);
        add_gpu_mesh(world, e);
        add_gpu_material(world, e);
        add_gpu_uvs(world, e);
        add_gpu_texture(world, e);
    }
    // rest
    // add_texture(world, e, chunk_texture_size, 1);
    // add_noise_texture(world, e);
    // zoxel_add_tag(e, DirtTexture);
    ecs_defer_end(world);
    prefab_terrain_chunk_octree = e;
    return e;
}

unsigned char get_chunk_division(int3 camera_position, int3 chunk_position) {
    unsigned char distance = int_max(int_abs(chunk_position.x - camera_position.x), int_abs(chunk_position.z - camera_position.z));
    return distance;
}

ecs_entity_t spawn_terrain_chunk_octree(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t terrain, int3 chunk_position, float3 position, float scale) {
    ecs_defer_begin(world);
    ecs_entity_t e = spawn_terrain_chunk(world, prefab, chunk_position, position, scale);
    set_unique_entity_name(world, e, "terrain_chunk_octree");
    ecs_set(world, e, ChunkDivision, { get_chunk_division(int3_zero, chunk_position) });
    ecs_set(world, e, VoxLink, { terrain });
    spawn_gpu_colors(world, e);
    ecs_defer_end(world);
    return e;
}

// unsigned char distance = ((int_abs(chunk_position.x) + int_abs(chunk_position.z)) / 2);
// unsigned char distance = int_max(int_abs(chunk_position.x), int_abs(chunk_position.z));