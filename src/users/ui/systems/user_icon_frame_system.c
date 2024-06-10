// todo: SelectedEvent, Deselected Event, or, SelectState = SelectedThisFrame, Selected, Deselected, None
// todo: Give item a texture, spawn as icon!
void UserIconFrameSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(SelectState, selectStates, 1)
    zox_field_in(UserDataLink, userDataLinks, 2)
    zox_field_in(CanvasLink, canvasLinks, 3)
    zox_field_in(TooltipEvent, tooltipEvents, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(SelectState, selectStates, selectState)
        zox_field_i(UserDataLink, userDataLinks, userDataLink)
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        zox_field_i(TooltipEvent, tooltipEvents, tooltipEvent)
        if (!(selectState->value == zox_select_state_selected_this_frame || selectState->value == zox_select_state_deselected_this_frame)) continue;
        if (!userDataLink->value) {
            continue;
        }
        if (!tooltipEvent->value) continue;
        find_child_with_tag(canvasLink->value, Tooltip, tooltip)
        if (!tooltip) {
            zox_log(" ! tooltip not found\n")
            continue;
        }
        // zox_set(tooltip, RenderDisabled, { (selectState->value == zox_select_state_deselected_this_frame) })
        TooltipEventData data = {
            .event = selectState->value,
            .tooltip = tooltip,
            .data = userDataLink->value
        };
        (*tooltipEvent->value)(world, &data);
    }
} zox_declare_system(UserIconFrameSystem)
