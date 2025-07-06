void Jump3DSystem(ecs_iter_t *it) {
    init_delta_time()
    zox_field_world()
    zox_field_in(DisableMovement, disableMovements, 1)
    zox_field_out(Jump, jumps, 2)
    zox_field_out(Acceleration3D, acceleration3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DisableMovement, disableMovements, disableMovement)
        if (disableMovement->value) continue;
        zox_field_o(Jump, jumps, jump)
        if (!jump->value) continue;
        zox_field_o(Acceleration3D, acceleration3Ds, acceleration3D)
        const float3 velocity3D = zox_get_value(it->entities[i], Velocity3D)
        float potential_velocity = velocity3D.y + (acceleration3D->value.y + physics3D_jump) * delta_time;
        if (potential_velocity < max_jump_velocity) acceleration3D->value.y += physics3D_jump;
        jump->value -= delta_time;
        if (jump->value < 0) jump->value = 0;
    } 
} zox_declare_system(Jump3DSystem)