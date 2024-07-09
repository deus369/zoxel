void ZeviceStickEnableSystem(ecs_iter_t *it) {
    zox_field_in(ZeviceStick, zeviceSticks, 1)
    zox_field_out(ZeviceDisabled, zeviceDisableds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ZeviceDisabled, zeviceDisableds, zeviceDisabled)
        if (!zeviceDisabled->value) continue;
        zox_field_i(ZeviceStick, zeviceSticks, zeviceStick)
        const unsigned char has_input = zevice_stick_has_input(zeviceStick, joystick_min_cutoff);
#ifdef zox_debug_zevice_states
        if (!has_input) zox_log("   = joystick reenabled [%lu] at %f\n", it->entities[i], zox_current_time)
#endif
        if (!has_input) zeviceDisabled->value = 0;
    }
} zox_declare_system(ZeviceStickEnableSystem)
