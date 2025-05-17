//! Bounds, because everyone needs limits! Used atm to keep player within the start area.
void Position3DBoundsSystem(ecs_iter_t *it) {
    const float teleport_force = 0.2f;
    zox_field_in(Position3DBounds, position3DBoundss, 1)
    zox_field_in(Bounds3D, bounds3Ds, 2)
    zox_field_out(Position3D, position3Ds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position3DBounds, position3DBoundss, position3DBounds)
        const float6 bounds = position3DBounds->value;
        if (bounds.x == 0 && bounds.y == 0 && bounds.z == 0 && bounds.w == 0 && bounds.u == 0 && bounds.v == 0) {
            continue; // disabled
        }
        zox_field_i(Bounds3D, bounds3Ds, bounds3D)
        zox_field_o(Position3D, position3Ds, position3D)
        if (position3D->value.x - bounds3D->value.x < bounds.x) position3D->value.x = bounds.x + teleport_force;
        else if (position3D->value.x + bounds3D->value.x > bounds.y) position3D->value.x = bounds.y - teleport_force;
        if (position3D->value.y - bounds3D->value.y < bounds.z) position3D->value.y = bounds.z + teleport_force;
        else if (position3D->value.y + bounds3D->value.y > bounds.w) position3D->value.y = bounds.w - teleport_force;
        if (position3D->value.z - bounds3D->value.z < bounds.u) position3D->value.z = bounds.u + teleport_force;
        else if (position3D->value.z + bounds3D->value.z > bounds.v) position3D->value.z = bounds.v - teleport_force;
    }
} zox_declare_system(Position3DBoundsSystem)
