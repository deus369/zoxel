float4 calculate_dissipation(const float4 omega3D) {
    float mag = sqrt(omega3D.x * omega3D.x + omega3D.y * omega3D.y + omega3D.z * omega3D.z + omega3D.w * omega3D.w);
    if (mag < dissipation_threshold) return quaternion_identity;
    float factor = (-rotation_friction * mag) / (mag * mag + 1e-6);
    float3 euler = quaternion_to_euler(omega3D);
    float3_multiply_float_p(&euler, factor);
    return quaternion_from_euler(euler);
}

void Dissipation3DSystem(ecs_iter_t *it) {
    zox_field_in(Omega3D, omega3Ds, 2)
    zox_field_out(Alpha3D, alpha3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Omega3D, omega3Ds, omega3D)
        if (omega3D->value.x == 0 && omega3D->value.y == 0 && omega3D->value.z == 0 && omega3D->value.w == 1) continue;
        zox_field_i_out(Alpha3D, alpha3Ds, alpha3D)
        quaternion_rotate_quaternion_p(&alpha3D->value, calculate_dissipation(omega3D->value));
    }
} zox_declare_system(Dissipation3DSystem)
