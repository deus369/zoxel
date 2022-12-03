// Camera2D prefab
ecs_entity_t camera2D_follower_prefab;

void spawn_camera2D_follower_prefab(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, base_camera_prefab);
    ecs_add_id(world, e, EcsPrefab);
    // ecs_set_name(world, e, "camera2D_prefab");
    set_unique_entity_name(world, e, "camera2D_follower_prefab");
    zoxel_add_tag(world, e, CameraFollower2D);
    zoxel_add(world, e, CameraTarget);
    ecs_defer_end(world);
    camera2D_follower_prefab = e;
    #ifdef zoxel_debug_prefabs
    zoxel_log_arg("spawn_prefab camera2D [%lu].\n", (long int) (e));
    #endif
}

ecs_entity_t spawn_camera2D_follower(ecs_world_t *world, float3 position, float4 rotation, int2 screenDimensions)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, camera2D_follower_prefab);
    ecs_set(world, e, Position, { position });
    ecs_set(world, e, Rotation, { rotation });
    ecs_set(world, e, ScreenDimensions, { screenDimensions });
    // zoxel_log_arg("Spawned Camera [%lu]\n", (long unsigned int) e);
    ecs_defer_end(world);
    return e;
}

ecs_entity_t spawn_ui_camera(ecs_world_t *world, int2 screenDimensions)
{
    ecs_defer_begin(world);
    float3 position = { 0, -0.0f, 1.0f };
    float4 rotation = quaternion_identity();
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, base_camera_prefab);
    set_unique_entity_name(world, e, "ui_camera");
    ecs_set(world, e, Position, { position });
    ecs_set(world, e, Rotation, { rotation });
    ecs_set(world, e, FieldOfView, { 53.2f });  // fudged this to get ui right... maybe not the best but it works xD
    ecs_set(world, e, ScreenDimensions, { screenDimensions });
    // zoxel_log_arg("Spawned Camera [%lu]\n", (long unsigned int) e);
    ecs_defer_end(world);
    ui_cameras[0] = e;
    return e;
}