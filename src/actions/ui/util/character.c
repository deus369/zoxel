void set_player_action(
    ecs_world_t *world,
    const ecs_entity_t player,
    const byte index
) {
    zox_geter_value(player, CharacterLink, ecs_entity_t, character);
    if (!zox_valid(character)) {
        return;
    }

    zox_set(character, ActionIndex, { index });
    spawn_sound_from_file_name(world, prefab_sound, "swap_action", 0, get_volume_sfx());

    zox_geter(character, ElementLinks, elements);
    find_array_element_with_tag(elements, MenuActions, actionbar);
    if (!actionbar) {
        return;
    }
    zox_geter(actionbar, Children, window_children);
    if (window_children->length < 2) {
        return;
    }
    zox_geter(window_children->value[1], Children, children);
    if (children->length == 0 || index >= children->length) {
        return;
    }
    // deselect first
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t child = children->value[i];
        if (!zox_valid(child)) {
            continue;
        }
        if (!zox_has(child, ActiveState)) {
            zox_log_error("[%i] has no ActiveState", i);
            continue;
        }
        zox_geter_value(child, ActiveState, byte, state);
        if (index != i && state) {
            zox_set(child, ActiveState, { 0 });
            zox_set(child, ActiveStateDirty, { zox_dirty_trigger });
        } else if (index == i && !state) {
            zox_set(child, ActiveState, { 1 });
            zox_set(child, ActiveStateDirty, { zox_dirty_trigger });
        }
    }
}

void player_action_ui_move(
    ecs_world_t *world,
    const ecs_entity_t player,
    const sbyte direction
) {
    zox_geter_value(player, CharacterLink, ecs_entity_t, character);
    if (!zox_valid(character)) {
        return;
    }
    zox_geter(character, ActionLinks, actions);
    zox_geter_value_non_const(character, ActionIndex, byte, selected);
    selected = selected + direction >= 0 ? selected + direction : actions->length + (selected + direction);
    zox_set(character, ActionIndex, { selected });
    spawn_sound_from_file_name(world, prefab_sound, "swap_action", 0, get_volume_sfx());

    // now set the ui
    zox_geter_value(player, CanvasLink, ecs_entity_t, canvas);
    find_child_with_tag(canvas, MenuActions, actionbar);
    if (!actionbar) {
        return;
    }
    zox_geter(actionbar, Children, window_children);
    if (window_children->length < 2) {
        return;
    }
    zox_geter(window_children->value[1], Children, children);
    if (children->length == 0) {
        return;
    }
    // deselect any prior ones
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t child = children->value[i];
        if (!zox_valid(child)) {
            continue;
        }
        if (!zox_has(child, ActiveState)) {
            zox_log_error("[%i] has no ActiveState", i);
            continue;
        }
        zox_geter_value(child, ActiveState, byte, state);
        if (selected != i && state) {
            zox_set(child, ActiveState, { 0 });
            zox_set(child, ActiveStateDirty, { zox_dirty_trigger });
        } else if (selected == i && !state) {
            zox_set(child, ActiveState, { 1 });
            zox_set(child, ActiveStateDirty, { zox_dirty_trigger });
        }
    }
}

void button_event_switch_action(ecs_world_t *world, const ClickEventData *event) {
    player_action_ui_move(world, event->clicker, 1);
}

/*byte get_character_action_index(ecs_world_t *world, const ecs_entity_t e) {
    if (!zox_valid(e)) {
        zox_log_error("character invalid")
        return 255;
    }
    zox_geter(e, ElementLinks, elements)
    find_array_element_with_tag(elements, MenuActions, actionbar)
    if (!actionbar) {
        return 255;
    }
    const Children *window_children = zox_get(actionbar, Children)
    if (window_children->length < 2) {
        return 255;
    }
    const Children *children = zox_get(window_children->value[1], Children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t child = children->value[i];
        if (!zox_valid(child) || !zox_has(child, ActiveState)) {
            continue;
        } else if (zox_gett_value(child, ActiveState)) {
            return i;
        }
    }
    return 255;
}*/