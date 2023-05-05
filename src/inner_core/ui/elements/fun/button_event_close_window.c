void button_event_close_window(ecs_world_t *world, ecs_entity_t trigger_entity) {
    // zoxel_log(" > closing window\n");
    const ParentLink *parentLink = ecs_get(world, trigger_entity, ParentLink);
    const ParentLink *parentParentLink = ecs_get(world, parentLink->value, ParentLink);
    ecs_entity_t window = parentParentLink->value;
    ecs_delete(world, window);
}

/*void WindowCloseSystem(ecs_iter_t *it) {
    const ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    for (int i = 0; i < it->count; i++) {
        const ClickableState *clickableState = &clickableStates[i];
        if (clickableState->value == 1) {
            const ParentLink *parentLink = ecs_get(it->world, it->entities[i], ParentLink);
            const ParentLink *parentParentLink = ecs_get(it->world, parentLink->value, ParentLink);
            ecs_entity_t window = parentParentLink->value;
            ecs_delete(it->world, window);
            // printf("Closing window [%lu].\n", (long int) window);
        }
    }
}
zoxel_declare_system(WindowCloseSystem)*/