void ZevicePointerRightResetSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_out(ZevicePointerRight)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(ZevicePointerRight, zevicePointerRight)
        zevicePointerRight->value = reset_button_state(zevicePointerRight->value);
    }
} zox_declare_system(ZevicePointerRightResetSystem)