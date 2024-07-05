// #define zox_debug_aoe_damage_system
#ifdef zox_debug_aoe_damage_system
    extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

// todo: Seperate area from damage, so the skill is a child of character, and it finds characters in area and applies damage at end step
// todo: seperate skill, use sphere cast (using sphere distance) to cache nearby characters - and lookup using chunk entities and not a seperate query

void DamageAuraSystem(ecs_iter_t *it) {
    const float damage_radius = 3.0f;
    zox_iter_world()
    zox_field_in(UserLink, userLinks, 1)
    zox_field_in(SkillActive, skillActives, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(UserLink, userLinks, userLink)
        if (!zox_alive(userLink->value)) continue;
        zox_field_i(SkillActive, skillActives, skillActive)
        if (!skillActive->value) continue;
        zox_field_e()
        const ecs_entity_t user = userLink->value;
        const Position3D *position3D = zox_get(userLink->value, Position3D)
        // todo: Get Chunk' Characters instead, this could potentially go through tens of thousands..
        // get nearby characters using distance formula
        // make this spherecast
        ecs_iter_t it2 = ecs_query_iter(world, it->ctx);
        while(ecs_query_next(&it2)) {
            const Dead *deads = ecs_field(&it2, Dead, 1);
            const Position3D *position3D2s = ecs_field(&it2, Position3D, 2);
            Children *childrens = ecs_field(&it2, Children, 3);
            DotLinks *dotLinkss = ecs_field(&it2, DotLinks, 4);
            for (int j = 0; j < it2.count; j++) {
                const ecs_entity_t e2 = it2.entities[j];
                if (user == e2) continue;
                const Dead *dead = &deads[j];
                if (dead->value) continue;
                const Position3D *position3D2 = &position3D2s[j];
                Children *children = &childrens[j];
                DotLinks *dotLinks = &dotLinkss[j];
                const float distance = float3_distance(position3D->value, position3D2->value);
                ecs_entity_t poisoned_entity = 0;
                // Checks if dot was already added to player!
                // get poison, that  was initiated by this aura user
                for (int k = 0; k < dotLinks->length; k++) {
                    const ecs_entity_t dot = dotLinks->value[k];
                    // if added in this function, SpawnerLink doesn't get added into flecs table until after the function, so the dot will not have component access yet, assume we havn't added a dot yet from the current user
                    if (zox_has(dot, SpawnerLink) && zox_gett_value(dot, SpawnerLink) == user) {
                        poisoned_entity = dot;
                        break;
                    }
                }
                // makes sure to check the debuff is linked to same character
                // makes it so t two players can damage a character at once
                if (!poisoned_entity && distance <= damage_radius) {
                    const ecs_entity_t new_dot = spawn_poison(world, prefab_poison, e2, user, e);
                    // zox_log(" + added new dot [%s] [%lu] total dots [%i]\n", zox_get_name(new_dot), new_dot, dotLinks->length)
                    add_to_DotLinks(dotLinks, new_dot);
                    // spawn particle system
                    if (!children->length) {
                        const float3 bounds = zox_get_value(e2, Bounds3D)
                        const ecs_entity_t particle3D_emitter = spawn_particle3D_emitter(world, e2, 4, float3_multiply_float(bounds, 2));
                        add_to_Children(children, particle3D_emitter);
                    }
#ifdef zox_debug_aoe_damage_system
                    spawn_line3D(world, position3D->value, position3D2->value, 0.5f, 0.1);
#endif
                }
            }
        }
        ecs_iter_fini(&it2);
    }
} zox_declare_system(DamageAuraSystem)


/*if (poisoned_entity && distance > damage_radius) {
    // actually for removal here
    remove_from_DotLinks(dotLinks, poisoned_entity);
    zox_delete(poisoned_entity)
    if (children->length) {
        const ecs_entity_t particle3D_emitter = children->value[0];
        remove_from_memory_component(children, ecs_entity_t, particle3D_emitter)
        zox_delete(particle3D_emitter)
    }
} else */
