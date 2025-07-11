const byte max_stack_quantity = 255;

void on_overlap_pickup(
    ecs_world_t *world,
    const ecs_entity_t e,
    const ecs_entity_t user) {
    if (!zox_gett_value(e, PickedUp) && zox_has(user, PickUpperer)) {
        // zox_log(" > e [%lu] picked up by user [%lu]\n", e, user)
        if (zox_has(e, ItemLink)) {
            const ecs_entity_t item = zox_get_value(e, ItemLink)
            zox_get_muter(user, ActionLinks, actions)
            const ecs_entity_t meta_item_block = item;
            byte stack_index = 255;
            for (int i = 0; i < actions->length; i++) {
                if (actions->value[i] == 0) continue;
                zox_get_prefab(actions->value[i], item_prefab)
                if (item_prefab == meta_item_block) {
                    stack_index = i;
                    break;
                }
            }
            // stack first
            byte did_stack = 0;
            if (stack_index != 255) {
                const ecs_entity_t stack_item = actions->value[stack_index];
                byte quantity = zox_get_value(stack_item, Quantity)
                if (quantity != max_stack_quantity) {
                    quantity++;
                    zox_set(stack_item, Quantity, { quantity })
                    const ecs_entity_t player = zox_get_value(user, PlayerLink)
                    on_set_quantity(world, player, stack_index, quantity);
                    did_stack = 1;
                }
            }
            if (!did_stack) {
                // place as new
                byte action_index = 255;
                for (int i = 0; i < actions->length; i++) {
                    if (actions->value[i] == 0) {
                        action_index = i;
                        break;
                    }
                }
                // zox_get_prefab(item, meta_item_block)
                if (action_index == 255 || !meta_item_block) {
                    // zox_log(" ! cannot  pickup, full or meta_item_block is [%lu]\n", meta_item_block)
                    // cannot pickup!
                    return;
                }
                const ecs_entity_t user_item = spawn_user_item_quantity(world, meta_item_block, user, 1);
                actions->value[action_index] = user_item;
                // zox_log(" + adding item [%s] to actions slot [%i]\n", zox_get_name(item), action_index)
                // now to effect ui!

                // todo: use generic ElementLinks here to get actionbar
                const ecs_entity_t player = zox_get_value(user, PlayerLink)
                if (!player) return;
                const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
                find_child_with_tag(canvas, MenuActions, menu_actions)
                if (menu_actions) {
                    const Children *menu_actions_children = zox_get(menu_actions, Children)
                    const ecs_entity_t menu_actions_body = menu_actions_children->value[1];
                    const Children *menu_actions_body_children = zox_get(menu_actions_body, Children)
                    const ecs_entity_t frame_action = menu_actions_body_children->value[action_index];
                    const Children *frame_action_children = zox_get(frame_action, Children)
                    const ecs_entity_t icon_action = frame_action_children->value[0];
                    // remember: uses meta item for texture source here
                    set_icon_from_user_data(world, frame_action, icon_action, meta_item_block);
                    set_icon_label_from_user_data(world, frame_action, meta_item_block);
                    zox_set(icon_action, UserDataLink, { user_item })
                    // zox_log(" > menu_actions found [%lu] user_item [%lu]\n", icon_action, meta_item_block) // base data off meta_item_block as item is still new
                }
            }
        }
        // picked up!
        zox_set(e, PickedUp, { pickup_state_trigger })
        zox_set(e, CollisionDisabled, { 1 })
    }
}
