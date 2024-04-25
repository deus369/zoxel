const unsigned char player_uis_count = 3;
const int2 crosshair_size = (int2) { 64, 64 };
const color crosshair_color = (color) { 66, 35, 25, 25 };
ecs_entity_t game_ui = 0;
ecs_entity_t game_ui_touch = 0;
ecs_entity_t actionbar_ui = 0;
ecs_entity_t healthbar_2D = 0;
ecs_entity_t crosshair_ui = 0;

void spawn_in_game_ui_touch(ecs_world_t *world) {
    if (game_ui_touch) return;
    const unsigned char pause_button_size = 80;
    const ClickEvent on_pause_ui = (ClickEvent) { &button_event_pause_game };
    game_ui_touch = spawn_button_on_canvas(world, main_canvas, (int2) { pause_button_size, pause_button_size }, (byte2) { 8, 4 }, (color) { 77, 32, 44, 255 }, "P", pause_button_size, float2_zero, on_pause_ui);
    // zox_log("  > spawning touch ui [%lu]\n", game_ui_touch)
}

ecs_entity_t spawn_crosshair(ecs_world_t *world, const ecs_entity_t canvas, const  ecs_entity_t parent) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t crosshair_ui = spawn_element_basic(world, canvas, parent, int2_zero, crosshair_size, crosshair_size, float2_half, 1, int2_zero, canvas_size);
    zox_add_tag(crosshair_ui, FrameTexture)
    zox_set(crosshair_ui, FrameCorner, { 7 })
    zox_set(crosshair_ui, OutlineThickness, { 3 })
    zox_set(crosshair_ui, Color, { crosshair_color})
    zox_set(crosshair_ui, GenerateTexture, { 1 })
    zox_set(crosshair_ui, Seed, { 666 })
    return crosshair_ui;
}

// todo: move to actions module
ecs_entity_t spawn_actionbar(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int actions_count = 8;
    const int padding = 6;
    const int icon_size = 64;
    const int margins = 16;
    const color actionbar_color = (color) { 66, 35, 25, 255 };
    const float2 actionbar_anchor = (float2) { 0.5f, 0 };
    const int2 actionbar_size = (int2) { padding + (icon_size + padding) * actions_count + margins * 2, icon_size + padding * 2 };
    const int2 actionbar_position = (int2) { 0, 24 };
    const ecs_entity_t actionbar_ui = spawn_element(world, canvas, parent, actionbar_position, actionbar_size, actionbar_anchor, 1, actionbar_color, int2_half(canvas_size), canvas_size);
    zox_prefab_set(actionbar_ui, Children, { 0, NULL })
    Children *children = zox_get_mut(actionbar_ui, Children)
    resize_memory_component(Children, children, ecs_entity_t, actions_count)
    for (int i = 0; i < actions_count; i++) {
        const color action_color = (color) { 99, 11, 66, 255 };
        const int position_x = (int) ((i - (actions_count / 2) + 0.5f) * (icon_size + padding));
        const int2 action_icon_position = (int2) { position_x, 0 };
        const int2 action_icon_size = (int2) { icon_size, icon_size };
        children->value[i] = spawn_element(world, canvas, actionbar_ui, action_icon_position, action_icon_size, float2_half, 2, action_color, actionbar_position, actionbar_size);
    }
    zox_modified(actionbar_ui, Children)
    return actionbar_ui;
}

ecs_entity_t spawn_healthbar_on_canvas(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, const ecs_entity_t player) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const float2 elementbar2D_anchor = float2_top_left; // float2_half;
    const ecs_entity_t healthbar_2D = spawn_elementbar2D(world, player, canvas, parent, int2_zero, (int2) { 12, 8 }, elementbar2D_anchor, "-----", 18, 0, int2_half(canvas_size), canvas_size, canvas_size, 0);
    if (local_character3D) {
        const StatLinks *statLinks = zox_get(local_character3D, StatLinks)
        zox_prefab_set(healthbar_2D, StatLink, { statLinks->value[0] })
    }
    return healthbar_2D;
}

void spawn_in_game_ui(ecs_world_t *world, const ecs_entity_t player) {    // spawn game uis
    // ecs_entity_t player = main_player;
    const DeviceMode *deviceMode = zox_get(player, DeviceMode)
    unsigned char is_touch = deviceMode->value == zox_device_mode_touchscreen;
#ifdef zoxel_mouse_emulate_touch
    is_touch = 1;
#endif
    const ecs_entity_t canvas = main_canvas;
    if (is_touch) spawn_in_game_ui_touch(world);
    // actionbar_ui - spawn actionbar
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    // game_ui = spawn_element_on_canvas(world, canvas, canvas_size, int2_half(canvas_size), float2_half);
    game_ui = spawn_element_invisible_on_canvas(world, canvas, int2_zero, canvas_size, float2_zero);
    zox_set(game_ui, Color, {{ 255, 255, 255, 0 }})
    // ecs_new_w_pair(world, EcsIsA, prefab_element);
    zox_prefab_set(game_ui, Children, { 0, NULL })
    // spawn actionbar here
    actionbar_ui = spawn_actionbar(world, canvas, game_ui);
    healthbar_2D = spawn_healthbar_on_canvas(world, canvas, game_ui, player);
    crosshair_ui = spawn_crosshair(world, canvas, game_ui);
    // set children of game_ui
    Children *game_ui_children = zox_get_mut(game_ui, Children)
    add_to_Children(game_ui_children, actionbar_ui);
    add_to_Children(game_ui_children, healthbar_2D);
    add_to_Children(game_ui_children, crosshair_ui);
    zox_modified(actionbar_ui, Children)
}

void dispose_in_game_ui_touch(ecs_world_t *world) {
    zox_delete_and_set(game_ui_touch)
}

void dispose_in_game_ui(ecs_world_t *world, ecs_entity_t player) {
    dispose_in_game_ui_touch(world);
    zox_delete_and_set(game_ui)
}
