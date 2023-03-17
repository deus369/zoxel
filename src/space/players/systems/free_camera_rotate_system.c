const int max_mouse_delta = 80;

void FreeCameraRotateSystem(ecs_iter_t *it) {
    double rotate_power = zoxel_delta_time; //  (double) (it->delta_time);
    rotate_power = 0.62 * rotate_power * degreesToRadians * 32.0;
    #ifdef WEB_BUILD
        rotate_power *= 10.0;
    #endif
    ecs_query_t *cameraQuery = it->ctx;
    if (!cameraQuery) {
        zoxel_log("[FreeCameraMoveSystem; cameraQuery is null]\n");
        return;
    }
    ecs_iter_t cameraIter = ecs_query_iter(it->world, cameraQuery);
    ecs_query_next(&cameraIter);
    if (cameraIter.count == 0) {
        return;
    }
    Mouse *mouses = ecs_field(it, Mouse, 1);
    const FreeRoam *freeRoams = ecs_field(&cameraIter, FreeRoam, 2);
    Euler *eulers = ecs_field(&cameraIter, Euler, 3);
    unsigned char can_rotate_cameras = 0;
    for (int j = 0; j < cameraIter.count; j++) {
        const FreeRoam *freeRoam = &freeRoams[j];
        if (freeRoam->value == 1) {
            can_rotate_cameras = 1;
            break;
        }
    }
    if (!can_rotate_cameras) {
        return;
    }
    for (int i = 0; i < it->count; i++) {
        const Mouse *mouse = &mouses[i];
        if (int_abs(mouse->delta.x) + int_abs(mouse->delta.y) >= max_mouse_delta) {
            // zoxel_log("mouse delta out of bounds [%ix%i]\n", mouse->delta.x, mouse->delta.y);
            continue;
        }
        float3 eulerAddition = { 0, -mouse->delta.x, mouse->delta.y };
        if (!(eulerAddition.x == 0 && eulerAddition.y == 0 && eulerAddition.z == 0)) {
            eulerAddition = float3_multiply_float(eulerAddition, (float) rotate_power);
            for (int j = 0; j < cameraIter.count; j++) {
                const FreeRoam *freeRoam = &freeRoams[j];
                Euler *euler = &eulers[j];
                if (freeRoam->value == 1) {
                    euler->value = float3_add(euler->value, eulerAddition);
                    // zoxel_log("mouse->delta eulerAddition [%ix%i]\n", mouse->delta.x, mouse->delta.y);
                }
            }
        }
    }
}
zoxel_declare_system(FreeCameraRotateSystem)