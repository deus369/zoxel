//! Bounds, because everyone needs limits! Used atm to keep player within the start area.
void Bounds2DSystem(ecs_iter_t *it) {
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    const Bounds2D *bounds2Ds = ecs_field(it, Bounds2D, 2);
    for (int i = 0; i < it->count; i++) {
        Position2D *position2D = &position2Ds[i];
        const Bounds2D *bounds2D = &bounds2Ds[i];
        if (position2D->value.x >= bounds2D->value.x) {
            position2D->value.x -= bounds2D->value.x * 2.0f;
        } else if (position2D->value.x <= -bounds2D->value.x) {
            position2D->value.x += bounds2D->value.x * 2.0f;
        }
        if (position2D->value.y >= bounds2D->value.y) {
            position2D->value.y -= bounds2D->value.y * 2.0f;
        } else if (position2D->value.y <= -bounds2D->value.y) {
            position2D->value.y += bounds2D->value.y * 2.0f;
        }
    }
}
zox_declare_system(Bounds2DSystem)