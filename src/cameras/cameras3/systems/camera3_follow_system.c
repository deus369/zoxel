void Camera3FollowSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(CameraFollowLink)
    zox_sys_in(LocalPosition3D)
    zox_sys_out(Position3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(CameraFollowLink, cameraFollowLink)
        zox_sys_i(LocalPosition3D, localPosition3D)
        zox_sys_o(Position3D, position)
        if (!cameraFollowLink->value) {
            continue;
        }
        if (zox_has(cameraFollowLink->value, Position2D)) {
            zox_geter_value(cameraFollowLink->value, Position2D, float2, target_position)
            position->value.x = target_position.x;
            position->value.y = target_position.y;
            position->value.z = 0;
        } else if (zox_has(cameraFollowLink->value, Position3D)) {
            zox_geter_value(cameraFollowLink->value, Position3D, float3, target_position)
            position->value = target_position;
        } else {
            continue;
        }
        float3_add_float3_p(&position->value, localPosition3D->value);
    }
} zox_declare_system(Camera3FollowSystem)