// todo: SelectedEvent, Deselected Event, or, SelectState = SelectedThisFrame, Selected, Deselected, None
// todo: Give item a texture, spawn as icon!

void UserIconTooltipSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(SelectState, selectStates, 1)
    zox_field_in(UserDataLink, userDataLinks, 2)
    zox_field_in(CanvasLink, canvasLinks, 3)
    zox_field_in(TooltipEvent, tooltipEvents, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(SelectState, selectStates, selectState)
        if (!(selectState->value == zox_select_state_selected_this_frame || selectState->value == zox_select_state_deselected_this_frame)) {
            continue;
        }
        zox_field_i(UserDataLink, userDataLinks, userDataLink)
        zox_field_i(TooltipEvent, tooltipEvents, tooltipEvent)
        if (!userDataLink->value || !tooltipEvent->value) {
            continue;
        }
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
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

