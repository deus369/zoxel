void Camera2DFollowSystem(ecs_iter_t *it) {
    zox_iter_world()
    const FreeRoam *freeRoams = ecs_field(it, FreeRoam, 2);
    const CameraTarget *cameraTargets = ecs_field(it, CameraTarget, 3);
    Position3D *positions = ecs_field(it, Position3D, 4);
    Rotation3D *rotations = ecs_field(it, Rotation3D, 5);
    for (int i = 0; i < it->count; i++) {
        const FreeRoam *freeRoam = &freeRoams[i];
        if (freeRoam->value == 0) {
            const CameraTarget *cameraTarget = &cameraTargets[i];
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
            Position3D *position = &positions[i];
            position->value.x = target_position.x;
            position->value.y = target_position.y;
            Rotation3D *rosition = &rotations[i];
            rosition->value = float4_identity;
        }
    }
} zox_declare_system(Camera2DFollowSystem)
