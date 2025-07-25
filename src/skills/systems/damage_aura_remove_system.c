// if poisoned, remove if leaving area
// I could do this per debuff instead of character...! if it's a area based debuff
void DamageAuraRemoveSystem(ecs_iter_t *it) {
    // const float damage_radius = 3.0f; // todo: grab this off skill
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_out(DotLinks)
    zox_sys_out(Children)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Position3D, position3D)
        zox_sys_o(DotLinks, dotLinks)
        zox_sys_o(Children, children)
        for (int j = dotLinks->length - 1; j >= 0; j--) {
            const ecs_entity_t dot = dotLinks->value[j];
            if (!zox_valid(dot) || !zox_has(dot, SkillLink)) {
                continue;
            }
            zox_geter_value(dot, SkillLink, ecs_entity_t, aura)
            zox_geter_value(dot, SpawnerLink, ecs_entity_t, user)
            if (!zox_valid(aura) || !zox_valid(user)) {
                // todo: remove dots when aura dies too
                continue;
            }
            zox_geter_value(aura, SkillRange, float, radius)
            zox_geter_value(aura, SkillActive, byte, active)
            byte is_still_in_aura = 0;
            if (active) { // if user exists and skill is active
                zox_geter_value(user, Position3D, float3, aura_position)
                const float distance = float3_distance(position3D->value, aura_position);
                is_still_in_aura = distance <= radius;
            }
            if (!is_still_in_aura) {
                // zox_log(" + no longer within aura [%i]\n", j)
                remove_from_DotLinks(dotLinks, dot);
                zox_delete(dot)
                // todo: link dot to particles?
                if (children->length) {
                    ecs_entity_t particle3D_emitter = 0;
                    for (int j = 0; j < children->length; j++) {
                        const ecs_entity_t child = children->value[j];
                        const ecs_entity_t skill = zox_get_value(child, SkillLink)
                        if (skill == aura) {
                            particle3D_emitter = child;
                            break;
                        }
                    }
                    if (particle3D_emitter) {
                        remove_from_Children(children, particle3D_emitter);
                        zox_delete(particle3D_emitter)
                    }
                }
            }
        }

    }
} zox_declare_system(DamageAuraRemoveSystem)