void ButtonClickEventSystem(ecs_iter_t *it) {
    const ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    const ClickEvent *clickEvents = ecs_field(it, ClickEvent, 3);
    for (int i = 0; i < it->count; i++) {
        const ClickableState *clickableState = &clickableStates[i];
        if (clickableState->value == 1) {
            const ClickEvent *clickEvent = &clickEvents[i];
            if (clickEvent->value != NULL) {
                (*clickEvent->value)(it->world, it->entities[i]);
            }
        }
    }
}
zoxel_declare_system(ButtonClickEventSystem)