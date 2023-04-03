/*void add_ui_mesh_components(ecs_world_t *world, ecs_entity_t e) {
    zoxel_set(world, e, Brightness, { 1 });
    add_gpu_mesh(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    //! \todo Fix: Causes a Flecs memory leak?!?! Temporarily commented out.
    zoxel_add(world, e, MeshVertices2D);
    zoxel_add(world, e, MeshIndicies);
    zoxel_add(world, e, MeshUVs);
    // Why can't i just set in prefab and reuse same memory array? write a test for this
    // set_mesh_uvs(world, e, square_vertices, 4);
    MeshUVs meshUVs = { };
    initialize_memory_component_non_pointer(meshUVs, float2, 4);
    memcpy(meshUVs.value, square_vertices, 4 * 8);
    ecs_set(world, e, MeshUVs, { meshUVs.length, meshUVs.value });
}*/