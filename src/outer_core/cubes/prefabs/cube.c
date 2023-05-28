ecs_entity_t prefab_cube;

ecs_entity_t spawn_prefab_cube(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_cube")
    #ifdef zoxel_transforms3D
        add_transform3Ds(world, e);
    #endif
    #ifdef zoxel_rendering
        zox_add(e, Brightness)
        zox_set(e, MeshDirty, { 1 })
        if (!headless) {
            prefab_set_mesh_indicies(world, e, cubeIndicies, 36);
            prefab_set_mesh_vertices(world, e, cubeVertices, 24);
        }
        add_gpu_mesh(world, e);
        add_gpu_material(world, e);
    #endif
    ecs_defer_end(world);
    prefab_cube = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab custom_mesh [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_cube(ecs_world_t *world, ecs_entity_t prefab, float3 position) {
    ecs_defer_begin(world);
    zox_instance(prefab)
    zox_name("cube")
    zox_set_only(e, Position3D, { position })
    zox_set_only(e, Scale1D, { 0.05f })
    zox_set_only(e, Brightness, { 1.4f })
    float4 rotationer = quaternion_from_euler( (float3) { 0.1f * degreesToRadians, 0.2f * degreesToRadians, 0 });
    zox_set_only(e, EternalRotation, { rotationer })
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_material(world, e, shader3D);
    }
    ecs_defer_end(world);
    // zoxel_log("Spawned Character2D [%lu]\n", (long unsigned int) e);
    return e;
}