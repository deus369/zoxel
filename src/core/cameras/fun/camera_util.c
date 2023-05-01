void resize_camera(ecs_world_t *world, ecs_entity_t e, int2 new_screen_dimensions) {
    if (e && ecs_is_alive(world, e)) {
        ecs_set(world, e, ScreenDimensions, { new_screen_dimensions });
    }
}

//! Uses ecs_get_mut to resize cameras. \todo Create a viewport resize event.
void resize_cameras(int2 screen_size) {
    for (int i = 0; i < main_cameras_count; i++) {
        resize_camera(world, main_cameras[i], screen_size);
    }
    resize_camera(world, ui_cameras[0], screen_size);
}

void set_main_cameras(int new_count) {
    main_cameras_count = new_count;
}

unsigned char get_mouse_constrained() {
    return ecs_get(world, mouse_entity, MouseLock)->value;
}