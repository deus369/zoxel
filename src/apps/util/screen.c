void set_app_screen_resize(ecs_world_t *world, const ecs_entity_t e, const int2 size) {
    if (fullscreen) {
        default_window_position = (int2) { (size.x) / 2, (size.y) / 2 };
    } else {
        zox_log(" > screen_dimensions.x: %i > %i\n", size.x, default_window_size.x)
        default_window_position = (int2) { (size.x - default_window_size.x) / 2, (size.y - default_window_size.y) / 2 };
    }
    zox_set(e, WindowPosition, { default_window_position })
}

int2 get_window_position(int2 window_size, int2 screen_size) {
    if (window_size.x == screen_size.x && window_size.y == screen_size.y) {
        return (int2) { (screen_size.x) / 2, (screen_size.y) / 2 };
    } else {
        return (int2) { (screen_size.x - window_size.x) / 2, (screen_size.y - window_size.y) / 2 };
    }
}