// todo: move to actions module
ecs_entity_t spawn_prefab_actionbar(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("actionbar")
    zox_add_tag(e, Actionbar)
    zox_prefab_add(e, Children)
    return e;
}

ecs_entity_t spawn_actionbar(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t canvas, const ecs_entity_t parent) {
    const int2 canvas_size = zox_get_value(canvas, PixelSize)
    const int actions_count = 8;
    const int padding_x = 6;
    const int padding_y = 12;
    const int icon_size = 64;
    const int margins = 16;
    const color actionbar_color = (color) { 66, 35, 25, 255 };
    const float2 actionbar_anchor = (float2) { 0.5f, 0 };
    const int2 actionbar_size = (int2) { padding_x + (icon_size + padding_x) * actions_count + margins * 2, icon_size + padding_y * 2 };
    const int2 actionbar_position = (int2) { 0, 24 };
    const ecs_entity_t actionbar_ui = spawn_element(world, prefab, canvas, parent, actionbar_position, actionbar_size, actionbar_anchor, 1, actionbar_color, int2_half(canvas_size), canvas_size);
    zox_prefab_add(actionbar_ui, Children)
    Children *children = zox_get_mut(actionbar_ui, Children)
    resize_memory_component(Children, children, ecs_entity_t, actions_count)
    for (int i = 0; i < actions_count; i++) {
        const color action_color = (color) { 99, 11, 66, 255 };
        const int position_x = (int) ((i - (actions_count / 2) + 0.5f) * (icon_size + padding_x));
        const int2 action_icon_position = (int2) { position_x, 0 };
        const int2 action_icon_size = (int2) { icon_size, icon_size };
        children->value[i] = spawn_element(world, prefab_icon_frame_action, canvas, actionbar_ui, action_icon_position, action_icon_size, float2_half, 2, action_color, actionbar_position, actionbar_size);
        if (i == 0) zox_set(children->value[i], ActiveState, { 1 }) // first one should be active
    }
    zox_modified(actionbar_ui, Children)
    return actionbar_ui;
}
