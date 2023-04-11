ecs_entity_t character3D_prefab;
ecs_entity_t main_character3D;
// ecs_entity_t_array_d* characters;

ecs_entity_t spawn_prefab_character3D(ecs_world_t *world) {
    // characters = create_ecs_entity_t_array_d();
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_vox);
    ecs_add_id(world, e, EcsPrefab);
    set_unique_entity_name(world, e, "prefab_character3D");
    add_seed(world, e, 999);
    add_physics3D_basic(world, e);
    if (!headless) {
        ecs_remove(world, e, MaterialGPULink);
        add_gpu_colors(world, e);
    }
    zoxel_add_tag(world, e, LinkChunk)
    zoxel_add(world, e, VoxLink)
    zoxel_set(world, e, ChunkLink, { 0 })
    zoxel_set(world, e, ChunkPosition, { int3_zero })
    zoxel_set(world, e, VoxelPosition, {{ 0, 0, 0 }})
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab character3D [%lu].\n", (long int) (e));
    #endif
    character3D_prefab = e;
    return e;
}

ecs_entity_t spawn_character3D(ecs_world_t *world, ecs_entity_t prefab, vox_file *vox,
    float3 position, float4 rotation, float scale) { //, unsigned char is_multithread) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    zoxel_set(world, e, Position3D, { position })
    zoxel_set(world, e, Scale1D, { scale })
    zoxel_set(world, e, Rotation3D, { rotation })
    zoxel_set(world, e, VoxLink, { main_terrain_world })
    set_vox_from_vox_file(world, e, vox);
    /*if (!headless && !is_multithread) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_colors(world, e);
    }*/
    ecs_defer_end(world);
    main_character3D = e;
    return e;
}

// zoxel_add(world, e, VoxelPosition)
// zoxel_add(world, e, ChunkLink)
// zoxel_add(world, e, ChunkPosition)