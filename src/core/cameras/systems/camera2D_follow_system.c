void Camera2DFollowSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(FreeRoam, freeRoams, 2)
    zox_field_in(CameraTarget, cameraTargets, 3)
    zox_field_out(Position3D, positions3D, 4)
    zox_field_out(Rotation3D, rotation3Ds, 5)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(FreeRoam, freeRoams, freeRoam)
        if (freeRoam->value == 0) {
            zox_field_i_in(CameraTarget, cameraTargets, cameraTarget)
            float3 target_position = { 0, 0, 0 };
            if (zox_has(cameraTarget->value, Position2D)) {
                const Position2D *playerPosition2D = zox_get(cameraTarget->value, Position2D)
                target_position.x = playerPosition2D->value.x;
                target_position.y = playerPosition2D->value.y;
            } else if (zox_has(cameraTarget->value, Position3D)) {
                const Position3D *playerPosition = zox_get(cameraTarget->value, Position3D)
                target_position.x = playerPosition->value.x;
                target_position.y = playerPosition->value.y;
            } else {
                continue;
            }
            zox_field_i_out(Position3D, positions3D, position3D)
            zox_field_i_out(Rotation3D, rotation3Ds, rotation3D)
            position3D->value.x = target_position.x;
            position3D->value.y = target_position.y;
            rotation3D->value = float4_identity;
        }
    }
} zox_declare_system(Camera2DFollowSystem)
