void ButtonClickEventSystem(ecs_iter_t *it) {
    zox_iter_world()
    const ClickEvent *clickEvents = ecs_field(it, ClickEvent, 2);
    ClickState *clickableStates = ecs_field(it, ClickState, 3);
    for (int i = 0; i < it->count; i++) {
        ClickState *clickState = &clickableStates[i];
        if (!clickState->value) continue;
        const ClickEvent *clickEvent = &clickEvents[i];
        const ecs_entity_t e = it->entities[i];
        clickState->value = 0;
        if (clickEvent->value) (*clickEvent->value)(world, e);
    }
} zox_declare_system(ButtonClickEventSystem)
