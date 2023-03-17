void resize_camera(ecs_world_t *world, ecs_entity_t e, int2 new_screen_dimensions) {
    if (e && ecs_is_alive(world, e)) {
        ecs_set(world, e, ScreenDimensions, { new_screen_dimensions });
    }
}

//! Uses ecs_get_mut to resize cameras. \todo Create a viewport resize event.
void resize_cameras(int width, int height) {
    int2 new_screen_dimensions = (int2) { width, height };
    for (int i = 0; i < main_cameras_count; i++) {
        resize_camera(world, main_cameras[i], new_screen_dimensions);
    }
    resize_camera(world, ui_cameras[0], new_screen_dimensions);
}

void set_main_cameras(int new_count) {
    main_cameras_count = new_count;
}

unsigned char get_mouse_constrained() {
    ecs_entity_t main_camera = main_cameras[0];
    if (!ecs_is_valid(world, main_camera)) {
        return 0;
    }
    unsigned char constrain_mouse;
    if (ecs_has(world, main_camera, FreeRoam) && ecs_get(world, main_camera, FreeRoam)->value == 1) {
        return 1;
    } else {
        return 0;
    }
}