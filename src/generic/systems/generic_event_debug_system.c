void GenericEventDebugSystem(ecs_iter_t *it) {
    zox_log(" > events occurs [%i]\n", it->count);
    zox_sys_begin()
    zox_sys_in(GenericEvent)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(GenericEvent, genericEvent)
        zox_log("     > event occurs [%lu] [%i]\n", e, genericEvent->value);
    }
} zoxd_system(GenericEventDebugSystem)
