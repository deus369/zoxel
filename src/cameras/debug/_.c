void toggle_cameras_updates() {
    zox_cameras_disable_streaming = !zox_cameras_disable_streaming;
    zox_log("+ streaming is [%s]", zox_cameras_disable_streaming ? "disabled" : "enabled")
}

void key_down_toggle_streaming(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_F3) {
        toggle_cameras_updates();
        // spawn_sound_from_file_index(world, prefab_sound, 0);
    }
}