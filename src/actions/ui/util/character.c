void set_player_action(ecs_world_t *world, const ecs_entity_t player, const byte index) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuActions, actionbar)
    if (!actionbar) {
        return;
    }
    zox_geter(actionbar, Children, window_children)
    if (window_children->length < 2) {
        return;
    }
    zox_geter(window_children->value[1], Children, children)
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
            zox_log_error("[%i] has no ActiveState", i)
            continue;
        }
        if (zox_gett_value(child, ActiveState)) {
            if (i == index) return;
            zox_set(child, ActiveState, { 0 })
            break;
        }
    }
    zox_set(children->value[index], ActiveState, { 1 })
    spawn_sound_from_file_name(world, prefab_sound, "swap_action", 0, get_volume_sfx());
}

void player_action_ui_move(ecs_world_t *world, const ecs_entity_t player, const int direction) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuActions, actionbar)
    if (!actionbar) {
        return;
    }
    zox_geter(actionbar, Children, window_children)
    if (window_children->length < 2) {
        return;
    }
    zox_geter(window_children->value[1], Children, children)
    if (children->length == 0) {
        return;
    }
    int selected = -1;
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t child = children->value[i];
        if (!zox_valid(child)) {
            continue;
        }
        if (!zox_has(child, ActiveState)) {
            zox_log_error("[%i] has no ActiveState", i)
            continue;
        }
        if (zox_gett_value(child, ActiveState)) {
            zox_set(child, ActiveState, { 0 })
            selected = i;
            break;
        }
    }
    if (selected == -1) {
        selected = 0; // none selected
    }
    selected += direction;
    if (selected == -1) {
        selected = children->length - 1;
    } else if (selected == children->length) {
        selected = 0;
    }
    zox_set(children->value[selected], ActiveState, { 1 })
    spawn_sound_from_file_name(world, prefab_sound, "swap_action", 0, get_volume_sfx());
}

byte get_player_action_index(ecs_world_t *world, const ecs_entity_t player) {
    if (!zox_valid(player)) {
        zox_log_error(" ! player invalid")
        return 255;
    }
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    if (!canvas) {
        return 255;
    }
    find_child_with_tag(canvas, MenuActions, actionbar)
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
}

void button_event_switch_action(ecs_world_t *world, const ClickEventData *event) {
    player_action_ui_move(world, event->clicker, 1);
}