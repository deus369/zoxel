int2 resize_element_system_screen_size = int2_zero;
// basically if viewport resizes, itll resize canvas / all 2D uis
void ResizeElementSystem(ecs_iter_t *it) {
    zox_iter_world()
    const CanvasLink *canvasLinks = ecs_field(it, CanvasLink, 1);
    const ParentLink *parentLinks = ecs_field(it, ParentLink, 2);
    for (int i = 0; i < it->count; i++) {
        const CanvasLink *canvasLink = &canvasLinks[i];
        const ParentLink *parentLink = &parentLinks[i];
        if (parentLink->value != canvasLink->value) continue; // do this for only canvas children
        ecs_entity_t e = it->entities[i];
        set_ui_transform(world, e, canvasLink->value, 0, resize_element_system_screen_size);
    }
} zox_declare_system(ResizeElementSystem)
