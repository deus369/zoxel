void TouchscreenExtractSystem(ecs_iter_t *it) {
    const int2 touchscreen_size = viewport_dimensions;
    zox_iter_world()
    zox_field_in(Children, childrens, 1)
    zox_field_out(ScreenDimensions, screenDimensionss, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Children, childrens, children)
        zox_field_o(ScreenDimensions, screenDimensionss, screenDimensions)
        screenDimensions->value = touchscreen_size;
        sdl_extract_touchscreen(world, children, touchscreen_size);
    }
} zox_declare_system(TouchscreenExtractSystem)
