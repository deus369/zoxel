void resize_ui_canvases(ecs_world_t *world, int2 screen_size) {
    resize_element_system_screen_size = screen_size;
    zox_set_only(main_canvas, PixelSize, { screen_size })
    ecs_run(world, ecs_id(ResizeElementSystem), 0, NULL);
    #ifdef debug_viewport_resize
        zoxel_log(" > viewport resized to dimensions: [%ix%i]\n", screen_size.x, screen_size.y);
    #endif
}

// based off 1920x1080
const float test_screen_height = 1080;
void fix_for_screen_size(int2 *pixel_size, int2 screen_size) {
    float max_dimension = int2_min(screen_size);
    pixel_size->x = (int) ((pixel_size->x / test_screen_height) * max_dimension);
    pixel_size->y = (int) ((pixel_size->y / test_screen_height) * max_dimension);
}

void fix_text_for_screen_size(int2 *position, int *font_size, int2 screen_size) {
    float max_dimension = int2_min(screen_size);
    *font_size = (int) ((*font_size / test_screen_height) * max_dimension);
    position->x = (int) ((position->x / test_screen_height) * max_dimension);
    position->y = (int) ((position->y / test_screen_height) * max_dimension);
}