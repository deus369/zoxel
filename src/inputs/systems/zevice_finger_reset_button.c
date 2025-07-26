void ZeviceFingerResetSystem(ecs_iter_t *it) {
    zox_sys_begin()
    zox_sys_in(ZevicePointerOld)
    zox_sys_out(ZevicePointerPosition)
    zox_sys_out(ZevicePointerDelta)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(ZevicePointerOld, zevicePointerOld)
        zox_sys_o(ZevicePointerPosition, zevicePointerPosition)
        zox_sys_o(ZevicePointerDelta, zevicePointerDelta)
        if (devices_get_released_this_frame(zevicePointerOld->value)) {
            zevicePointerPosition->value = int2_hidden;
            zevicePointerDelta->value = int2_zero;
        }
    }
} zox_declare_system(ZeviceFingerResetSystem)