// reset each zevice in a system, on EcsOnLoad
void ZeviceButtonResetSystem(iter *it) {
    zox_sys_begin()
    zox_sys_out(ZeviceButton)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(ZeviceButton, zeviceButton)
        reset_device_button(zeviceButton);
    }
} zoxd_system(ZeviceButtonResetSystem)
