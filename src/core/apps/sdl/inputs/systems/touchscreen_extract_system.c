void TouchscreenExtractSystem(ecs_iter_t *it) {
    zox_iter_world()
    const Children *childrens = ecs_field(it, Children, 2);
    for (int i = 0; i < it->count; i++) {
        const Children *childrenss = &childrens[i];
        sdl_extract_touchscreen(world, childrenss);
    }
} zox_declare_system(TouchscreenExtractSystem)
