void Velocity3DSystem(ecs_iter_t *it) { //! Veloco Rapters!
    #ifdef zoxel_disable_velocity
        return;
    #endif
    double delta_time = zox_delta_time;
    zox_field_out(Position3D, positions, 1)
    zox_field_in(Velocity3D, velocity3Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Velocity3D, velocity3Ds, velocity3D)
        zox_field_i_out(Position3D, positions, position3D)
        position3D->value.x += velocity3D->value.x * delta_time;
        position3D->value.y += velocity3D->value.y * delta_time;
        position3D->value.z += velocity3D->value.z * delta_time;
    }
} zox_declare_system(Velocity3DSystem)
