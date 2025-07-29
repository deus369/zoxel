#ifdef zox_mod_actions
// right click = place
// todo: use a state and implement results inside respective systems
// todo: move item activate to a seperate item system
void ActionActivateSystem(ecs_iter_t *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(RaycastVoxelData)
    zox_sys_out(ActionLinks)
    zox_sys_out(TriggerActionB)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(RaycastVoxelData, raycastVoxelData)
        zox_sys_o(ActionLinks, actions)
        zox_sys_o(TriggerActionB, triggerActionB)
        if (!triggerActionB->value) {
            continue;
        }

        // todo: action index should be based on character not player ui... omg
        const ecs_entity_t player = zox_get_value(e, PlayerLink)
        if (!zox_valid(player)) {
            continue;
        }
        const byte action_selected = get_player_action_index(world, player);


        if (action_selected == 255) {
            triggerActionB->value = 0;
            continue; // no actionbar
        }
        if (action_selected >= actions->length) {
            zox_log(" > action selected is out of bounds\n")
            triggerActionB->value = 0;
            continue;
        }
        const ecs_entity_t action = actions->value[action_selected];
        // no action assigned
        if (!zox_valid(action)) {
            triggerActionB->value = 0;
            continue;
        }
        if (zox_has(action, Skill)) {
            // zox_log(" > toggling skill [%s]\n", zox_get_name(action))
            if (zox_has(action, Aura)) {
                // Toggle Skill
                zox_set(action, SkillActive, { !zox_gett_value(action, SkillActive) })
                spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[28], 0.6, get_volume_sfx());
            } else if (zox_has(action, Melee)) {
                zox_set(action, SkillActive, { !zox_gett_value(action, SkillActive) })
            } else {
                zox_log("! uknown skill type [%s]\n", zox_get_name(action))
            }
        } else if (zox_has(action, Item)) {
            // if item can place?!?!
            // if item quantity > 0
            byte quantity = zox_get_value(action, Quantity)
            if (quantity == 0) {
                zox_log(" ! cannot place with zero quantity")
            } else {
                byte is_use_quantity = 0;
                if (zox_has(action, ItemBlock)) {
                    const ecs_entity_t block = zox_get_value(action, BlockLink)
                    if (zox_valid(block) && zox_has(block, BlockIndex)) {
                        // zox_log("! placing block %s", zox_get_name(block))
                        // todo: check placing on type and normal
                        const byte block_index = zox_get_value(block, BlockIndex)

                        raycast_action(world, raycastVoxelData, block_index, 1);

                        is_use_quantity = 1;
                    } else {
                        zox_log_error("invalid block [%s]", zox_get_name(block))
                    }
                }
                if (is_use_quantity) {
                    quantity--;
                    // place block sound
                    spawn_sound_generated(world, prefab_sound_generated, instrument_violin, note_frequencies[30 + rand() % 6], 0.6, 1.8f * get_volume_sfx());

                    if (quantity > 0) {
                        zox_set(action, Quantity, { quantity })
                        on_set_quantity(world, player, action_selected, quantity);
                    } else {
                        // set action to nullptr
                        // destroy entity
                        zox_delete(action)
                        actions->value[action_selected] = 0;
                        // now set ui
                        // now to effect ui!
                        if (zox_has(e, ElementLinks)) {
                            zox_geter(e, ElementLinks, elements)
                            // zox_log("+ character has element links [%i]", elements->length)
                            // find_child_with_tag(canvas, MenuActions, menu_actions)
                            find_array_component_with_tag(elements, MenuActions, actionbar)
                            if (zox_valid(actionbar)) {
                                // zox_log("+ character has a actionbar")
                                zox_geter(actionbar, Children, menu_actions_children)
                                if (menu_actions_children->length >= 2) {
                                    const ecs_entity_t menu_actions_body = menu_actions_children->value[1];
                                    if (!zox_valid(menu_actions_body)) {
                                        zox_log_error("invalid menu_actions_body")
                                        continue;
                                    }
                                    zox_geter(menu_actions_body, Children, menu_actions_body_children)

                                    const ecs_entity_t frame_action = menu_actions_body_children->value[action_selected];
                                    if (!zox_valid(frame_action)) {
                                        zox_log_error("invalid frame_action")
                                        continue;
                                    }

                                    zox_geter(frame_action, Children, frame_action_children)

                                    const ecs_entity_t icon_action = frame_action_children->value[0];
                                    if (!zox_valid(icon_action)) {
                                        zox_log_error("invalid icon_action")
                                        continue;
                                    }

                                    // now reset icon
                                    // zox_log_error("resetting action icon [%s]", zox_get_name(icon_action))
                                    set_icon_from_user_data(world, frame_action,
                                        icon_action,
                                        0);
                                    set_icon_label_from_user_data(world,
                                        frame_action,
                                        0);
                                }
                            } else {
                                zox_log_error("character has no actionbar")
                            }
                        } else {
                            zox_log_error("character has no element links")
                        }
                    }
                }
            }
        } else {
            zox_log_error("action is not a block item [%s]", zox_get_name(action))
        }
        triggerActionB->value = 0;
    }
} zox_declare_system(ActionActivateSystem)
#endif