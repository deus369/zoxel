// update inspector element text every .5 seconds by checking if value changed... with a string check
void InspectorElementSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(EntityTarget)
    zox_sys_in(ComponentTarget)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(EntityTarget, entityTarget)
        zox_sys_i(ComponentTarget, componentTarget)
        if (!entityTarget->value || !zox_alive(entityTarget->value) || !componentTarget->value) {
            continue;
        }
        char buffer[inspector_component_size_buffer];
        get_component_label(world, entityTarget->value, componentTarget->value, buffer);
        set_entity_label_with_text(world, e, buffer);
    }
} zoxd_system(InspectorElementSystem)