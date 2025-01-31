void GenericEventDebugSystem(ecs_iter_t *it) {
    zox_log(" > events occurs [%i]\n", it->count);
    zox_field_in(GenericEvent, genericEvents, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(GenericEvent, genericEvents, genericEvent)
        zox_log("     > event occurs [%lu] [%i]\n", e, genericEvent->value);
    }
} zox_declare_system(GenericEventDebugSystem)
