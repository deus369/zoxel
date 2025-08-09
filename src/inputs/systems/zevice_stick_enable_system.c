void ZeviceStickEnableSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(ZeviceStick)
    zox_sys_out(ZeviceDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ZeviceStick, zeviceStick)
        zox_sys_o(ZeviceDisabled, zeviceDisabled)
        if (!zeviceDisabled->value) {
            continue;
        }
        const byte has_input = zevice_stick_has_input(zeviceStick, joystick_min_cutoff);
        if (!has_input) {
            zeviceDisabled->value = 0;
        }
    }
} zoxd_system(ZeviceStickEnableSystem)