// todo: SelectedEvent, Deselected Event, or, SelectState = SelectedThisFrame, Selected, Deselected, None
// todo: Give item a texture, spawn as icon!
void UserIconFrameSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(SelectState, selectStates, 1)
    zox_field_in(UserDataLink, userDataLinks, 2)
    zox_field_in(CanvasLink, canvasLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(SelectState, selectStates, selectState)
        zox_field_i(UserDataLink, userDataLinks, userDataLink)
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        if (!(selectState->value == zox_select_state_selected_this_frame || selectState->value == zox_select_state_deselected_this_frame)) continue;
        if (!userDataLink->value) {
            // zox_log(" + %s blank item ui\n", select_type)
            continue;
        }
        find_child_with_tag(canvasLink->value, Tooltip, tooltip)
        if (!tooltip) {
            zox_log(" ! tooltip not found\n")
            continue;
        }
        if (selectState->value == zox_select_state_deselected_this_frame) {
            set_entity_with_text(world, tooltip, "");
            zox_set(tooltip, RenderDisabled, { 1 })
            continue;
        }
        // zox_log(" + selecting user element: %s\n", zox_get_name(userDataLink->value))
        char *result = malloc(64);
        const ZoxName *zox_name = zox_get(userDataLink->value, ZoxName)
        if (zox_name) {
            char *name_string = convert_zext_to_text(zox_name->value, zox_name->length);
            // zox_log(" + %s item ui [%s]\n", select_type, name_string)
            sprintf(result, "[%s] x1\n", name_string);
            free(name_string);
        } else {
            // zox_log(" + %s item ui [%lu]\n", select_type, userDataLink->value)
            sprintf(result, "[%lu] x1\n", userDataLink->value);
        }
        set_entity_with_text(world, tooltip, result);
        free(result);
        zox_set(tooltip, RenderDisabled, { 0 })
    }
} zox_declare_system(UserIconFrameSystem)
