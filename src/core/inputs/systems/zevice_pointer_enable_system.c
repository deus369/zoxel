void ZevicePointerEnableSystem(ecs_iter_t *it) {
    zox_field_in(ZevicePointer, zevicePointers, 1)
    zox_field_out(ZeviceDisabled, zeviceDisableds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ZeviceDisabled, zeviceDisableds, zeviceDisabled)
        if (!zeviceDisabled->value) continue;
        zox_field_i_in(ZevicePointer, zevicePointers, zevicePointer)
        const unsigned char has_input = devices_get_is_pressed(zevicePointer->value);
#ifdef zox_debug_zevice_states
        if (!has_input) zox_log("   = zevice_pointer reenabled [%lu] at %f\n", it->entities[i], zox_current_time)
#endif
        if (!has_input) zeviceDisabled->value = 0;
    }
} zox_declare_system(ZevicePointerEnableSystem)
