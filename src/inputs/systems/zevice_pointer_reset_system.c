void ZevicePointerResetSystem(ecs_iter_t *it) {
    zox_field_out(ZevicePointer, zevicePointers, 1)
    zox_field_out(ZevicePointerOld, zevicePointerOlds, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(ZevicePointer, zevicePointers, zevicePointer)
        zox_field_o(ZevicePointerOld, zevicePointerOlds, zevicePointerOld)
        zevicePointerOld->value = zevicePointer->value;
        zevicePointer->value = reset_button_state(zevicePointer->value);
    }
} zox_declare_system(ZevicePointerResetSystem)