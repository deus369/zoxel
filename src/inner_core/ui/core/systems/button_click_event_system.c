void ButtonClickEventSystem(ecs_iter_t *it) {
    zox_iter_world()
    ClickState *clickableStates = ecs_field(it, ClickState, 2);
    const ClickEvent *clickEvents = ecs_field(it, ClickEvent, 3);
    for (int i = 0; i < it->count; i++) {
        ClickState *clickState = &clickableStates[i];
        if (clickState->value != 1) continue;
        const ClickEvent *clickEvent = &clickEvents[i];
        if (clickEvent->value != NULL) (*clickEvent->value)(world, it->entities[i]);
        clickState->value = 0;
    }
} zox_declare_system(ButtonClickEventSystem)
