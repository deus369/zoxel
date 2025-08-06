const byte max_stack_quantity = 255;


void on_overlap_pickup(
    ecs_world_t *world,
    const ecs_entity_t e,
    const ecs_entity_t user
) {
    if (!zox_gett_value(e, PickedUp) && zox_has(user, PickUpperer)) {
        // zox_log(" > e [%lu] picked up by user [%lu]\n", e, user)
        if (zox_has(e, ItemLink)) {
            const ecs_entity_t item = zox_get_value(e, ItemLink);
            zox_get_muter(user, ActionLinks, actions)
            const ecs_entity_t meta_item_block = item;
            byte stack_index = 255;
            for (int i = 0; i < actions->length; i++) {
                if (actions->value[i] == 0) {
                    continue;
                }
                zox_get_prefab(actions->value[i], item_prefab);
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
                    zox_set(stack_item, Quantity, { quantity });
                    on_action_updated_quantity(world, user, stack_index, quantity);
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
                on_action_updated(world, user, action_index, user_item, item);
            }
        }
        // picked up!
        zox_set(e, PickedUp, { pickup_state_trigger });
        zox_set(e, CollisionDisabled, { 1 });
    }
}
