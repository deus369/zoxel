// todo: find a way to hook this into the game uis
extern void button_event_switch_action(ecs_world_t *world, const ClickEventData *event);
extern void button_event_jump(ecs_world_t *world, const ClickEventData *event);
extern void button_event_attack(ecs_world_t *world, const ClickEventData *event);

ecs_entity_t spawn_prefab_menu_game_touch(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("menu_game_touch")
    zox_add_tag(e, MenuGameTouch)
    zox_prefab_set(e, AnchorSize, { float2_one })
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_button_game(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, const int2 canvas_size, const int2 position, const float2 anchor, const byte size, const ClickEvent event) {
    SpawnButton data = {
        .canvas = {
            .e = canvas,
            .size = canvas_size
        },
        .parent = {
            .e = parent,
            .size = canvas_size
        },
        .element = {
            .prefab = prefab_button,
            .position = position,
            .layer = 6,
            .anchor = anchor
        },
        .zext = {
            .text = " ",
            .font_size = size,
            .font_thickness = 4,
            .font_fill_color = default_font_fill_color,
            .font_outline_color = default_font_outline_color
        },
        .button = {
            .color = button_color,
            .prefab_zext = prefab_zext
        }};
    const ecs_entity_t e = spawn_button(world, &data);
    zox_set(e, ClickEvent, { event.value })
    return e;
}

ecs_entity_t spawn_menu_game_touch(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t e = spawn_element_invisible_on_canvas(world, prefab, canvas, int2_zero, canvas_size, float2_half);
    zox_name("menu_game_touch")
    const byte button_size = 140;
    const byte button_padding = 20;
    const byte bottom_padding = 60;
    zox_get_muter(e, Children, children)
#ifndef zox_disable_touch_buttons
    // left side - pause - switch weapon
    const int2 position_pause = (int2) {
        button_size,
        bottom_padding + (button_size + button_padding) * 1 };
    add_to_Children(children, spawn_button_game(world, canvas, e, canvas_size, position_pause, float2_zero, button_size, (ClickEvent) { &button_event_pause_game }));
    const int2 position_action_switch = (int2) {
        button_size,
        bottom_padding + (button_size + button_padding) * 2 };
    add_to_Children(children, spawn_button_game(world, canvas, e, canvas_size, position_action_switch, float2_zero, button_size, (ClickEvent) { &button_event_switch_action }));
    // right side - jump and attack
    const float2 anchor_right = (float2) { 1, 0 };
    const int2 position_jump = (int2) {
        - button_size - (button_size + button_padding) * 0,
        bottom_padding + (button_size + button_padding) * 1 };
    add_to_Children(children, spawn_button_game(world, canvas, e, canvas_size, position_jump, anchor_right, button_size, (ClickEvent) { &button_event_jump }));
    const int2 position_attack = (int2) {
        - button_size - (button_size + button_padding) * 0,
        bottom_padding + (button_size + button_padding) * 2 };
    add_to_Children(children, spawn_button_game(world, canvas, e, canvas_size, position_attack, anchor_right, button_size, (ClickEvent) { &button_event_attack }));
#endif
    return e;
}

// called from game state changes
void spawn_in_game_ui_touch(ecs_world_t *world, const ecs_entity_t canvas) {
    find_child_with_tag(canvas, MenuGameTouch, game_menu_touch)
    if (!game_menu_touch) spawn_menu_game_touch(world, prefab_menu_game_touch, canvas);
}

void dispose_game_menu_touch(ecs_world_t *world, const ecs_entity_t canvas) {
    find_child_with_tag(canvas, MenuGameTouch, game_menu_touch)
    if (game_menu_touch) zox_delete(game_menu_touch)
}