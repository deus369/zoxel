void ZevicePointerDeltaResetSystem(iter *it) {
    zox_sys_begin()
    zox_sys_out(ZevicePointerDelta)
    for (int i = 0; i < it->count; i++) {
        zox_sys_o(ZevicePointerDelta, zevicePointerDelta)
        zevicePointerDelta->value = int2_zero;
    }
} zoxd_system(ZevicePointerDeltaResetSystem)
