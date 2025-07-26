void ZevicePointerEnableSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(ZevicePointer)
    zox_sys_out(ZeviceDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ZevicePointer, zevicePointer)
        zox_sys_o(ZeviceDisabled, zeviceDisabled)
        if (!zeviceDisabled->value) {
            continue;
        }
        const byte has_input = devices_get_is_pressed(zevicePointer->value);
        if (!has_input) zeviceDisabled->value = 0;
    }
} zox_declare_system(ZevicePointerEnableSystem)
