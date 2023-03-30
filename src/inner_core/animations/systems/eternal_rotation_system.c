void EternalRotationSystem(ecs_iter_t *it) {
    Rotation3D *rotations = ecs_field(it, Rotation3D, 1);
    const EternalRotation *eternalRotations = ecs_field(it, EternalRotation, 2);
    for (int i = 0; i < it->count; i++) {
        const EternalRotation *eternalRotation = &eternalRotations[i];
        Rotation3D *rotation3D = &rotations[i];
        rotation3D->value = quaternion_rotate(eternalRotation->value, rotation3D->value);
        // printf("Rotation3D: %f %f %f %f\n", rotation->value.x, rotation->value.y, rotation->value.z, rotation->value.w);
        // float3 euler = quaternion_to_euler(rotation->value);
        // zoxel_log(" + rotating [%fx%fx%f]\n", euler.x, euler.y, euler.z);
        #ifdef zoxel_debug_eternal_rotation
            print_quadrant(rotation3D->value);
            test_quaternion_math(rotation3D->value);
        #endif
    }
}
zoxel_declare_system(EternalRotationSystem)