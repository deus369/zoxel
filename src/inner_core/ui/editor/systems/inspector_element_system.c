// update inspector element text every .5 seconds by checking if value changed... with a string check
void InspectorElementSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(EntityTarget, entityTargets, 2)
    zox_field_in(ComponentTarget, componentTargets, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(EntityTarget, entityTargets, entityTarget)
        if (!entityTarget->value) continue;
        if (!zox_alive(entityTarget->value)) continue;
        zox_field_i_in(ComponentTarget, componentTargets, componentTarget)
        if (!componentTarget->value) continue;
        zox_field_e()
        char buffer[inspector_component_size_buffer];
        get_component_label(world, entityTarget->value, componentTarget->value, buffer);
        set_entity_label_with_text(world, e, buffer);
    }
} zox_declare_system(InspectorElementSystem)
