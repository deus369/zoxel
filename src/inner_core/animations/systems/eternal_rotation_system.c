void EternalRotationSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    Rotation3D *rotations = ecs_field(it, Rotation3D, 1);
    const EternalRotation *eternalRotations = ecs_field(it, EternalRotation, 2);
    for (int i = 0; i < it->count; i++) {
        const EternalRotation *eternalRotation = &eternalRotations[i];
        Rotation3D *rotation3D = &rotations[i];
        float3 euler = quaternion_to_euler(eternalRotation->value);
        float3_multiply_float_p(&euler, delta_time);
        float4 rotate_speed = quaternion_from_euler(euler);
        rotation3D->value = quaternion_rotate(rotate_speed, rotation3D->value);
    }
}
zoxel_declare_system(EternalRotationSystem)

// #define main_camera_rotation_speed 60 * 0.14f
// float4 rotate_speed = eternalRotation->value; // float4_multiply_float2(eternalRotation->value, delta_time);
// printf("Rotation3D: %f %f %f %f\n", rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);
// float3 euler = quaternion_to_euler(rotation->value);
// zoxel_log(" + rotating [%fx%fx%f]\n", euler.x, euler.y, euler.z);
/*#ifdef zoxel_debug_eternal_rotation
    print_quadrant(rotation3D->value);
    test_quaternion_math(rotation3D->value);
#endif*/