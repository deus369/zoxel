void TooltipSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(SelectState, selectStates, 1)
    zox_field_in(CanvasLink, canvasLinks, 2)
    zox_field_in(TooltipEvent, tooltipEvents, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(SelectState, selectStates, selectState)
        if (!(selectState->value == zox_select_state_selected_this_frame || selectState->value == zox_select_state_deselected_this_frame)) {
            continue;
        }
        zox_field_i(TooltipEvent, tooltipEvents, tooltipEvent)
        if (!tooltipEvent->value) {
            continue;
        }
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        find_child_with_tag(canvasLink->value, Tooltip, tooltip)
        if (!tooltip) {
            zox_log(" ! tooltip not found in canvas\n")
            continue;
        }
        if (selectState->value == zox_select_state_deselected_this_frame) {
            set_entity_text(world, tooltip, "");
            continue;
        }
        TooltipEventData data = {
            .event = selectState->value,
            .tooltip = tooltip,
            .triggered = it->entities[i]
        };
        (*tooltipEvent->value)(world, &data);
    }
} zox_declare_system(TooltipSystem)