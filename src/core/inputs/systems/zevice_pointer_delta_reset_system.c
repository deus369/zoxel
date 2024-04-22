void ZevicePointerDeltaResetSystem(ecs_iter_t *it) {
    zox_field_out(ZevicePointerDelta, zevicePointerDeltas, 1)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(ZevicePointerDelta, zevicePointerDeltas, zevicePointerDelta)
        zevicePointerDelta->value = int2_zero;
    }
} zox_declare_system(ZevicePointerDeltaResetSystem)
