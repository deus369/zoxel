extern byte process_icon_type_action(ecs_world_t *world, const ecs_entity_t e);
extern void set_linked_action(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e);
extern void set_linked_item(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e);
extern void set_linked_skill(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e);

void UserIconClickSystem(ecs_iter_t *it) {
    if (!icon_mouse_follow) {
        return; // global icon_mouse_follow for now
    }
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(ClickState)
    zox_sys_in(IconType)
    zox_sys_in(IconIndex)
    zox_sys_out(UserDataLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(ClickState, clickState)
        zox_sys_i(IconType, iconType)
        zox_sys_i(IconIndex, iconIndex)
        zox_sys_o(UserDataLink, userDataLink)
        if (clickState->value != zox_click_state_clicked_this_frame) {
            continue;
        }
        byte icon_type = iconType->value;
        if (!icon_type) {
            continue;
        }
        zox_geter_value(icon_mouse_follow, UserDataLink, ecs_entity_t, mouse_data)
        byte mouse_data_empty = !zox_valid(mouse_data);
        byte clicked_data_empty = !zox_valid(userDataLink->value);
        if (mouse_data_empty && clicked_data_empty) {
            continue; // if both empty
        }
        // const byte is_mouse_empty = !mouse_data;
        // check matches mouse's icon type
        const byte mouse_icon_type = zox_get_value(icon_mouse_follow, IconType)
        if (mouse_icon_type > zox_icon_type_action && icon_type > zox_icon_type_action && icon_type != mouse_icon_type) {
            zox_log(" ! cannot place [%i] in [%i] slot\n", mouse_icon_type, icon_type)
            continue; // didn't match
        }
        ecs_entity_t character = 0;
        if (!mouse_data_empty) {
            character = zox_get_value(mouse_data, UserLink)
        } else if (!clicked_data_empty) {
            character = zox_get_value(userDataLink->value, UserLink)
        }
        // what icon frame is clicked?
        // swap with icon_mouse_follow:
        // q: is all data on icon??
        // swap icon with mouse icon
        if (!clicked_data_empty) {
            if (icon_type == zox_icon_type_action) {
                icon_type = process_icon_type_action(world, userDataLink->value);
            }
            zox_set(icon_mouse_follow, IconType, { icon_type })
        } else {
            zox_set(icon_mouse_follow, IconType, { 0 })
        }
        zox_set(icon_mouse_follow, UserDataLink, { userDataLink->value })
        zox_set(icon_mouse_follow, RenderDisabled, { clicked_data_empty })
        userDataLink->value = mouse_data;
        // zox_log("swapping textures\n")
        swap_textures(world, e, icon_mouse_follow);

        // remember: this is a temporary fix for: bug where e doesn't clear on picked up items
        const ecs_entity_t frame = zox_get_value(e, ParentLink)
        if (mouse_data_empty) {
            set_icon_from_user_data(world, frame, e, 0);
        }
        set_icon_label_from_user_data(world, frame, mouse_data);

        // new data placed in mouse_data
        // use iconType->value and iconIndex->value to set data on character
        // how to get character from icon? UserLink!

        // === Base on Frame clicked ===
        if (iconType->value == zox_icon_type_action) {
            // zox_log(" + character [%lu] setting [%s] [%i]\n", character, "action", iconIndex->value)
            set_linked_action(world, character, iconIndex->value, mouse_data);
        } else if (iconType->value == zox_icon_type_skill) {
            // zox_log(" + character [%lu] setting [%s] [%i]\n", character, "skill", iconIndex->value)
            set_linked_skill(world, character, iconIndex->value, mouse_data);
        } else if (iconType->value == zox_icon_type_item) {
            // zox_log(" + character [%lu] setting [%s] [%i]\n", character, "item", iconIndex->value)
            set_linked_item(world, character, iconIndex->value, mouse_data);
        }

        // clear the tooltip when picked up icon
        if (!clicked_data_empty) {
            const ecs_entity_t canvas = zox_get_value(e, CanvasLink)
            if (zox_valid(canvas)) {
                find_child_with_tag(canvas, Tooltip, tooltip)
                if (zox_valid(tooltip)) {
                    set_entity_text(world, tooltip, "");
                }
            }
        }
    }
} zox_declare_system(UserIconClickSystem)