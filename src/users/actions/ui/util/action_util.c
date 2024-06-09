void set_player_action(ecs_world_t *world, const ecs_entity_t player, const unsigned char index) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuGame, menu_game)
    if (!menu_game) return;
    find_child_with_tag(menu_game, Actionbar, actionbar)
    if (!actionbar) return;
    const Children *children = zox_get(actionbar, Children)
    if (index >= children->length) return;
    // deselect first
    for (int i = 0; i < children->length; i++) {
        if (zox_gett_value(children->value[i], ActiveState)) {
            if (i == index) return;
            zox_set(children->value[i], ActiveState, { 0 })
            break;
        }
    }
    zox_set(children->value[index], ActiveState, { 1 })
}

void player_action_ui_move(ecs_world_t *world, const ecs_entity_t player, const int direction) {
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuGame, menu_game)
    if (!menu_game) return;
    find_child_with_tag(menu_game, Actionbar, actionbar)
    if (!actionbar) return;
    const Children *children = zox_get(actionbar, Children)
    if (children->length == 0) return;
    int selected = -1;
    for (int i = 0; i < children->length; i++) {
        if (zox_gett_value(children->value[i], ActiveState)) {
            zox_set(children->value[i], ActiveState, { 0 })
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
