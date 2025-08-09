void TooltipSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(SelectState)
    zox_sys_in(CanvasLink)
    zox_sys_in(TooltipEvent)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(SelectState, selectState)
        zox_sys_i(TooltipEvent, tooltipEvent)
        zox_sys_i(CanvasLink, canvasLink)
        if (!(selectState->value == zox_select_state_selected_this_frame || selectState->value == zox_select_state_deselected_this_frame)) {
            continue;
        }
        if (!tooltipEvent->value) {
            continue;
        }
        find_child_with_tag(canvasLink->value, Tooltip, tooltip)
        if (!tooltip) {
            zox_log(" ! tooltip not found in canvas\n")
            continue;
        }
        if (selectState->value == zox_select_state_deselected_this_frame) {
            set_entity_text(world, tooltip, "");
            continue;
        }
        zox_sys_e()
        TooltipEventData data = {
            .event = selectState->value,
            .tooltip = tooltip,
            .triggered = e
        };
        if ((*tooltipEvent->value)(world, &data)) {
            // hmm need to rethink this
        }
    }
} zoxd_system(TooltipSystem)