void Camera3DFollowSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const CameraFollowLink *cameraFollowLinks = ecs_field(it, CameraFollowLink, 1);
    const LocalPosition3D *localPosition3Ds = ecs_field(it, LocalPosition3D, 2);
    Position3D *positions = ecs_field(it, Position3D, 3);
    for (int i = 0; i < it->count; i++) {
        const CameraFollowLink *cameraFollowLink = &cameraFollowLinks[i];
        if (cameraFollowLink->value == 0) continue;
        float3 target_position = { 0, 0, 0 };
        if (zox_has(cameraFollowLink->value, Position2D)) {
            const Position2D *target_position2D = ecs_get(world, cameraFollowLink->value, Position2D);
            target_position.x = target_position2D->value.x;
            target_position.y = target_position2D->value.y;
            target_position.z = 0;
        } else if (zox_has(cameraFollowLink->value, Position3D)) {
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
} zox_declare_system(Camera3DFollowSystem)
