// note on meta: since just spawned user item, we cant use it yet
void on_action_updated(
    ecs_world_t* world,
    ecs_entity_t e,
    byte index,
    ecs_entity_t action,
    ecs_entity_t meta
) {
    zox_geter(e, ElementLinks, elements);
    find_array_element_with_tag(elements, MenuActions, ui);
    if (!zox_valid(ui)) {
        return;
    }
    zox_geter(ui, Children, children);
    const ecs_entity_t menu_actions_body = children->value[1];
    zox_geter(menu_actions_body, Children, grand_children);
    const ecs_entity_t frame = grand_children->value[index];
    zox_geter(frame, Children, great_grand_children);
    const ecs_entity_t icon = great_grand_children->value[0];
    // remember: uses meta item for texture source here
    // zox_get_prefab(action, meta);
    set_icon_from_user_data(
        world,
        frame,
        icon,
        meta);
    set_icon_label_from_user_data(
        world,
        frame,
        meta);
    zox_set(icon, UserDataLink, { action });
}


// when action was updated
void on_action_updated_quantity(
    ecs_world_t *world,
    const ecs_entity_t character,
    const unsigned action_selected,
    const byte quantity
) {
    if (!zox_valid(character) || !zox_has(character, ElementLinks)) {
        return;
    }
    zox_geter(character, ElementLinks, elements);
    find_array_element_with_tag(elements, MenuActions, actionbar);
    if (actionbar) {
        zox_geter(actionbar, Children, menu_actions_children);
        const ecs_entity_t menu_actions_body = menu_actions_children->value[1];
        zox_geter(menu_actions_body, Children, menu_actions_body_children);
        const ecs_entity_t frame_action = menu_actions_body_children->value[action_selected];
        set_icon_label_from_user_data_quantity(world, frame_action, quantity);
    }
}