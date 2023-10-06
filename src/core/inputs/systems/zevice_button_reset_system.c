// reset each zevice in a system, on EcsOnLoad
// make extract system too, link the sdl joystick to the reset systems

void ZeviceButtonResetSystem(ecs_iter_t *it) {
    ZeviceButton *zeviceButtons = ecs_field(it, ZeviceButton, 1);
    for (int i = 0; i < it->count; i++) {
        ZeviceButton *zeviceButton = &zeviceButtons[i];
        reset_device_button(zeviceButton);
    }
} zox_declare_system(ZeviceButtonResetSystem)

void ZevicePointerResetSystem(ecs_iter_t *it) {
    ZevicePointer *zevicePointers = ecs_field(it, ZevicePointer, 1);
    for (int i = 0; i < it->count; i++) {
        ZevicePointer *zevicePointer = &zevicePointers[i];
        reset_device_pointer(zevicePointer);
    }
} zox_declare_system(ZevicePointerResetSystem)

void ZevicePointerDeltaResetSystem(ecs_iter_t *it) {
    ZevicePointerDelta *zevicePointerDeltas = ecs_field(it, ZevicePointerDelta, 1);
    for (int i = 0; i < it->count; i++) {
        ZevicePointerDelta *zevicePointerDelta = &zevicePointerDeltas[i];
        zevicePointerDelta->value = int2_zero;
    }
} zox_declare_system(ZevicePointerDeltaResetSystem)