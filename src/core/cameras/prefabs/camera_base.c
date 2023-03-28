ecs_entity_t base_camera_prefab;

ecs_entity_t spawn_camera_base_prefab(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "base_camera_prefab");
    zoxel_add_tag(world, e, Camera);
    zoxel_add(world, e, Position3D);
    zoxel_add(world, e, Rotation3D);
    zoxel_set(world, e, Euler, { { 0, 0, 0 } });
    zoxel_set(world, e, ProjectionMatrix, { float4x4_identity() });
    zoxel_set(world, e, ViewMatrix, { float4x4_identity() });
    zoxel_set(world, e, ScreenDimensions, { { 0, 0 } });
    zoxel_set(world, e, ScreenPosition, { { 0, 0 } });
    zoxel_set(world, e, FieldOfView, { 60 });
    zoxel_set(world, e, CameraNearDistance, { 0.01f });
    ecs_defer_end(world);
    base_camera_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab camera_base [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_base_camera(ecs_world_t *world, float3 position, float4 rotation, int2 screen_dimensions, int2 screen_position) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, base_camera_prefab);
    set_unique_entity_name(world, e, "base_camera");
    ecs_set(world, e, Position3D, { position });
    ecs_set(world, e, Rotation3D, { rotation });
    ecs_set(world, e, ScreenDimensions, { screen_dimensions });
    ecs_set(world, e, ScreenPosition, { screen_position });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned base camera [%lu]\n", (long int) e);
    #endif
    return e;
}

ecs_entity_t spawn_free_camera(ecs_world_t *world, float3 position, float4 rotation,
    int2 screen_dimensions, int2 screen_position) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, base_camera_prefab);
    set_unique_entity_name(world, e, "free_camera");
    ecs_set(world, e, Position3D, { position });
    ecs_set(world, e, Rotation3D, { rotation });
    ecs_set(world, e, Euler, { quaternion_to_euler(rotation) });
    ecs_set(world, e, ScreenDimensions, { screen_dimensions });
    ecs_set(world, e, ScreenPosition, { screen_position });
    zoxel_add_tag(world, e, EulerOverride);
    zoxel_set(world, e, FreeRoam, { 0 });
    // adds a limit, - half pi to + half pi, 0.8 is around half that
    zoxel_set(world, e, EulerLimitZ, { { -0.8f, 0.8f } });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned Free Camera [%lu]\n", (long int) e);
    #endif
    return e;
}