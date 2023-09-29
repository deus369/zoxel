// #define zox_debug_aoe_damage_system
#ifdef zox_debug_aoe_damage_system
    extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void AOEDamageSystem(ecs_iter_t *it) {
    // for any nearby entities with UserStatLinks:
    //      - add a damage debuff on them
    //      - remove when they leave the sphere of influence
    // for now, just damage directly
    // use StatValue to lower their health
    float damage_rate = 3.0f;
    float damage_radius = 6.0f;
    ecs_world_t *world = it->world;
    float delta_time = zox_delta_time;
    const Position3D *position3Ds = ecs_field(it, Position3D, 2);
    // zox_log("  aoe damaging system [%i]\n", it->count)
    for (int i = 0; i < it->count; i++) {
        ecs_entity_t e = it->entities[i];
        const Position3D *position3D = &position3Ds[i];
        ecs_iter_t it3 = ecs_query_iter(world, it->ctx);
        ecs_iter_t *it2 = &it3;
        while(ecs_query_next(it2)) {
            const Position3D *position3D2s = ecs_field(it2, Position3D, 1);
            const UserStatLinks *userStatLinkss = ecs_field(it2, UserStatLinks, 2);
            for (int j = 0; j < it2->count; j++) {
                ecs_entity_t e2 = it2->entities[j];
                if (e == e2) continue;
                const Position3D *position3D2 = &position3D2s[j];
                float distance = float3_distance(position3D->value, position3D2->value);
                if (distance > damage_radius) continue;
                const UserStatLinks *userStatLinks = &userStatLinkss[j];
                ecs_entity_t health_stat = userStatLinks->value[0];
                StatValue *statValue = ecs_get_mut(world, health_stat, StatValue);
                statValue->value -= delta_time * damage_rate;
                if (statValue->value < 0) statValue->value = 0;
                ecs_modified(world, health_stat, StatValue);
                #ifdef zox_debug_aoe_damage_system
                    spawn_line3D(world, position3D->value, position3D2->value, 0.5f, 0.1);
                #endif
            }
        }
    }
} zox_declare_system(AOEDamageSystem)