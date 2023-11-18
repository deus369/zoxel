void Gravity3DSystem(ecs_iter_t *it) {
    zox_field_in(Gravity3D, gravity3Ds, 1)
    zox_field_out(Acceleration3D, acceleration3Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Gravity3D, gravity3Ds, gravity3D)
        zox_field_i_out(Acceleration3D, acceleration3Ds, acceleration3D)
        acceleration3D->value.x += gravity3D->value.x;
        acceleration3D->value.y += gravity3D->value.y;
        acceleration3D->value.z += gravity3D->value.z;
    }
} zox_declare_system(Gravity3DSystem)
