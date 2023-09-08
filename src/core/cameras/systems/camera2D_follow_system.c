void CameraFollow2DSystem(ecs_iter_t *it) {
    const FreeRoam *freeRoams = ecs_field(it, FreeRoam, 2);
    const CameraTarget *cameraTargets = ecs_field(it, CameraTarget, 3);
    Position3D *positions = ecs_field(it, Position3D, 4);
    Rotation3D *rotations = ecs_field(it, Rotation3D, 5);
    for (int i = 0; i < it->count; i++) {
        const FreeRoam *freeRoam = &freeRoams[i];
        if (freeRoam->value == 0) {
            const CameraTarget *cameraTarget = &cameraTargets[i];
            float3 target_position = { 0, 0, 0 };
            if (ecs_has(it->world, cameraTarget->value, Position2D)) {
                const Position2D *playerPosition2D = ecs_get(it->world, cameraTarget->value, Position2D);
                target_position.x = playerPosition2D->value.x;
                target_position.y = playerPosition2D->value.y;
            } else if (ecs_has(it->world, cameraTarget->value, Position3D)) {
                const Position3D *playerPosition = ecs_get(it->world, cameraTarget->value, Position3D);
                target_position.x = playerPosition->value.x;
                target_position.y = playerPosition->value.y;
            } else {
                continue;
            }
            Position3D *position = &positions[i];
            position->value.x = target_position.x;
            position->value.y = target_position.y;
            Rotation3D *rosition = &rotations[i];
            rosition->value = float4_identity();
        }
    }
} zox_declare_system(CameraFollow2DSystem)

void CameraFollowSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const CameraFollowLink *cameraFollowLinks = ecs_field(it, CameraFollowLink, 1);
    const LocalPosition3D *localPosition3Ds = ecs_field(it, LocalPosition3D, 2);
    Position3D *positions = ecs_field(it, Position3D, 3);
    for (int i = 0; i < it->count; i++) {
        const CameraFollowLink *cameraFollowLink = &cameraFollowLinks[i];
        if (cameraFollowLink->value == 0) continue;
        float3 target_position = { 0, 0, 0 };
        if (ecs_has(world, cameraFollowLink->value, Position2D)) {
            const Position2D *target_position2D = ecs_get(world, cameraFollowLink->value, Position2D);
            target_position.x = target_position2D->value.x;
            target_position.y = target_position2D->value.y;
            target_position.z = 0;
        } else if (ecs_has(world, cameraFollowLink->value, Position3D)) {
            const Position3D *target_position3D = ecs_get(world, cameraFollowLink->value, Position3D);
            target_position = target_position3D->value;
        } else {
            continue;
        }
        const LocalPosition3D *localPosition3D = &localPosition3Ds[i];
        Position3D *position = &positions[i];
        position->value = target_position;
        float3_add_float3_p(&position->value, localPosition3D->value);
    }
} zox_declare_system(CameraFollowSystem)