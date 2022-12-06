//! Uses base camera as prefab for now
ecs_entity_t spawn_ui_camera(ecs_world_t *world, int2 screenDimensions)
{
    float3 position = { 0, -0.0f, 1.0f };
    float4 rotation = quaternion_identity();
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, base_camera_prefab);
    set_unique_entity_name(world, e, "ui_camera");
    zoxel_add_tag(world, e, UICamera);
    ecs_set(world, e, Position, { position });
    ecs_set(world, e, Rotation, { rotation });
    ecs_set(world, e, FieldOfView, { 53.2f });  // fudged this to get ui right... maybe not the best but it works xD
    ecs_set(world, e, ScreenDimensions, { screenDimensions });
    // zoxel_log_arg("Spawned Camera [%lu]\n", (long unsigned int) e);
    ecs_defer_end(world);
    ui_cameras[0] = e;
    return e;
}