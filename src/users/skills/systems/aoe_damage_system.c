// #define zox_debug_aoe_damage_system
#ifdef zox_debug_aoe_damage_system
extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif
// todo: Seperate area from damage, so the skill is a child of character, and it finds characters in area and applies damage at end step
// todo: seperate skill, use sphere cast (using sphere distance) to cache nearby characters - and lookup using chunk entities and not a seperate query
void AOEDamageSystem(ecs_iter_t *it) {
    const float damage_radius = 3.0f;
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i_in(Position3D, position3Ds, position3D)
        // get nearby characters using distance formula
        // make this spherecast
        ecs_iter_t it2 = ecs_query_iter(world, it->ctx);
        while(ecs_query_next(&it2)) {
            const Dead *deads = ecs_field(&it2, Dead, 1);
            const Position3D *position3D2s = ecs_field(&it2, Position3D, 2);
            Children *childrens = ecs_field(&it2, Children, 3);
            Poison *poisons = ecs_field(&it2, Poison, 4);
            for (int j = 0; j < it2.count; j++) {
                const ecs_entity_t e2 = it2.entities[j];
                if (e == e2) continue;
                const Dead *dead = &deads[j];
                if (dead->value) continue;
                const Position3D *position3D2 = &position3D2s[j];
                Children *children = &childrens[j];
                Poison *poison = &poisons[j];
                const float distance = float3_distance(position3D->value, position3D2->value);

                // Fuck it was doingg  both att  once!!!
                // make sure to check the debuff is linked to same character
                // make it so t two players can damage a character at once
                /*if (distance > damage_radius) {
                    if (poison->value) {
                        poison->value = 0;
                        if (children->length) {
                            const ecs_entity_t particle3D_emitter = children->value[0];
                            remove_from_memory_component(children, ecs_entity_t, particle3D_emitter)
                            zox_delete(particle3D_emitter)
                        }
                    }
                } else {*/
                if (distance <= damage_radius) {
                    // spawn particle system
                    if (!poison->value) {
                        poison->value = 1;
                        // zox_log("aoedmg on %lu - %lu\n", it->entities[i], e2)
                        if (!children->length) {
                            ecs_entity_t particle3D_emitter = spawn_particle3D_emitter(world, e2, 4);
                            add_to_Children(children, particle3D_emitter);
                        }
                    }
#ifdef zox_debug_aoe_damage_system
                    spawn_line3D(world, position3D->value, position3D2->value, 0.5f, 0.1);
#endif
                }
            }
        }
    }
} zox_declare_system(AOEDamageSystem)
