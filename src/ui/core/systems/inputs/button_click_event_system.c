void ButtonClickEventSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ClickEvent)
    zox_sys_in(ClickState)
    zox_sys_out(Clicker)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(ClickEvent, clickEvent)
        zox_sys_i(ClickState, clickState)
        zox_sys_o(Clicker, clicker)
        if (clickState->value != zox_click_state_released_this_frame) {
            continue;
        }
        if (clickEvent->value) {
            const ClickEventData event_data = (ClickEventData) { .clicker = clicker->value, .clicked = e };
            (*clickEvent->value)(world, &event_data);
        }
    }
} zox_declare_system(ButtonClickEventSystem)
