void ZevicePointerResetSystem(ecs_iter_t *it) {
    ZevicePointer *zevicePointers = ecs_field(it, ZevicePointer, 1);
    for (int i = 0; i < it->count; i++) {
        ZevicePointer *zevicePointer = &zevicePointers[i];
        reset_device_pointer(zevicePointer);
    }
} zox_declare_system(ZevicePointerResetSystem)