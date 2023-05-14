/*float4 limit_rotation(float4 rotation, float2 euler_limit_x) {
    // Convert quaternion to axis-angle representation
    float angle = 2.0f * acos(rotation.w);
    float3 axis = { rotation.x, rotation.y, rotation.z };
    if (angle > M_PI) {
        // negate the quaternion to get equivalent rotation within 180 degrees
        angle = 2.0f * M_PI - angle;
        float3_multiply_float_p(&axis, -1);
    }
    // limit rotation angle
    float limit_angle = fabs(euler_limit_x.y - euler_limit_x.x) / 2.0f;
    if (angle > limit_angle) {
        // calculate new axis using cross product and limit angle
        float3 new_axis = float3_cross(axis, (float3) { 0, 1, 0 });
        new_axis = float3_multiply_float(float3_normalize(new_axis), sin(limit_angle));
        // calculate new w value using cos of limit angle
        float new_w = cos(limit_angle);
        // construct new quaternion
        rotation.x = new_axis.x;
        rotation.y = new_axis.y;
        rotation.z = new_axis.z;
        rotation.w = new_w;
    }
    return rotation;
}*/

void EulerLimitZSystem(ecs_iter_t *it) {
    const EulerLimitZ *eulerLimitZs = ecs_field(it, EulerLimitZ, 1);
    Euler *eulers = ecs_field(it, Euler, 2);
    // Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    for (int i = 0; i < it->count; i++) {
        const EulerLimitZ *eulerLimitZ = &eulerLimitZs[i];
        Euler *euler = &eulers[i];
        if (euler->value.z < eulerLimitZ->value.x) {
            euler->value.z = eulerLimitZ->value.x;
        }
        if (euler->value.z > eulerLimitZ->value.y) {
            euler->value.z = eulerLimitZ->value.y;
        }
        // Rotation3D *rotation = &rotations[i];
        // rotation->value = limit_rotation(rotation->value, (float2) { -0.6f, 0.6f });
        // zoxel_log("euler limitations! [%fx%fx%f] - [%f-%f]\n", euler->value.x, euler->value.y, euler->value.z, eulerLimitZ->value.x, eulerLimitZ->value.y);
    }
}
zox_declare_system(EulerLimitZSystem)

void EulerLimitXSystem(ecs_iter_t *it) {
    const EulerLimitX *eulerLimitXs = ecs_field(it, EulerLimitX, 1);
    Euler *eulers = ecs_field(it, Euler, 2);
    for (int i = 0; i < it->count; i++) {
        const EulerLimitX *eulerLimitX = &eulerLimitXs[i];
        Euler *euler = &eulers[i];
        if (euler->value.x < eulerLimitX->value.x) {
            euler->value.x = eulerLimitX->value.x;
        }
        if (euler->value.x > eulerLimitX->value.y) {
            euler->value.x = eulerLimitX->value.y;
        }
        // zoxel_log("euler limitations! [%fx%fx%f] - [%f-%f]\n", euler->value.x, euler->value.y, euler->value.z, eulerLimitZ->value.x, eulerLimitZ->value.y);
    }
}
zox_declare_system(EulerLimitXSystem)