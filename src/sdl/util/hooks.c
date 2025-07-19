void sdl_on_window_moved(ecs_world_t *world, const ecs_entity_t e, int2 position) {
    zox_log_sdl("> sdl_on_window_moved [%ix%i]", position.x, position.y)
    zox_set(e, WindowPosition, { position })
    if (!zox_gett_value(e, WindowFullscreen) && !zox_gett_value(e, WindowMaximized)) {
        zox_set(e, WindowPositionRestore, { position })
        zox_log_sdl("+ setting window restore position to [%ix%i]", position.x, position.y)
    }
    zox_geter_value(e, WindowMonitor, byte, old_monitor_index)
    byte monitor_index = zox_app_get_monitor(world, e);
    if (old_monitor_index != monitor_index) {
        zox_set(e, WindowMonitor, { monitor_index })
        zox_set_monitor_silently(world, e, monitor_index);
        zox_log_sdl("+ monitor has swapped [%i]", monitor_index)
    }
}

void on_window_resized(ecs_world_t *world, const ecs_entity_t e, int2 size) {
    if (!zox_gett_value(e, WindowFullscreen) && !zox_gett_value(e, WindowMaximized)) {
        zox_set(e, WindowSizeRestore, { size })
        zox_log_sdl("+ setting window restore size to [%ix%i]", size.x, size.y)
    }
    if (!int2_equals(size, zox_gett_value(e, WindowSize))) {
        zox_set(e, WindowSize, { size })
        zox_set(e, WindowSizeDirty, { zox_dirty_trigger })
        zox_log_sdl("+ window viewport [%ix%i]", size.x, size.y)
    }

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
