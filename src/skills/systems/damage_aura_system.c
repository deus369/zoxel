// #define zox_debug_aoe_damage_system
#ifdef zox_debug_aoe_damage_system
    extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void DamageAuraSystem(ecs_iter_t *it) {
    zox_sys_query()
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(UserLink)
    zox_sys_in(SkillActive)
    zox_sys_in(SkillDamage)
    zox_sys_in(SkillRange)
    zox_sys_in(Color)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(UserLink, userLink)
        zox_sys_i(SkillActive, skillActive)
        zox_sys_i(SkillDamage, skillDamage)
        zox_sys_i(SkillRange, skillRange)
        zox_sys_i(Color, colorr)
        if (!zox_alive(userLink->value) || !skillActive->value || !skillDamage->value || !skillRange->value) {
            continue;
        }
        // zox_get_prefab(prefab_aura, e)
        const ecs_entity_t user = userLink->value;
        zox_geter_value(userLink->value, Position3D, float3, position3)
        // todo: Get Chunk' Characters instead, this could potentially go through tens of thousands..
        // get nearby characters using distance formula
        // make this spherecast
        zox_sys_query_begin()
        while (zox_sys_query_loop()) {
            zox_sys_begin_2()
            zox_sys_in_2(Dead)
            zox_sys_in_2(Position3D)
            zox_sys_out_2(Children)
            zox_sys_out_2(DotLinks)
            for (int j = 0; j < it2.count; j++) {
                zox_sys_e_2()
                zox_sys_i_2(Position3D, position3D2)
                zox_sys_i_2(Dead, dead)
                zox_sys_o_2(Children, children)
                zox_sys_o_2(DotLinks, dotLinks)
                if (user == e2 || dead->value) {
                    continue;
                }
                const float distance = float3_distance(position3, position3D2->value);
                ecs_entity_t poisoned_entity = 0;
                // Checks if dot was already added to player!
                // get poison, that  was initiated by this aura user
                for (int k = 0; k < dotLinks->length; k++) {
                    const ecs_entity_t dot = dotLinks->value[k];
                    if (!zox_has(dot, SkillLink)) {
                        continue;
                    }
                    zox_geter_value(dot, SkillLink, ecs_entity_t, skill_spawner)
                    // zox_get_prefab(prefab_aura, e)
                    // if added in this function, SpawnerLink doesn't get added into flecs table until after the function, so the dot will not have component access yet, assume we havn't added a dot yet from the current user
                    if (skill_spawner == e) { // zox_has(dot, SpawnerLink) && zox_gett_value(dot, SpawnerLink) == user) {
                        poisoned_entity = dot;
                        break;
                    }
                }
                if (poisoned_entity) {
                    continue;
                }
                // makes sure to check the debuff is linked to same character
                // makes it so t two players can damage a character at once
                if (distance <= skillRange->value) {
                    const ecs_entity_t new_dot = spawn_poison(world, prefab_poison, e2, user, e, skillDamage->value);
                    // zox_log(" + added new dot [%s] [%lu] total dots [%i]\n", zox_get_name(new_dot), new_dot, dotLinks->length)
                    add_to_DotLinks(dotLinks, new_dot);
                    // spawn particle system
                    const float3 bounds = zox_get_value(e2, Bounds3D)
                    const ecs_entity_t particle3D_emitter = spawn_particle3D_emitter(world, e2, 4, float3_scale(bounds, 2), colorr->value);
                    add_to_Children(children, particle3D_emitter);
                    zox_set(particle3D_emitter, SkillLink, { e })
#ifdef zox_debug_aoe_damage_system
                    spawn_line3D(world, position3, position3D2->value, 0.5f, 0.1);
#endif
                }
            }
        }
        zox_sys_query_end()
    }
} zox_declare_system(DamageAuraSystem)