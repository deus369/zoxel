void ZevicePointerResetSystem(ecs_iter_t *it) {
    zox_field_out(ZevicePointer, zevicePointers, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ZevicePointer, zevicePointers, zevicePointer)
        reset_device_pointer(zevicePointer);
    }
} zox_declare_system(ZevicePointerResetSystem)
