void Camera3DFollowSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(CameraFollowLink, cameraFollowLinks, 1)
    zox_field_in(LocalPosition3D, localPosition3Ds, 2)
    zox_field_out(Position3D, positions, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CameraFollowLink, cameraFollowLinks, cameraFollowLink)
        if (cameraFollowLink->value == 0) continue;
        float3 target_position = { 0, 0, 0 };
        if (zox_has(cameraFollowLink->value, Position2D)) {
            const Position2D *target_position2D = zox_get(cameraFollowLink->value, Position2D)
            target_position.x = target_position2D->value.x;
            target_position.y = target_position2D->value.y;
            target_position.z = 0;
        } else if (zox_has(cameraFollowLink->value, Position3D)) {
            const Position3D *target_position3D = zox_get(cameraFollowLink->value, Position3D)
            target_position = target_position3D->value;
        } else {
            continue;
        }
        zox_field_i(LocalPosition3D, localPosition3Ds, localPosition3D)
        zox_field_o(Position3D, positions, position)
        position->value = target_position;
        float3_add_float3_p(&position->value, localPosition3D->value);
    }
} zox_declare_system(Camera3DFollowSystem)
