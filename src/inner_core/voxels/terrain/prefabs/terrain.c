ecs_entity_t prefab_terrain;
ecs_entity_t main_terrain_world;

ecs_entity_t spawn_prefab_terrain(ecs_world_t *world) {
    ecs_defer_begin(world);
    // ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, voxel_prefab);
    ecs_entity_t e = ecs_new_prefab(world, "");
    // ecs_entity_t e = ecs_new(world, 0, voxel_prefab, 1);
    // ecs_add_id(world, e, EcsPrefab);
    // set_unique_entity_name(world, e, "prefab_terrain_chunk");
    // ecs_set_name(world, e, "prefab_terrain_chunk");
    zoxel_add_tag(world, e, TerrainWorld)
    zoxel_add(world, e, ChunkLinks)
    #ifndef voxels_terrain_multi_material
        zoxel_add_tag(world, e, DirtTexture);
        add_texture(world, e, chunk_texture_size, 1);
        add_noise_texture(world, e);
        add_gpu_texture(world, e);
    #endif
    ecs_defer_end(world);
    prefab_terrain = e;
    return e;
}

ecs_entity_t spawn_terrain(ecs_world_t *world, ecs_entity_t prefab, float3 position, float scale) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    set_unique_entity_name(world, e, "terrain");
    ecs_set(world, e, Position3D, { position });
    ecs_set(world, e, Scale1D, { scale });
    #ifndef voxels_terrain_multi_material
        spawn_gpu_material(world, e, shader3D_textured);
        spawn_gpu_texture(world, e);
    #endif
    ecs_defer_end(world);
    main_terrain_world = e;
    return e;
}