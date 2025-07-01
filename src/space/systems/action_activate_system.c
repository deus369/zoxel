#ifdef zox_mod_actions
// right click = place
// todo: use a state and implement results inside respective systems
// todo: move item activate to a seperate item system
void ActionActivateSystem(ecs_iter_t *it) {
    zox_field_world()
    zox_field_in(RaycastVoxelData, raycastVoxelDatas, 1)
    zox_field_out(ActionLinks, actionLinkss, 2)
    zox_field_out(TriggerActionB, triggerActionBs, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TriggerActionB, triggerActionBs, triggerActionB)
        if (!triggerActionB->value) {
            continue;
        }
        zox_field_e()
        zox_field_i(RaycastVoxelData, raycastVoxelDatas, raycastVoxelData)
        zox_field_o(ActionLinks, actionLinkss, actionLinks)
        const ecs_entity_t player = zox_get_value(e, PlayerLink)
        if (!player) {
            continue;
        }
        const byte action_selected = get_player_action_index(world, player);
        if (action_selected == 255) {
            triggerActionB->value = 0;
            continue; // no actionbar
        }
        if (action_selected >= actionLinks->length) {
            zox_log(" > action selected is out of bounds\n")
            triggerActionB->value = 0;
            continue;
        }
        const ecs_entity_t action_entity = actionLinks->value[action_selected];
        // no action assigned
        if (!action_entity) {
            triggerActionB->value = 0;
            continue;
        }
        if (zox_has(action_entity, Skill)) {
            // zox_log(" > toggling skill [%s]\n", zox_get_name(action_entity))
            if (zox_has(action_entity, Aura)) {
                // Toggle Skill
                zox_set(action_entity, SkillActive, { !zox_gett_value(action_entity, SkillActive) })
            } else if (zox_has(action_entity, Melee)) {
                zox_set(action_entity, SkillActive, { !zox_gett_value(action_entity, SkillActive) })
            } else {
                zox_log("! uknown skill type [%s]\n", zox_get_name(action_entity))
            }
        } else if (zox_has(action_entity, Item)) {
            // if item quantity > 0
            byte quantity = zox_get_value(action_entity, Quantity)
            if (quantity == 0) {
                zox_log(" ! cannot place with zero quantity")
            } else {
                byte is_use_quantity = 0;
                if (zox_has(action_entity, ItemBlock)) {
                    const ecs_entity_t block = zox_get_value(action_entity, BlockLink)
                    if (block) {
                        // todo: check placing on type and normal
                        const byte block_index = zox_get_value(block, BlockIndex)
                        raycast_action(world, raycastVoxelData, block_index, 1);
                        is_use_quantity = 1;
                    }
                }
                if (is_use_quantity) {
                    quantity--;
                    if (quantity > 0) {
                        zox_set(action_entity, Quantity, { quantity })
                        on_set_quantity(world, player, action_selected, quantity);
                    } else {
                        // set action to nullptr
                        // destroy entity
                        zox_delete(action_entity)
                        actionLinks->value[action_selected] = 0;
                        // now set ui
                        // now to effect ui!
                        const ecs_entity_t canvas = zox_get_value(player, CanvasLink)
                        find_child_with_tag(canvas, MenuActions, menu_actions)
                        if (menu_actions) {
                            const Children *menu_actions_children = zox_get(menu_actions, Children)
                            const ecs_entity_t menu_actions_body = menu_actions_children->value[1];
                            const Children *menu_actions_body_children = zox_get(menu_actions_body, Children)
                            const ecs_entity_t frame_action = menu_actions_body_children->value[action_selected];
                            const Children *frame_action_children = zox_get(frame_action, Children)
                            const ecs_entity_t icon_action = frame_action_children->value[0];
                            if (icon_action) {
                                // now reset icon
                                set_icon_from_user_data(world, frame_action, icon_action, 0); set_icon_label_from_user_data(world, frame_action, 0);
                            }
                            // zox_log(" > menu_actions found [%lu] user_item [%lu]\n", icon_action, meta_item_block) // base data off meta_item_block as item is still new
                        }
                    }
                }
            }
        } else {
            zox_log(" > action entity is not a block item\n")
        }
        triggerActionB->value = 0;
    }
} zox_declare_system(ActionActivateSystem)
#endif