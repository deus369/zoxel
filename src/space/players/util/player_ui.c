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

void spawn_in_game_ui(ecs_world_t *world, ecs_entity_t player) {    // spawn game uis
    // ecs_entity_t player = main_player;
    const DeviceMode *deviceMode = zox_get(player, DeviceMode)
    unsigned char is_touch = deviceMode->value == zox_device_mode_touchscreen;
#ifdef zoxel_mouse_emulate_touch
    is_touch = 1;
#endif
    ecs_entity_t canvas = main_canvas;
    if (is_touch) spawn_in_game_ui_touch(world);
    // actionbar_ui - spawn actionbar
    game_ui = ecs_new_w_pair(world, EcsIsA, prefab_element);
    zox_prefab_set(game_ui, Children, { 0, NULL })
    // spawn actionbar here
    int actions_count = 8;
    int padding = 6;
    int icon_size = 64;
    int margins = 16;
    actionbar_ui = spawn_element_on_canvas(world, canvas, (int2) { 0, 24 }, (int2) { padding + (icon_size + padding) * actions_count + margins * 2, icon_size + padding * 2 }, (float2) { 0.5f, 0 });
    zox_prefab_set(actionbar_ui, Children, { 0, NULL })
    Children *children = zox_get_mut(actionbar_ui, Children)
    resize_memory_component(Children, children, ecs_entity_t, actions_count)
    for (int i = 0; i < actions_count; i++) {
        const color action_color = (color) { 99, 11, 66, 255 };
        int position_x = (int) ((i - (actions_count / 2) + 0.5f) * (icon_size + padding));
        children->value[i] = spawn_element(world, actionbar_ui, canvas, (int2) { position_x, 0 }, (int2) { icon_size, icon_size }, float2_half, 1, action_color);
    }
    zox_modified(actionbar_ui, Children)
    // statbar testing
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    float2 elementbar2D_anchor = float2_top_left; // float2_half;
    healthbar_2D = spawn_elementbar2D(world, player, canvas, canvas, int2_zero, (int2) { 12, 8 }, elementbar2D_anchor, "-----", 18, 0, int2_half(canvas_size), canvas_size, canvas_size, 0);
    if (local_character3D) {
        const StatLinks *statLinks = zox_get(local_character3D, StatLinks)
        zox_prefab_set(healthbar_2D, StatLink, { statLinks->value[0] })
    }
    // spawn crosshair
    crosshair_ui = spawn_on_canvas_element_basic(world, canvas, int2_zero, crosshair_size, crosshair_size, (float2) { 0.5f, 0.5f });
    zox_add_tag(crosshair_ui, FrameTexture)
    zox_set(crosshair_ui, FrameCorner, { 7 })
    zox_set(crosshair_ui, OutlineThickness, { 3 })
    zox_set(crosshair_ui, Color, { crosshair_color})
    zox_set(crosshair_ui, GenerateTexture, { 1 })
    zox_set(crosshair_ui, Seed, { 666 })
    // set children of game_ui
    Children *game_ui_children = zox_get_mut(game_ui, Children)
    resize_memory_component(Children, game_ui_children, ecs_entity_t, player_uis_count)
    game_ui_children->value[0] = actionbar_ui;
    game_ui_children->value[1] = healthbar_2D;
    game_ui_children->value[2] = crosshair_ui;
    zox_modified(actionbar_ui, Children)
}

void dispose_in_game_ui_touch(ecs_world_t *world) {
    zox_delete_and_set(game_ui_touch)
}

void dispose_in_game_ui(ecs_world_t *world, ecs_entity_t player) {
    // todo: get ui links
    dispose_in_game_ui_touch(world);
    zox_delete_and_set(game_ui)
}
