void resize_ui_canvases(ecs_world_t *world, int2 screen_size) {
    resize_element_system_screen_size = screen_size;
    zox_set_only(main_canvas, PixelSize, { screen_size })
    ecs_run(world, ecs_id(ResizeElementSystem), 0, NULL);
    #ifdef debug_viewport_resize
        zoxel_log(" > viewport resized to dimensions: [%ix%i]\n", screen_size.x, screen_size.y);
    #endif
}