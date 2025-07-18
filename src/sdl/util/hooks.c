void sdl_on_window_moved(ecs_world_t *world, const ecs_entity_t e, int2 position) {
    zox_log_sdl("> sdl_on_window_moved [%ix%i]", position.x, position.y)
    //int window_height = get_sdl_window_header_size(world, e);
    //zox_geter_value(e, WindowSize, int2, size)
    //position.x += size.x / 2;
    //position.y += size.y / 2 + window_height;
    zox_set(e, WindowPosition, { position })
    if (!zox_gett_value(e, WindowFullscreen) && !zox_gett_value(e, WindowMaximized)) {
        zox_set(e, WindowPositionRestore, { position })
        zox_log_sdl("+ setting window restore position to [%ix%i]", position.x, position.y)
    }
}

void on_window_resized(ecs_world_t *world, const ecs_entity_t e, int2 size) {
    if (!zox_gett_value(e, WindowFullscreen) && !zox_gett_value(e, WindowMaximized)) {
        zox_set(e, WindowSizeRestore, { size })
        zox_log_sdl("+ setting window restore size to [%ix%i]", size.x, size.y)
    }
    zox_set(e, WindowSize, { size })
    set_viewport_size(world, size);
    screen_dimensions = size;
    zox_log_sdl("+ window viewport [%ix%i]", size.x, size.y)

}

void on_window_maximized(ecs_world_t *world, const ecs_entity_t e, const int2 size) {
    // zox_set_maximized(world, 1);
    zox_set_maximized_silently(world, e, 1);
    zox_log_sdl("+ window maximized [%ix%i]", size.x, size.y)
}

void on_window_restored(ecs_world_t *world, const ecs_entity_t e, const int2 size) {
    // zox_set_maximized(world, 0);
    zox_set_maximized_silently(world, e, 0);
    zox_log_sdl("+ window restored [%ix%i]", size.x, size.y)
}
