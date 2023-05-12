ecs_entity_t prefab_chunk;

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
    #ifdef zox_disable_vox_octrees
        add_chunk(world, e, default_chunk_size);
    #else
        add_chunk_octree(world, e, default_chunk_size);
    #endif
    add_generate_chunk(world, e);
    if (!headless) {
        zoxel_add(world, e, MeshIndicies);
        zoxel_add(world, e, MeshVertices);
        add_gpu_mesh(world, e);
        add_gpu_material(world, e);
        zoxel_add(world, e, MeshColorRGBs);
        zoxel_add(world, e, ColorsGPULink);
    }
    ecs_defer_end(world);
    prefab_chunk = e;
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