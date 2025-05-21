void key_down_toggle_streaming(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_j) {
        toggle_cameras_updates();
        spawn_sound_from_file(world, prefab_sound, 0);
    }
}

void key_down_test_ui(ecs_world_t *world, int32_t keycode) {
    if (keycode == SDLK_h) {
        const ecs_entity_t canvas = main_canvas;
        const int2 position = (int2) { 8, 8 };
        const int2 size = (int2) { 32 * 4, 32 * 4 };
        const ecs_entity_t source_texture = files_textures[2];
        spawn_element_texture(world, canvas, source_texture, position, size);
        spawn_sound_from_file(world, prefab_sound, 0);
    }
}
