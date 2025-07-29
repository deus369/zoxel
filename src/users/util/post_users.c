// todo: refactor how these work so i can just hook into user events

void on_set_quantity(ecs_world_t *world,
    const ecs_entity_t character,
    const unsigned action_selected,
    const byte quantity)
{
    if (!zox_valid(character) || !zox_has(character, ElementLinks)) {
        return;
    }
    zox_geter(character, ElementLinks, elements)
    find_array_component_with_tag(elements, MenuActions, actionbar)
    if (actionbar) {
        const Children *menu_actions_children = zox_get(actionbar, Children)
        const ecs_entity_t menu_actions_body = menu_actions_children->value[1];
        const Children *menu_actions_body_children = zox_get(menu_actions_body, Children)
        const ecs_entity_t frame_action = menu_actions_body_children->value[action_selected];
        set_icon_label_from_user_data_quantity(world, frame_action, quantity);
    }
}

/*void set_taskbar_icon_active(ecs_world_t *world, const ecs_entity_t canvas, const ecs_entity_t frame, const int i) {
    if (i == taskbar_items) { if_has_child_with_tag(canvas, MenuItems) zox_set(frame, ActiveState, { 1 }) }
    else if (i == taskbar_skills) { if_has_child_with_tag(canvas, MenuSkills) zox_set(frame, ActiveState, { 1 }) }
    else if (i == taskbar_quests) { if_has_child_with_tag(canvas, MenuQuests) zox_set(frame, ActiveState, { 1 }) }
    else if (i == taskbar_stats) { if_has_child_with_tag(canvas, MenuStats) zox_set(frame, ActiveState, { 1 }) }
    else if (i == taskbar_actions) { if_has_child_with_tag(canvas, MenuActions) zox_set(frame, ActiveState, { 1 }) }
}

void on_toggle_taskbar_icon(ecs_world_t *world, const ClickEventData *event) {
    const ecs_entity_t canvas = zox_get_value(event->clicker, CanvasLink)
    const byte index = zox_get_value(event->clicked, IconIndex)
    if (index == taskbar_menu) toggle_ui_with_tag_e(spawn_menu_paused_player, MenuPaused, event->clicker)
    else if (index == taskbar_stats) toggle_ui_with_tag_e(spawn_menu_stats_player, MenuStats, event->clicker)
    else if (index == taskbar_items) toggle_ui_with_tag_e(spawn_menu_items_player, MenuItems, event->clicker)
    else if (index == taskbar_skills) toggle_ui_with_tag_e(spawn_menu_skills_player, MenuSkills, event->clicker)
    else if (index == taskbar_quests) toggle_ui_with_tag_e(spawn_menu_quests_player, MenuQuests, event->clicker)
    // testing - spawn_actionbar_player
    else if (index == taskbar_actions) toggle_ui_with_tag_e(spawn_menu_actions_player, MenuActions, event->clicker)
    else return; // nothing to open
    // toggle frames active state
    const ecs_entity_t frame = zox_get_value(event->clicked, ParentLink)
    if (!frame || !zox_has(frame, ActiveState)) {
        zox_log(" ! invalid frame\n")
        return;
    }
    zox_set(frame, ActiveState, { !zox_gett_value(frame, ActiveState) })
}
*/