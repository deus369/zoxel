// #define zox_debug_log_extract_mous

void sdl_reset_mouse_wheel() {
    static_mouse_wheel = int2_zero;
}

void sdl_extract_mouse_wheel(SDL_Event event) {
    if (event.type == SDL_MOUSEWHEEL) {
        static_mouse_wheel = (int2) { event.wheel.x, event.wheel.y };
    }
}

int2 get_mouse_center_point(ecs_world_t *world, const ecs_entity_t e) {
    zox_geter_value2(e, WindowSize, int2, size)
    size = int2_half(size);
    if (zox_gett_value(e, WindowMaximized)) {
    //    size = get_window_size_without_header(world, e, size);
    }
    return size;
}