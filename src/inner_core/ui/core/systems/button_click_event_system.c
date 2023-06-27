void ButtonClickEventSystem(ecs_iter_t *it) {
    ClickableState *clickableStates = ecs_field(it, ClickableState, 2);
    const ClickEvent *clickEvents = ecs_field(it, ClickEvent, 3);
    for (int i = 0; i < it->count; i++) {
        ClickableState *clickableState = &clickableStates[i];
        if (clickableState->value != 1) continue;
        const ClickEvent *clickEvent = &clickEvents[i];
        if (clickEvent->value != NULL) (*clickEvent->value)(it->world, it->entities[i]);
        clickableState->value = 0;
        // zoxel_log(" > click event  clicking\n");
    }
} zox_declare_system(ButtonClickEventSystem)