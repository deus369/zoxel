const float skybox_scale = 1024.0f;
ecs_entity_t prefab_skybox;
ecs_entity_t skybox;

ecs_entity_t spawn_prefab_skybox(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_skybox")
    #ifdef zoxel_transforms3D
        add_transform3Ds(world, e);
    #endif
    #ifdef zoxel_rendering
        zox_add(e, Brightness)
        zox_set(e, MeshDirty, { 1 })
        if (!headless) prefab_set_mesh_indicies(world, e, cube_indicies_inverted, 36);
        if (!headless) prefab_set_mesh_vertices(world, e, cubeVertices, 24);
        add_gpu_mesh(world, e);
        add_gpu_material(world, e);
    #endif
    ecs_defer_end(world);
    prefab_skybox = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" + spawned prefab skybox [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_skybox(ecs_world_t *world) {
    zox_instance(prefab_skybox)
    zox_name("skybox")
    zox_set_only(e, Position3D, { float3_zero })
    zox_set_only(e, Scale1D, { skybox_scale })
    zox_set_only(e, Brightness, { 1.0f })
    if (!headless) spawn_gpu_mesh(world, e);
    if (!headless) spawn_gpu_material(world, e, shader_skybox);
    skybox = e;
    #ifdef zoxel_debug_spawns
        zoxel_log(" + spawned skybox [%lu]\n", (long int) e);
    #endif
    return e;
}