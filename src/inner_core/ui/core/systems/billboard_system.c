
float4 float3ToQuaternion(float3 normal) {
    float3 axis;
    float4 quaternion;

    // Step 1: Normalize the normal vector
    float length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
    normal.x /= length;
    normal.y /= length;
    normal.z /= length;

    // Step 2: Calculate the angle of rotation
    float angle = acos(normal.z); // dot(normal, (0, 0, 1)) = normal.z

    // Step 3: Calculate the axis of rotation
    axis.x = -normal.y;
    axis.y = normal.x;
    axis.z = 0;

    // Step 4: Create the quaternion
    quaternion.x = axis.x * sin(angle / 2);
    quaternion.y = axis.y * sin(angle / 2);
    quaternion.z = axis.z * sin(angle / 2);
    quaternion.w = cos(angle / 2);

    return quaternion;
}

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
        // float3 delta = float3_subtract_float3(target_position->value, position3D->value);
        float3 normal = float3_normalize(normal); // normalize
        // rotation3D->value = quaternion_from_float3(normal); // turn to quaternion
        // rotation3D->value = float3ToQuaternion(normal);
    }
} zox_declare_system(BillboardSystem)