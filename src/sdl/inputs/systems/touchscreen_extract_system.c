void TouchscreenExtractSystem(ecs_iter_t *it) {
    global_any_fingers_down = 0;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Children)
    zox_sys_in(AppLink)
    zox_sys_out(ScreenDimensions)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Children, children)
        zox_sys_i(AppLink, appLink)
        zox_sys_o(ScreenDimensions, screenDimensions)
        zox_geter_value(appLink->value, WindowSize, int2, screen_size)
        screenDimensions->value = screen_size;
        sdl_extract_touchscreen(world, children, screen_size);
    }
} zox_declare_system(TouchscreenExtractSystem)
