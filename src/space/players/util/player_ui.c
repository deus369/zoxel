const unsigned char player_uis_count = 3;
const int2 crosshair_texture_size = (int2) { 24, 24 };
const int2 crosshair_pixel_size = (int2) { 48, 48 };
const color crosshair_color = (color) { 33, 122, 122, 13 };
ecs_entity_t game_ui_touch = 0;

void spawn_in_game_ui_touch(ecs_world_t *world, const ecs_entity_t canvas) {
    if (game_ui_touch) return;
    const unsigned char pause_button_size = 80;
    const ClickEvent on_pause_ui = (ClickEvent) { &button_event_pause_game };
    game_ui_touch = spawn_button_on_canvas(world, canvas, (int2) { pause_button_size, pause_button_size }, (byte2) { 8, 4 }, (color) { 77, 32, 44, 255 }, "P", pause_button_size, float2_zero, on_pause_ui);
    // zox_log("  > spawning touch ui [%lu]\n", game_ui_touch)
}

ecs_entity_t spawn_crosshair(ecs_world_t *world, const ecs_entity_t canvas, const  ecs_entity_t parent) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t crosshair_ui = spawn_element_basic(world, canvas, parent, int2_zero, crosshair_pixel_size, crosshair_texture_size, float2_half, 1, int2_half(canvas_size), canvas_size);
    zox_add_tag(crosshair_ui, FrameTexture)
    zox_set(crosshair_ui, FrameCorner, { 7 })
    zox_set(crosshair_ui, OutlineThickness, { 3 })
    zox_set(crosshair_ui, Color, { crosshair_color})
    zox_set(crosshair_ui, GenerateTexture, { 1 })
    zox_set(crosshair_ui, Seed, { 666 })
    // zox_log(" > crosshair [%lu]\n", crosshair_ui)
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
    // zox_log(" > actionbar_ui [%lu]\n", actionbar_ui)
    for (int i = 0; i < actions_count; i++) {
        const color action_color = (color) { 99, 11, 66, 255 };
        const int position_x = (int) ((i - (actions_count / 2) + 0.5f) * (icon_size + padding));
        const int2 action_icon_position = (int2) { position_x, 0 };
        const int2 action_icon_size = (int2) { icon_size, icon_size };
        children->value[i] = spawn_element(world, canvas, actionbar_ui, action_icon_position, action_icon_size, float2_half, 2, action_color, actionbar_position, actionbar_size);
        // zox_log("   > actionbar_icon [%lu]\n", children->value[i])
    }
    zox_modified(actionbar_ui, Children)
    return actionbar_ui;
}

ecs_entity_t spawn_healthbar_on_canvas(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t parent, const ecs_entity_t player, const ecs_entity_2 character_group) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const float2 elementbar2D_anchor = float2_top_left;
    const int2 healthbar_size = (int2) { 12, 8 };
    const ecs_entity_t healthbar_2D = spawn_elementbar2D(world, player, canvas, parent, int2_zero, healthbar_size, elementbar2D_anchor, "-----", 18, 0, int2_half(canvas_size), canvas_size, canvas_size, 0);
    // const ecs_entity_t character = zox_get_value(player, CharacterLink)
    if (character_group.x) {
        // const StatLinks *statLinks = zox_get(character, StatLinks)
        zox_set(healthbar_2D, StatLink, { character_group.y })
    }
    return healthbar_2D;
}

void spawn_in_game_ui(ecs_world_t *world, const ecs_entity_t player, const ecs_entity_2 character_group) {
    const DeviceMode *deviceMode = zox_get(player, DeviceMode)
    unsigned char is_touch = deviceMode->value == zox_device_mode_touchscreen;
#ifdef zoxel_mouse_emulate_touch
    is_touch = 1;
#endif
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    if (is_touch) spawn_in_game_ui_touch(world, canvas);
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const ecs_entity_t game_ui = spawn_element_invisible_on_canvas(world, canvas, int2_zero, canvas_size, float2_half);
    zox_add_tag(game_ui, MenuInGame)
    zox_prefab_set(game_ui, AnchorSize, { (float2) { 1, 1 }})
    zox_prefab_set(game_ui, Children, { 0, NULL })
    on_child_added(world, canvas, game_ui);
    Children *game_ui_children = zox_get_mut(game_ui, Children)
    add_to_Children(game_ui_children, spawn_crosshair(world, canvas, game_ui));
    add_to_Children(game_ui_children, spawn_actionbar(world, canvas, game_ui));
    add_to_Children(game_ui_children, spawn_healthbar_on_canvas(world, canvas, game_ui, player, character_group));
    zox_modified(game_ui, Children)
}

void dispose_in_game_ui_touch(ecs_world_t *world) {
    zox_delete_and_set(game_ui_touch)
}

void dispose_in_game_ui(ecs_world_t *world, ecs_entity_t player) {
    dispose_in_game_ui_touch(world);
    const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
    find_child_with_tag(canvas, MenuInGame, game_ui)
    zox_delete(game_ui)
}
