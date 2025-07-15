void Gravity3DSystem(ecs_iter_t *it) {
    zox_field_in(Gravity3D, gravity3Ds, 1)
    // zox_field_in(Grounded, groundeds, 2)
    zox_field_out(Acceleration3D, acceleration3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Gravity3D, gravity3Ds, gravity3D)
        // zox_field_i(Grounded, groundeds, grounded)
        zox_field_o(Acceleration3D, acceleration3Ds, acceleration3D)
        float3_add_float3_p(&acceleration3D->value, gravity3D->value);
        // if (!grounded->value) float3_add_float3_p(&acceleration3D->value, gravity3D->value);
        // else float3_add_float3_p(&acceleration3D->value, float3_multiply_float(gravity3D->value, 0.2f));
    }
} zox_declare_system(Gravity3DSystem)
