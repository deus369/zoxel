void FreeCameraToggleSystem(ecs_iter_t *it) {
    // QueryContainer2 *queryContainer2 = (QueryContainer2*) it->ctx;
    // ecs_query_t *cameraQuery = it->ctx; // queryContainer2->query1;
    ecs_iter_t cameraIter = ecs_query_iter(it->world, it->ctx);
    ecs_query_next(&cameraIter);
    if (cameraIter.count == 0) {
        return;
    }
    const Mouse *mouses = ecs_field(it, Mouse, 1);
    MouseLock *mouseLocks = ecs_field(it, MouseLock, 2);
    FreeRoam *freeRoams = ecs_field(&cameraIter, FreeRoam, 2);
    for (int i = 0; i < it->count; i++) {
        const Mouse *mouse = &mouses[i];
        if (mouse->left.pressed_this_frame || mouse->right.pressed_this_frame) {
            MouseLock *mouseLock = &mouseLocks[i];
            if (mouseLock->value == 0) {
                mouseLock->value = 1;
            } else {
                mouseLock->value = 0;
            }
            zoxel_log(" > free camera toggled [%s]\n", mouseLock->value ? "on" : "off");
            for (int j = 0; j < cameraIter.count; j++) {
                FreeRoam *freeRoam = &freeRoams[j];
                freeRoam->value = mouseLock->value;
            }
        }
    }
}
zoxel_declare_system(FreeCameraToggleSystem)