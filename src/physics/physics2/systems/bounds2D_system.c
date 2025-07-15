//! Bounds, because everyone needs limits! Used atm to keep player within the start area.
void Bounds2DSystem(ecs_iter_t *it) {
    zox_field_in(Bounds2D, bounds2Ds, 2)
    zox_field_out(Position2D, position2Ds, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Bounds2D, bounds2Ds, bounds2D)
        zox_field_o(Position2D, position2Ds, position2D)
        if (position2D->value.x > bounds2D->value.x) position2D->value.x = bounds2D->value.x;
        else if (position2D->value.x < -bounds2D->value.x) position2D->value.x = -bounds2D->value.x;
        if (position2D->value.y > bounds2D->value.y) position2D->value.y = bounds2D->value.y;
        else if (position2D->value.y < -bounds2D->value.y) position2D->value.y = -bounds2D->value.y;
    }
} zox_declare_system(Bounds2DSystem)
