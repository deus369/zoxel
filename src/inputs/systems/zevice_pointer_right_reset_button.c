void ZevicePointerRightResetSystem(ecs_iter_t *it) {
    zox_field_out(ZevicePointerRight, zevicePointerRights, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ZevicePointerRight, zevicePointerRights, zevicePointerRight)
        zevicePointerRight->value = reset_button_state(zevicePointerRight->value);
    }
} zox_declare_system(ZevicePointerRightResetSystem)