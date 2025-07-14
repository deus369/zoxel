void ButtonClickEventSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(ClickEvent, clickEvents, 1)
    zox_field_in(ClickState, clickStates, 2)
    zox_field_out(Clicker, clickers, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ClickState, clickStates, clickState)
        if (clickState->value != zox_click_state_released_this_frame) {
            continue;
        }
        zox_field_e()
        zox_field_i(ClickEvent, clickEvents, clickEvent)
        zox_field_o(Clicker, clickers, clicker)
        if (clickEvent->value) {
            const ClickEventData event_data = (ClickEventData) { .clicker = clicker->value, .clicked = e };
            (*clickEvent->value)(world, &event_data);
        }
    }
} zox_declare_system(ButtonClickEventSystem)
