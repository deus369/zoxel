// update inspector element text every .5 seconds by checking if value changed... with a string check
void InspectorElementSystem(ecs_iter_t *it) {
    zox_iter_world()
    const EntityTarget *entityTargets = ecs_field(it, EntityTarget, 2);
    const ComponentTarget *componentTargets = ecs_field(it, ComponentTarget, 3);
    //ZextData *zextDatas = ecs_field(it, ZextData, 3);
    //ZextDirty *zextDirtys = ecs_field(it, ZextDirty, 4);
    for (int i = 0; i < it->count; i++) {
        const EntityTarget *entityTarget = &entityTargets[i];
        if (!entityTarget->value) continue;
        if (!ecs_is_alive(world, entityTarget->value)) continue;
        const ComponentTarget *componentTarget = &componentTargets[i];
        if (!componentTarget->value) continue;
        const ecs_entity_t e = it->entities[i];
        //ZextDirty *zextDirty = &zextDirtys[i];
        //if (zextDirty->value) continue;
        //ZextData *zextData = &zextDatas[i];
        char buffer[inspector_component_size_buffer];
        get_component_label(world, entityTarget->value, componentTarget->value, buffer);
        // zox_log("   > if value changed [%s]\n", buffer)
        // zextDirty->value = 1;
        set_entity_label_with_text(world, e, buffer);
    }
    // zox_log("   > inspector elements [%i]\n", it->count)
} zox_declare_system(InspectorElementSystem)
