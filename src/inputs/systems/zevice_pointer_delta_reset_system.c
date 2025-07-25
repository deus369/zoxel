void ZevicePointerDeltaResetSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_out(ZevicePointerDelta)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(ZevicePointerDelta, zevicePointerDelta)
        zevicePointerDelta->value = int2_zero;
    }
} zox_declare_system(ZevicePointerDeltaResetSystem)
