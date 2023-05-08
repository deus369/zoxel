ecs_entity_t voxel_prefab;

ecs_entity_t spawn_chunk_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    #ifdef zoxel_transforms3D
        add_transform3Ds(world, e);
        zoxel_set(world, e, Scale1D, { 0.05f });
    #endif
    zoxel_set(world, e, MeshDirty, { 0 });
    zoxel_set(world, e, Brightness, { 1.4f });
    add_seed(world, e, 666);
    add_chunk(world, e, default_chunk_size);
    add_generate_chunk(world, e);
    if (!headless) {
        zoxel_add(world, e, MeshIndicies);
        zoxel_add(world, e, MeshVertices);
    }
    add_gpu_mesh(world, e);
    add_gpu_material(world, e);
    ecs_defer_end(world);
    voxel_prefab = e;
    return e;
}

ecs_entity_t spawn_chunk(ecs_world_t *world, ecs_entity_t prefab, float3 position, float scale) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    ecs_set(world, e, Position3D, { position });
    ecs_set(world, e, Scale1D, { scale });
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_material(world, e, shader3D_colored);
    }
    ecs_defer_end(world);
    return e;
}