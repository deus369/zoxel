void TouchscreenExtractSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(Children, childrens, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Children, childrens, children)
        sdl_extract_touchscreen(world, children);
    }
} zox_declare_system(TouchscreenExtractSystem)
