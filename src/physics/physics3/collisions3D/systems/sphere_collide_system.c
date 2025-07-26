void SphereCollideSystem(ecs_iter_t *it) {
    zox_sys_query()
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_in(SphereRadius)
    zox_sys_in(CollisionDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(Position3D, position3D)
        zox_sys_i(SphereRadius, sphereRadius)
        zox_sys_i(CollisionDisabled, collisionDisabled)
        if (collisionDisabled->value) {
            continue;
        }
        zox_sys_query_begin()
        while (zox_sys_query_loop()) {
            zox_sys_begin_2()
            zox_sys_in_2(Position3D)
            zox_sys_in_2(SphereRadius)
            zox_sys_in_2(CollisionDisabled)
            /*const Position3D *position3Ds2 = ecs_sys(&it2, Position3D, 1);
            const SphereRadius *sphereRadiuss2 = ecs_sys(&it2, SphereRadius, 2);
            const CollisionDisabled *collisionDisableds2 = ecs_sys(&it2, CollisionDisabled, 3);*/
            for (int j = 0; j < it2.count; j++) {
                zox_sys_i_2(Position3D, position3D2)
                zox_sys_i_2(SphereRadius, sphereRadius2)
                zox_sys_i_2(CollisionDisabled, collisionDisabled2)
                // const CollisionDisabled *collisionDisabled2 = &collisionDisableds2[j];
                if (collisionDisabled2->value) {
                    continue;
                }
                const ecs_entity_t e2 = it2.entities[j];
                if (e == e2) {
                    continue;
                }
                //const Position3D *position3D2 = &position3Ds2[j];
                //const SphereRadius *sphereRadius2 = &sphereRadiuss2[j];
                const float distance = float3_distance(position3D->value, position3D2->value);
                const byte overlaps = (distance <= sphereRadius->value + sphereRadius2->value);
                if (overlaps) {
                    if (zox_has(e, OverlapEvent)) {
                        zox_geter(e, OverlapEvent, overlapEvent)
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
