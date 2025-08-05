ecs_entity_t spawn_menu_game_touch(
    ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t player,
    const ecs_entity_t canvas
) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t e = spawn_layout2_on_canvas(world, prefab, canvas, int2_zero, canvas_size, float2_half);
    zox_name("menu_game_touch")
    const byte button_size = 140;
    const byte button_padding = 20;
    const byte bottom_padding = 60;

    Children children = (Children) { };
#ifndef zox_disable_touch_buttons
    // left side - pause - switch weapon
    const int2 position_pause = (int2) {
        button_size,
        bottom_padding + (button_size + button_padding) * 1 };
    add_to_Children(&children, spawn_button_game(world, canvas, e, canvas_size, position_pause, float2_zero, button_size, (ClickEvent) { &button_event_pause_game }));
#ifdef spawn_actions_on_touch_menu
    const int2 position_action_switch = (int2) {
        button_size,
        bottom_padding + (button_size + button_padding) * 2 };
    add_to_Children(&children, spawn_button_game(world, canvas, e, canvas_size, position_action_switch, float2_zero, button_size, (ClickEvent) { &button_event_switch_action }));
#endif
    // right side - jump and attack
    const float2 anchor_right = (float2) { 1, 0 };
    const int2 position_jump = (int2) {
        - button_size - (button_size + button_padding) * 0,
        bottom_padding + (button_size + button_padding) * 1 };
    add_to_Children(&children, spawn_button_game(world, canvas, e, canvas_size, position_jump, anchor_right, button_size, (ClickEvent) { &button_event_jump }));
    const int2 position_attack = (int2) {
        - button_size - (button_size + button_padding) * 0,
        bottom_padding + (button_size + button_padding) * 2
    };
    add_to_Children(&children, spawn_button_game(world, canvas, e, canvas_size, position_attack, anchor_right, button_size, (ClickEvent) { &button_event_attack }));
#endif
    // link to character
    zox_geter(player, CharacterLink, characterLink)
    zox_get_muter(characterLink->value, ElementLinks, elementLinks)
    add_to_ElementLinks(elementLinks, e);
    zox_set(e, ElementHolder, { characterLink->value })
    zox_set_ptr(e, Children, children);
    return e;
}

// called from game state changes
void spawn_in_game_ui_touch(
    ecs_world_t *world,
    const ecs_entity_t player,
    const ecs_entity_t canvas
) {
    if (!zox_valid(canvas)) {
        return;
    }
    find_child_with_tag(canvas, MenuGameTouch, game_menu_touch)
    if (!zox_valid(game_menu_touch)) {
        spawn_menu_game_touch(world, prefab_menu_game_touch, player, canvas);
    }
}

void dispose_menu_game_touch(
    ecs_world_t *world,
    const ecs_entity_t player
) {
    if (!zox_valid(player)) {
        return;
    }
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    if (!zox_valid(canvas)) {
        return;
    }
    find_child_with_tag(canvas, MenuGameTouch, game_menu_touch)
    if (zox_valid(game_menu_touch)) {
        zox_delete(game_menu_touch)
    }
}