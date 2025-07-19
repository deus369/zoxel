const float ui_camera_fov = 53.22f;  // fudged this to get ui right... works for now

ecs_entity_t spawn_prefab_camera_ui(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("ui_camera")
    zox_add_tag(e, CameraUI)
    zox_add_tag(e, Camera2D)
    zox_set(e, FieldOfView, { ui_camera_fov })
    zox_set(e, CameraNearDistance, { 0.01f })
    const float3 position3D = { 0, 0, 1.0f };
    zox_set(e, Position3D, { position3D })
    zox_set(e, Rotation3D, { quaternion_identity })
    return e;
}


ecs_entity_t spawn_camera_ui(ecs_world_t *world,
    const ecs_entity_t prefab,
    const int2 position,
    const int2 dimensions,
    const float4 screen_to_canvas)
{
    zox_instance(prefab)
    zox_name("ui_camera")
    zox_set(e, ScreenPosition, { position })
    zox_set(e, ScreenDimensions, { dimensions })
    zox_set(e, ScreenToCanvas, { screen_to_canvas })
    return e;
}
