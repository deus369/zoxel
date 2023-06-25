void BillboardSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    const CameraLink *cameraLinks = ecs_field(it, CameraLink, 2);
    const Position3D *position3Ds = ecs_field(it, Position3D, 3);
    Rotation3D *rotation3Ds = ecs_field(it, Rotation3D, 4);
    for (int i = 0; i < it->count; i++) {
        const CameraLink *cameraLink = &cameraLinks[i];
        if (cameraLink->value == 0) continue;
        const Position3D *position3D = &position3Ds[i];
        Rotation3D *rotation3D = &rotation3Ds[i];
        const Position3D *target_position = ecs_get(world, cameraLink->value, Position3D);
        float3 delta = float3_subtract_float3(position3D->value, target_position->value);
        float3 normal = float3_normalize(normal); // normalize
        // rotation3D->value = quaternion_from_float3(normal); // turn to quaternion
    }
} zox_declare_system(BillboardSystem)