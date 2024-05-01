// #define zox_debug_aoe_damage_system
#ifdef zox_debug_aoe_damage_system
extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif
// todo: Seperate area from damage, so the skill is a child of character, and it finds characters in area and applies damage at end step
// todo: seperate skill, use sphere cast (using sphere distance) to cache nearby characters - and lookup using chunk entities and not a seperate query
void AOEDamageSystem(ecs_iter_t *it) {
    const float damage_rate = 2.0f;
    const float damage_radius = 3.0f;
    const float delta_time = zox_delta_time;
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i_in(Position3D, position3Ds, position3D)
        // get nearby characters using distance formula
        ecs_iter_t it3 = ecs_query_iter(world, it->ctx);
        ecs_iter_t *it2 = &it3;
        while(ecs_query_next(it2)) {
            const Position3D *position3D2s = ecs_field(it2, Position3D, 1);
            const StatLinks *statLinkss = ecs_field(it2, StatLinks, 2);
            Children *childrens = ecs_field(it2, Children, 3);
            for (int j = 0; j < it2->count; j++) {
                const ecs_entity_t e2 = it2->entities[j];
                if (e == e2) continue;
                const Position3D *position3D2 = &position3D2s[j];
                Children *children = &childrens[j];
                const float distance = float3_distance(position3D->value, position3D2->value);
                if (distance > damage_radius) {
                    if (children->length) {
                        ecs_entity_t particle3D_emitter = children->value[0];
                        remove_from_memory_component(children, ecs_entity_t, particle3D_emitter)
                        zox_delete(particle3D_emitter)
                    }
                    continue;
                }
                // spawn particle system
                // zox_log("  > spawning particle3D emitter [%i]\n", children->length)
                if (!children->length) {
                    ecs_entity_t particle3D_emitter = spawn_particle3D_emitter(world, e2, 4);
                    resize_memory_component(Children, children, ecs_entity_t, 1)
                    children->value[0] = particle3D_emitter;
                }
                const StatLinks *statLinks = &statLinkss[j];
                const ecs_entity_t health_stat = statLinks->value[0];
                StatValue *statValue = zox_get_mut(health_stat, StatValue)
                statValue->value -= delta_time * damage_rate;
                if (statValue->value < 0) statValue->value = 0;
                zox_modified(health_stat, StatValue)
                if (!statValue->value) continue;
#ifdef zox_debug_aoe_damage_system
                spawn_line3D(world, position3D->value, position3D2->value, 0.5f, 0.1);
#endif
            }
        }
    }
} zox_declare_system(AOEDamageSystem)
