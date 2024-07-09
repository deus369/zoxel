void TouchscreenExtractSystem(ecs_iter_t *it) {
    const int2 touchscreen_size = viewport_dimensions;
    zox_iter_world()
    zox_field_in(Children, childrens, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Children, childrens, children)
        sdl_extract_touchscreen(world, children, touchscreen_size);
    }
} zox_declare_system(TouchscreenExtractSystem)
