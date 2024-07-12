ecs_entity_t spawn_prefab_cube(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_cube")
    add_transform3Ds(world, e, 1);
    zox_add(e, Brightness)
    zox_prefab_set(e, MeshDirty, { 1 })
    if (!headless) {
        zox_prefab_add(e, MeshIndicies)
        zox_prefab_add(e, MeshVertices)
        add_gpu_mesh(world, e);
        add_gpu_material(world, e);
        prefab_set_mesh_indicies(world, e, cube_indicies, 36);
        prefab_set_mesh_vertices(world, e, cube_vertices_singles, cube_vertices_singles_length);
    }
    zox_set(e, Scale1D, { 0.125f })
    zox_set(e, Brightness, { 1.4f })
    float4 rotationer = quaternion_from_euler( (float3) { 0.1f * degreesToRadians, 0.2f * degreesToRadians, 0 });
    zox_prefab_set(e, EternalRotation, { rotationer })
    return e;
}

ecs_entity_t spawn_cube(ecs_world_t *world, const ecs_entity_t prefab, const float3 position) {
    zox_instance(prefab)
    // zox_name("cube")
    zox_set(e, Position3D, { position })
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, shader3D);
    return e;
}
