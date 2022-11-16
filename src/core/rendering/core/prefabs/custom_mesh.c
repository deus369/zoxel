ecs_entity_t custom_mesh_prefab;

void spawn_custom_mesh_prefab(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "test_custom_mesh");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab custom_mesh [%lu].\n", (long int) (e));
    #endif
    // printf("Spawned test_custom_mesh [%lu].\n", (long int) (e));
    zoxel_set(world, e, EntityDirty, { 1 });
    #ifdef zoxel_transforms3D
    add_transform3Ds(world, e);
    #endif
    zoxel_add(world, e, MeshIndicies);
    zoxel_add(world, e, MeshVertices);
    add_gpu_mesh(world, e);
    add_gpu_material(world, e);
    zoxel_add(world, e, Brightness);
    custom_mesh_prefab = e;
    ecs_defer_end(world);
}

void spawn_custom_mesh(ecs_world_t *world, ecs_entity_t prefab, float3 position)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, custom_mesh_prefab);
    ecs_set(world, e, Position, { position }); // {{ 0, 0.6f, 0 }});
    ecs_set(world, e, Rotation, {{ 0, 0, 0, 1.0f }});
    ecs_set(world, e, Scale1D, { 0.05f });
    ecs_set(world, e, Brightness, { 1.4f });
    float4 rotationer = quaternion_from_euler( (float3) { 0.1f * degreesToRadians, 0.2f * degreesToRadians, 0 });
    zoxel_set(world, e, EternalRotation, { rotationer });
    // printf("Spawned Character2D [%lu]\n", (long unsigned int) e);
    spawn_gpu_mesh(world, e);
    spawn_gpu_material(world, e, instanceShader3D);
    set_mesh_indicies_world(world, e, cubeIndicies, 36);
    set_mesh_vertices_world(world, e, cubeVertices, 24);
    ecs_defer_end(world);
}