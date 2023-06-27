void GenericEventDebugSystem(ecs_iter_t *it) {
    zoxel_log(" > events occurs [%i]\n", it->count);
    const GenericEvent *genericEvents = ecs_field(it, GenericEvent, 1);
    for (int i = 0; i < it->count; i++) {
        const GenericEvent *genericEvent = &genericEvents[i];
        zoxel_log("     > event occurs [%lu] [%i]\n", it->entities[i], genericEvent->value);
    }
} zox_declare_system(GenericEventDebugSystem)