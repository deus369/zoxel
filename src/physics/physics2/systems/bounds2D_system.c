//! Bounds, because everyone needs limits! Used atm to keep player within the start area.
void Bounds2DSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(Bounds2D)
    zox_sys_out(Position2D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Bounds2D, bounds2D)
        zox_sys_o(Position2D, position2D)
        if (position2D->value.x > bounds2D->value.x) position2D->value.x = bounds2D->value.x;
        else if (position2D->value.x < -bounds2D->value.x) position2D->value.x = -bounds2D->value.x;
        if (position2D->value.y > bounds2D->value.y) position2D->value.y = bounds2D->value.y;
        else if (position2D->value.y < -bounds2D->value.y) position2D->value.y = -bounds2D->value.y;
    }
} zox_declare_system(Bounds2DSystem)
