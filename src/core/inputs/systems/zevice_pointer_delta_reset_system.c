void ZevicePointerDeltaResetSystem(ecs_iter_t *it) {
    ZevicePointerDelta *zevicePointerDeltas = ecs_field(it, ZevicePointerDelta, 1);
    for (int i = 0; i < it->count; i++) {
        ZevicePointerDelta *zevicePointerDelta = &zevicePointerDeltas[i];
        zevicePointerDelta->value = int2_zero;
    }
} zox_declare_system(ZevicePointerDeltaResetSystem)