// basically if viewport resizes, itll resize canvas / all 2D uis
void ResizeElementSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(CanvasLink, canvasLinks, 1)
    zox_field_in(ParentLink, parentLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(CanvasLink, canvasLinks, canvasLink)
        zox_field_i_in(ParentLink, parentLinks, parentLink)
        if (parentLink->value != canvasLink->value) continue;
        zox_field_e()
        set_ui_transform(world, e, canvasLink->value, 0, resize_element_system_screen_size);
    }
} zox_declare_system(ResizeElementSystem)
