// if poisoned, remove if leaving area
// I could do this per debuff instead of character...! if it's a area based debuff
void DamageAuraRemoveSystem(ecs_iter_t *it) {
    const float damage_radius = 3.0f; // todo: grab this off skill
    zox_iter_world()
    zox_field_in(Position3D, position3Ds, 1)
    zox_field_out(DotLinks, dotLinkss, 2)
    zox_field_out(Children, childrens, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_o(DotLinks, dotLinkss, dotLinks)
        zox_field_o(Children, childrens, children)
        for (int j = dotLinks->length - 1; j >= 0; j--) {
            unsigned char is_still_in_aura = 0;
            const ecs_entity_t dot = dotLinks->value[j];
            if (dot && zox_has(dot, SpawnerLink) && zox_has(dot, SkillLink)) {
                const ecs_entity_t user = zox_get_value(dot, SpawnerLink)
                const ecs_entity_t aura = zox_get_value(dot, SkillLink)
                if (user && aura && zox_gett_value(aura, SkillActive)) { // if user exists and skill is active
                    const float3 aura_position = zox_get_value(user, Position3D)
                    const float distance = float3_distance(position3D->value, aura_position);
                    is_still_in_aura = distance <= damage_radius;
                }
            } else {
                // handle errors
                if (!dot) {
                    zox_log(" ! dot invalid [%i]\n", j)
                } else if (!zox_has(dot, SpawnerLink)) {
                    zox_log(" ! dot [%s] has no SpawnerLink [%i]\n", zox_get_name(dot), j)
                } else {
                    zox_log(" ! dot has no SkillLink [%i]\n", j)
                }
                continue;
            }
            if (!is_still_in_aura) {
                // zox_log(" + no longer within aura [%i]\n", j)
                remove_from_DotLinks(dotLinks, dot);
                zox_delete(dot)
                // todo: link dot to particles?
                if (children->length) {
                    const ecs_entity_t particle3D_emitter = children->value[0];
                    remove_from_memory_component(children, ecs_entity_t, particle3D_emitter)
                    zox_delete(particle3D_emitter)
                }
            }
        }

    }
} zox_declare_system(DamageAuraRemoveSystem)
