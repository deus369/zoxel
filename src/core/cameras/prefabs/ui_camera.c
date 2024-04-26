const float ui_camera_fov = 53.22f;  // fudged this to get ui right... works for now

ecs_entity_t spawn_ui_camera(ecs_world_t *world, const int2 position, const int2 dimensions) {
    const float3 position3D = { 0, 0, 1.0f };
    zox_instance(prefab_base_camera)
    zox_name("ui_camera")
    zox_add_tag(e, UICamera)
    zox_add_tag(e, Camera2D)
    zox_set(e, Position3D, { position3D })
    zox_set(e, Rotation3D, { quaternion_identity })
    zox_set(e, FieldOfView, { ui_camera_fov })
    zox_set(e, ScreenPosition, { position })
    zox_set(e, ScreenDimensions, { dimensions })
    return e;
}
