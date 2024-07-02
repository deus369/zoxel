void set_player_action(ecs_world_t *world, const ecs_entity_t player, const unsigned char index) {
    // zox_log(" > setting action [%i]\n", index)
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    //find_child_with_tag(canvas, MenuGame, menu_game)
    //if (!menu_game) return;
    find_child_with_tag(canvas, MenuActions, actionbar)
    if (!actionbar) return;
    const Children *window_children = zox_get(actionbar, Children)
    if (window_children->length < 2) return;
    const Children *children = zox_get(window_children->value[1], Children)
    if (children->length == 0) return;
    if (index >= children->length) return;
    // deselect first
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t child = children->value[i];
        if (!zox_valid(child)) continue;
        if (!zox_has(child, ActiveState)) {
            zox_log(" ! [%i] has no ActiveState\n", i)
            continue;
        }
        if (zox_gett_value(child, ActiveState)) {
            if (i == index) return;
            zox_set(child, ActiveState, { 0 })
            break;
        }
    }
    zox_set(children->value[index], ActiveState, { 1 })
}

void player_action_ui_move(ecs_world_t *world, const ecs_entity_t player, const int direction) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    //find_child_with_tag(canvas, MenuGame, menu_game)
    //if (!menu_game) return;
    find_child_with_tag(canvas, MenuActions, actionbar)
    if (!actionbar) return;
    const Children *window_children = zox_get(actionbar, Children)
    if (window_children->length < 2) return;
    const Children *children = zox_get(window_children->value[1], Children)
    if (children->length == 0) return;
    int selected = -1;
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t child = children->value[i];
        if (!zox_valid(child)) continue;
        if (!zox_has(child, ActiveState)) {
            zox_log(" ! [%i] has no ActiveState\n", i)
            continue;
        }
        if (zox_gett_value(child, ActiveState)) {
            zox_set(child, ActiveState, { 0 })
            selected = i;
            break;
        }
    }
    if (selected == -1) selected = 0; // none selected
    selected += direction;
    if (selected == -1) selected = children->length - 1;
    else if (selected == children->length) selected = 0;
    zox_set(children->value[selected], ActiveState, { 1 })
}


unsigned char get_player_action_index(ecs_world_t *world, const ecs_entity_t player) {
    if (!player) {
        zox_log(" ! player invalid\n")
        return 0;
    }
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    if (!canvas) return 0;
    find_child_with_tag(canvas, MenuActions, actionbar)
    if (!actionbar) return 0;
    const Children *window_children = zox_get(actionbar, Children)
    if (window_children->length < 2) return 0;
    const Children *children = zox_get(window_children->value[1], Children)
    for (int i = 0; i < children->length; i++) {
        const ecs_entity_t child = children->value[i];
        if (!zox_valid(child) || !zox_has(child, ActiveState)) continue;
        if (zox_gett_value(child, ActiveState)) return i;
    }
    return 0;
}
