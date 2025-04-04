// #define zox_debug_log_extract_mous

void sdl_reset_mouse_wheel() {
    static_mouse_wheel = int2_zero;
}

void sdl_extract_mouse_wheel(SDL_Event event) {
    if (event.type == SDL_MOUSEWHEEL) static_mouse_wheel = (int2) { event.wheel.x, event.wheel.y };
}
