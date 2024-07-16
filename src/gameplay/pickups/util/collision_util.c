void on_overlap_pickup(ecs_world_t *world, const ecs_entity_t e, const ecs_entity_t e2) {
    if (!zox_gett_value(e, PickedUp) && zox_has(e2, PickUpperer)) {
        // zox_log(" > e [%lu] picked up by e2 [%lu]\n", e, e2)
        if (zox_has(e, ItemLink)) {
            const ecs_entity_t item = zox_get_value(e, ItemLink)
            zox_get_muter(e2, ActionLinks, actions)
            unsigned char action_index = 255;
            for (int i = 0; i < actions->length; i++) {
                if (actions->value[i] == 0) {
                    action_index = i;
                    break;
                }
            }
            const ecs_entity_t meta_item_block = item;
            // zox_get_prefab(item, meta_item_block)
            if (action_index == 255 || !meta_item_block) {
                // zox_log(" ! cannot  pickup, full or meta_item_block is [%lu]\n", meta_item_block)
                // cannot pickup!
                return;
            }
            const ecs_entity_t user_item = spawn_user_item(world, meta_item_block, e2);
            actions->value[action_index] = user_item;
            // zox_log(" + adding item [%s] to actions slot [%i]\n", zox_get_name(item), action_index)
            // now to effect ui!
            const ecs_entity_t player = zox_get_value(e2, PlayerLink)
            const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
            find_child_with_tag(canvas, MenuActions, menu_actions)
            if (menu_actions) {
                const Children *menu_actions_children = zox_get(menu_actions, Children)
                const ecs_entity_t menu_actions_body = menu_actions_children->value[1];
                const Children *menu_actions_body_children = zox_get(menu_actions_body, Children)
                const ecs_entity_t frame_action = menu_actions_body_children->value[action_index];
                const Children *frame_action_children = zox_get(frame_action, Children)
                const ecs_entity_t icon_action = frame_action_children->value[0];
                zox_set(icon_action, UserDataLink, { user_item })
                set_icon_from_user_data(world, icon_action, meta_item_block);
                // zox_log(" > menu_actions found [%lu] user_item [%lu]\n", icon_action, meta_item_block) // base data off meta_item_block as item is still new
            }
        }
        // picked up!
        zox_set(e, PickedUp, { pickup_state_trigger })
        zox_set(e, CollisionDisabled, { 1 })
    }
}
