ecs_entity_t element_prefab;

void spawn_element_prefab(ecs_world_t *world)
{
    element_prefab = ecs_new_prefab(world, "ui_element_prefab");
    // printf("Spawned test_custom_mesh [%lu].\n", (long int) (e));
    #ifdef zoxel_transforms2D
    add_transform2Ds(world, custom_mesh_prefab);
    #endif
    // add_seed(world, custom_mesh_prefab, 444);
    /*zoxel_set_component(world, custom_mesh_prefab, EntityDirty, { 1 });
    zoxel_add_component(world, custom_mesh_prefab, MeshIndicies);
    zoxel_add_component(world, custom_mesh_prefab, MeshVertices);
    add_gpu_mesh(world, custom_mesh_prefab);
    add_gpu_material(world, custom_mesh_prefab);
    float4 rotationer = quaternion_from_euler( (float3) { 0.1f * degreesToRadians, 0.2f * degreesToRadians, 0 });
    zoxel_set_component(world, custom_mesh_prefab, EternalRotation, { rotationer });
    zoxel_add_component(world, custom_mesh_prefab, Brightness);*/
    // spawn prefab
}

ecs_entity_t spawn_element(ecs_world_t *world, ecs_entity_t prefab, float3 position)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, element_prefab);
    ecs_set(world, e, Position, { position }); // {{ 0, 0.6f, 0 }});
    ecs_set(world, e, Rotation, {{ 0, 0, 0, 1.0f }});
    ecs_set(world, e, Scale1D, { 0.05f });
    /*ecs_set(world, e, Brightness, { 1.4f });
    // printf("Spawned Character2D [%lu]\n", (long unsigned int) e);
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, instanceShader3D);
    set_mesh_indicies_world(world, e, cubeIndicies, 36);
    set_mesh_vertices_world(world, e, cubeVertices, 24);*/
    return e;
}