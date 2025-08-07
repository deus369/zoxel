void Gravity3DSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(Gravity3D)
    zox_sys_in(DisableGravity)
    zox_sys_out(Acceleration3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Gravity3D, gravity3D)
        zox_sys_i(DisableGravity, disableGravity)
        zox_sys_o(Acceleration3D, acceleration3D)
        if (!disableGravity->value) {
            float3_add_float3_p(&acceleration3D->value, gravity3D->value);
        }
    }
} zox_declare_system(Gravity3DSystem)
