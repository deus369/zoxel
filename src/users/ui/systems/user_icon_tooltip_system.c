// todo: SelectedEvent, Deselected Event, or, SelectState = SelectedThisFrame, Selected, Deselected, None
// todo: Give item a texture, spawn as icon!

void UserIconTooltipSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(SelectState)
    zox_sys_in(UserDataLink)
    zox_sys_in(CanvasLink)
    zox_sys_in(TooltipEvent)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(SelectState, selectState)
        zox_sys_i(UserDataLink, userDataLink)
        zox_sys_i(TooltipEvent, tooltipEvent)
        zox_sys_i(CanvasLink, canvasLink)
        if (!(selectState->value == zox_select_state_selected_this_frame || selectState->value == zox_select_state_deselected_this_frame)) {
            continue;
        }
        if (!zox_valid(userDataLink->value) || !tooltipEvent->value) {
            continue;
        }
        find_child_with_tag(canvasLink->value, Tooltip, tooltip)
        if (!tooltip) {
            zox_log(" ! tooltip not found in canvas\n")
            continue;
        }
        // deselect event here is fine
        if (selectState->value == zox_select_state_deselected_this_frame) {
            set_entity_text(world, tooltip, "");
            continue;
        }
        TooltipEventData data = {
            .event = selectState->value,
            .tooltip = tooltip,
            .data = userDataLink->value
        };
        (*tooltipEvent->value)(world, &data);
        // zox_log(" > icon [%lu] selected at %f\n", it->entities[i], zox_current_time)
    }
} zox_declare_system(UserIconTooltipSystem)

