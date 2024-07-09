//! Bounds, because everyone needs limits! Used atm to keep player within the start area.
void Position3DBoundsSystem(ecs_iter_t *it) {
    const float teleport_force = 0.2f;
    zox_field_in(Position3DBounds, position3DBoundss, 1)
    zox_field_in(Bounds3D, bounds3Ds, 2)
    zox_field_out(Position3D, position3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position3DBounds, position3DBoundss, bounds)
        zox_field_i(Bounds3D, bounds3Ds, bounds3D)
        zox_field_o(Position3D, position3Ds, position3D)
        if (position3D->value.x - bounds3D->value.x < bounds->value.x) position3D->value.x = bounds->value.x + teleport_force;
        else if (position3D->value.x + bounds3D->value.x > bounds->value.y) position3D->value.x = bounds->value.y - teleport_force;
        if (position3D->value.y - bounds3D->value.y < bounds->value.z) position3D->value.y = bounds->value.z + teleport_force;
        else if (position3D->value.y + bounds3D->value.y > bounds->value.w) position3D->value.y = bounds->value.w - teleport_force;
        if (position3D->value.z - bounds3D->value.z < bounds->value.u) position3D->value.z = bounds->value.u + teleport_force;
        else if (position3D->value.z + bounds3D->value.z > bounds->value.v) position3D->value.z = bounds->value.v - teleport_force;
    }
} zox_declare_system(Position3DBoundsSystem)
