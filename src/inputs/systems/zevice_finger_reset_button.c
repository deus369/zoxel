void ZeviceFingerResetSystem(ecs_iter_t *it) {
    zox_field_in(ZevicePointerOld, zevicePointerOlds, 1)
    zox_field_out(ZevicePointerPosition, zevicePointerPositions, 2)
    zox_field_out(ZevicePointerDelta, zevicePointerDeltas, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ZevicePointerOld, zevicePointerOlds, zevicePointerOld)
        zox_field_o(ZevicePointerPosition, zevicePointerPositions, zevicePointerPosition)
        zox_field_o(ZevicePointerDelta, zevicePointerDeltas, zevicePointerDelta)
        if (devices_get_released_this_frame(zevicePointerOld->value)) {
            zevicePointerPosition->value = int2_hidden;
            zevicePointerDelta->value = int2_zero;
        }
    }
} zox_declare_system(ZeviceFingerResetSystem)