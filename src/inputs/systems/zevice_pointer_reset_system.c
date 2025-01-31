void ZevicePointerResetSystem(ecs_iter_t *it) {
    zox_field_out(ZevicePointer, zevicePointers, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ZevicePointer, zevicePointers, zevicePointer)
        unsigned char last_value = zevicePointer->value;
        zevicePointer->value = reset_button_state(zevicePointer->value);
        // resets position here if finger is released last frame
        zox_field_e()
        if (zox_has(e, Finger)) {
            if (devices_get_released_this_frame(last_value)) {
                zox_get_muter(e, ZevicePointerPosition, zevicePointerPosition)
                zox_get_muter(e, ZevicePointerDelta, zevicePointerDelta)
                zevicePointerPosition->value = int2_hidden;
                zevicePointerDelta->value = int2_zero;
            }
        }
    }
} zox_declare_system(ZevicePointerResetSystem)

void ZevicePointerRightResetSystem(ecs_iter_t *it) {
    zox_field_out(ZevicePointerRight, zevicePointerRights, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ZevicePointerRight, zevicePointerRights, zevicePointerRight)
        zevicePointerRight->value = reset_button_state(zevicePointerRight->value);
    }
} zox_declare_system(ZevicePointerRightResetSystem)
