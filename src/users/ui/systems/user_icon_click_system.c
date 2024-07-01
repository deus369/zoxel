void UserIconClickSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ClickState, clickStates, 1)
    zox_field_in(CanvasLink, canvasLinks, 2)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ClickState, clickStates, clickState)
        if (clickState->value != zox_click_state_clicked_this_frame) continue;
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        // swap icon with mouse icon
        zox_log(" > user icon clicked, following mouse\n")
    }
} zox_declare_system(UserIconClickSystem)
