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
