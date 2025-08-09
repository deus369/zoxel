void ZeviceButtonEnableSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(ZeviceButton)
    zox_sys_out(ZeviceDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ZeviceButton, zeviceButton)
        zox_sys_o(ZeviceDisabled, zeviceDisabled)
        if (!zeviceDisabled->value) {
            continue;
        }
        const byte has_input = devices_get_is_pressed(zeviceButton->value);
        if (!has_input) {
            zeviceDisabled->value = 0;
        }
    }
} zoxd_system(ZeviceButtonEnableSystem)
