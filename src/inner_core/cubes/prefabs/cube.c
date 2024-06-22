ecs_entity_t prefab_cube;

ecs_entity_t spawn_prefab_cube(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_cube")
    add_transform3Ds(world, e, 1);
    zox_add(e, Brightness)
    zox_prefab_set(e, MeshDirty, { 1 })
    if (!headless) {
        zox_prefab_add(e, MeshIndicies)
        zox_prefab_add(e, MeshVertices)
        prefab_set_mesh_indicies(world, e, cube_indicies, 36);
        prefab_set_mesh_vertices(world, e, cube_vertices_singles, cube_vertices_singles_length);
        add_gpu_mesh(world, e);
        add_gpu_material(world, e);
    }
    prefab_cube = e;
    return e;
}

ecs_entity_t spawn_cube(ecs_world_t *world, ecs_entity_t prefab, float3 position) {
    zox_instance(prefab)
    zox_name("cube")
    zox_set(e, Position3D, { position })
    zox_set(e, Scale1D, { 0.05f })
    zox_set(e, Brightness, { 1.4f })
    float4 rotationer = quaternion_from_euler( (float3) { 0.1f * degreesToRadians, 0.2f * degreesToRadians, 0 });
    zox_set(e, EternalRotation, { rotationer })
    if (!headless) {
        spawn_gpu_mesh(world, e);
        spawn_gpu_material(world, e, shader3D);
    }
    return e;
}
