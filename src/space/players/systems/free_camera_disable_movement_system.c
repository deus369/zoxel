void FreeCameraDisableMovementSystem(ecs_iter_t *it) {
    ecs_iter_t playerIter = ecs_query_iter(it->world, it->ctx);
    ecs_query_next(&playerIter);
    if (playerIter.count == 0) return;
    Mouse *mouses = ecs_field(it, Mouse, 1);
    DisableMovement *disableMovements = ecs_field(&playerIter, DisableMovement, 2);
    for (int i = 0; i < it->count; i++) {
        const Mouse *mouse = &mouses[i];
        if (mouse->left.pressed_this_frame) {
            for (int j = 0; j < playerIter.count; j++) {
                DisableMovement *disableMovement = &disableMovements[j];
                disableMovement->value = !disableMovement->value;
                zoxel_log(" > DisableMovement Toggled [%s]\n", disableMovement->value ? "true" : "false");
            }
        }
    }
} zox_declare_system(FreeCameraDisableMovementSystem)