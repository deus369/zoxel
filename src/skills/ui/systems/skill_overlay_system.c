// UserDataLink, RenderDisabled

void SkillOverlaySystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(UserDataLink, userDataLinks, 1)
    zox_field_in(Children, childrens, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(UserDataLink, userDataLinks, userDataLink)
        // zox_log("> action frame %lu, user data [%lu]\n", it->entities[i], userDataLink->value)
        const ecs_entity_t skill = userDataLink->value;
        byte is_skill = skill && zox_valid(skill) && zox_alive(skill) && zox_has(skill, Skill);
        zox_field_i(Children, childrens, children)
        if (!children->length) {
            continue;
        }
        const ecs_entity_t overlay = children->value[0];
        byte skill_active = 0;
        if (is_skill) {
            skill_active = zox_get_value(skill, SkillActive)
        }
        const byte new_render_disabled = !skill_active;
        if (zox_gett_value(overlay, RenderDisabled) != new_render_disabled) {
            zox_set(overlay, RenderDisabled, { new_render_disabled })
        }
    }
} zox_declare_system(SkillOverlaySystem)