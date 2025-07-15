void SphereCollideSystem(ecs_iter_t *it) {
    zox_sys_query()
    zox_field_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(SphereRadius, sphereRadiuss, 2)
    zox_field_in(CollisionDisabled, collisionDisableds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(CollisionDisabled, collisionDisableds, collisionDisabled)
        if (collisionDisabled->value) {
            continue;
        }
        zox_field_e()
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(SphereRadius, sphereRadiuss, sphereRadius)
        zox_sys_query_begin()
        while (zox_sys_query_loop()) {
            const Position3D *position3Ds2 = ecs_field(&it2, Position3D, 1);
            const SphereRadius *sphereRadiuss2 = ecs_field(&it2, SphereRadius, 2);
            const CollisionDisabled *collisionDisableds2 = ecs_field(&it2, CollisionDisabled, 3);
            for (int j = 0; j < it2.count; j++) {
                const CollisionDisabled *collisionDisabled2 = &collisionDisableds2[j];
                if (collisionDisabled2->value) {
                    continue;
                }
                const ecs_entity_t e2 = it2.entities[j];
                if (e == e2) {
                    continue;
                }
                const Position3D *position3D2 = &position3Ds2[j];
                const SphereRadius *sphereRadius2 = &sphereRadiuss2[j];
                const float distance = float3_distance(position3D->value, position3D2->value);
                const byte overlaps = (distance <= sphereRadius->value + sphereRadius2->value);
                if (overlaps) {
                    if (zox_has(e, OverlapEvent)) {
                        const OverlapEvent *overlapEvent = zox_get(e, OverlapEvent)
                        if (overlapEvent->value) (*overlapEvent->value)(world, e, e2);
                    }
                    // zox_log(" > e [%lu] overlapping e2 [%lu]\n", e, e2)
                    // detects when one object overlaps another
                    // we should do overlap event here
                    // that would involve caching overlapped entities tho
                }
            }
        }
        zox_sys_query_end()
    }
} zox_declare_system(SphereCollideSystem)
