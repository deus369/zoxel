// #define zoxel_debug_omega3D_system

void Omega3DSystem(ecs_iter_t *it) {
    double delta_time = zox_delta_time;
    const Omega3D *omega3Ds = ecs_field(it, Omega3D, 1);
    Rotation3D *rotation3Ds = ecs_field(it, Rotation3D, 2);
    for (int i = 0; i < it->count; i++) {
        const Omega3D *omega3D = &omega3Ds[i];
        if (omega3D->value.x == 0 && omega3D->value.y == 0 && omega3D->value.z == 0 && omega3D->value.w == 1) {
            continue;
        }
        // check if it's magnitude is close to a cutoff point and then set to identity too
        Rotation3D *rotation3D = &rotation3Ds[i];
        #ifdef zoxel_debug_omega3D_system
            zoxel_log(" > omega3D [%fx%fx%fx%f]\n", omega3D->value.x, omega3D->value.y, omega3D->value.z, omega3D->value.w);
            zoxel_log("     + pre rotation [%fx%fx%fx%f]\n", rotation3D->value.x, rotation3D->value.y, rotation3D->value.z, rotation3D->value.w);
        #endif
        float magnitude = quaternion_magnitude(omega3D->value);
        if (magnitude == 0.0f) continue;
        float4 delta_rotation = get_delta_rotation(omega3D->value, magnitude, delta_time);
        quaternion_rotate_quaternion_p(&rotation3D->value, delta_rotation);
        #ifdef zoxel_debug_omega3D_system
            zoxel_log("     + post rotation [%fx%fx%fx%f]\n", rotation3D->value.x, rotation3D->value.y, rotation3D->value.z, rotation3D->value.w);
        #endif
    }
}
zox_declare_system(Omega3DSystem)

// float4 rotation_delta = omega3D->value;
// float4_multiply_float_p(&rotation_delta, delta_time);
// quaternion_rotate_quaternion_p(&rotation3D->value, rotation_delta);

// Multiply the current rotation by the delta rotation to update the rotation
/*float4 new_rotation = {
    delta_rotation.w * rotation3D->value.x + delta_rotation.x * rotation3D->value.w - delta_rotation.y * rotation3D->value.z + delta_rotation.z * rotation3D->value.y,
    delta_rotation.w * rotation3D->value.y + delta_rotation.x * rotation3D->value.z + delta_rotation.y * rotation3D->value.w - delta_rotation.z * rotation3D->value.x,
    delta_rotation.w * rotation3D->value.z - delta_rotation.x * rotation3D->value.y + delta_rotation.y * rotation3D->value.x + delta_rotation.z * rotation3D->value.w,
    delta_rotation.w * rotation3D->value.w - delta_rotation.x * rotation3D->value.x - delta_rotation.y * rotation3D->value.y - delta_rotation.z * rotation3D->value.z
};
rotation3D->value = new_rotation;*/