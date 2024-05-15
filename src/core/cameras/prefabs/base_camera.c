ecs_entity_t prefab_base_camera;

ecs_entity_t spawn_camera_base_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_base_camera")
    zox_add_tag(e, Camera)
    zox_add_tag(e, CameraTransform)
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, ParentLink, { 0 })
    zox_prefab_set(e, LocalPosition3D, { float3_zero })
    zox_prefab_set(e, LocalRotation3D, { quaternion_identity })
    zox_prefab_set(e, Euler, { (float3) { 0, 180 * degreesToRadians, 0 } })
    zox_prefab_set(e, ProjectionMatrix, { float4x4_identity() })
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_prefab_set(e, ViewMatrix, { float4x4_identity() })
    zox_prefab_set(e, ScreenPosition, { int2_zero })
    zox_prefab_set(e, ScreenDimensions, { int2_zero })
    zox_prefab_set(e, FieldOfView, { camera_fov })
    zox_prefab_set(e, CameraNearDistance, { 0.01f })
    zox_prefab_set(e, CanFreeRoam, { 0 })
    zox_prefab_set(e, FreeRoam, { 0 }) // newer
    zox_prefab_set(e, CameraMode, { 0 })
    zox_prefab_set(e, ScreenToCanvas, { float4_zero })
    zox_prefab_set(e, CameraPlanes, { 0, NULL })
    prefab_base_camera = e;
    return e;
}

ecs_entity_t spawn_base_camera(ecs_world_t *world, const float3 position, const float4 rotation, const float camera_fov, const int2 screen_position, const int2 screen_dimensions, const float4 screen_to_canvas) {
    zox_instance(prefab_base_camera)
    zox_name("base_camera")
    zox_set(e, Position3D, { position })
    zox_set(e, Rotation3D, { rotation })
    zox_set(e, ScreenDimensions, { screen_dimensions })
    zox_set(e, ScreenPosition, { screen_position })
    zox_set(e, CameraMode, { camera_mode })
    zox_set(e, FieldOfView, { camera_fov })
    zox_set(e, ScreenToCanvas, { screen_to_canvas })
    return e;
}
