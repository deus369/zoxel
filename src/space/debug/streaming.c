void key_down_toggle_streaming(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_j) {
        toggle_cameras_updates();
        spawn_sound_from_file(world, prefab_sound, 0);
    }
}