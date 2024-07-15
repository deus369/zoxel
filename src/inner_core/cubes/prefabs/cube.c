ecs_entity_t spawn_prefab_cube(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_cube")
    add_transform3Ds(world, e, 1);
    zox_prefab_set(e, Brightness, { 1.4f })
    zox_prefab_set(e, MeshDirty, { 1 })
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, Scale1D, { 0.125f })
    if (!headless) {
        zox_prefab_add(e, MeshIndicies)
        zox_prefab_add(e, MeshVertices)
        add_gpu_mesh(world, e);
        add_gpu_material(world, e);
        prefab_set_mesh_indicies(world, e, cube_indicies, cube_indicies_length);
        // prefab_set_mesh_vertices_float3(world, e, cube_vertices, cube_vertices_length);
        prefab_set_mesh_vertices_float(world, e, cube_vertices_singles, cube_vertices_singles_length);
    }
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
