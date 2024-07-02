void swap_textures(ecs_world_t *world, const ecs_entity_t e1, const ecs_entity_t e2) {
    zox_get_muter(e1, TextureData, texture_a)
    zox_get_muter(e1, TextureSize, texture_size_a)
    zox_get_muter(e2, TextureData, texture_b)
    zox_get_muter(e2, TextureSize, texture_size_b)
    const TextureData temp_data = (TextureData) { texture_a->length, texture_a->value };
    const int2 temp_size = texture_size_a->value;
    texture_a->value = texture_b->value;
    texture_a->length = texture_b->length;
    texture_size_a->value = texture_size_b->value;
    texture_b->value = temp_data.value;
    texture_b->length = temp_data.length;
    texture_size_b->value = temp_size;
    zox_set(e1, TextureDirty, { 1 })
    zox_set(e2, TextureDirty, { 1 })
}

extern unsigned char process_icon_type_action(ecs_world_t *world, const ecs_entity_t e);
extern void set_linked_action(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e);
extern void set_linked_item(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e);
extern void set_linked_skill(ecs_world_t *world, const ecs_entity_t user, const int index, const ecs_entity_t e);

void UserIconClickSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ClickState, clickStates, 1)
    zox_field_in(IconType, iconTypes, 2)
    zox_field_in(IconIndex, iconIndexs, 3)
    zox_field_out(UserDataLink, userDataLinks, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ClickState, clickStates, clickState)
        if (clickState->value != zox_click_state_clicked_this_frame) continue;
        zox_field_o(UserDataLink, userDataLinks, userDataLink)
        zox_field_i(IconType, iconTypes, iconType)
        zox_field_i(IconIndex, iconIndexs, iconIndex)
        zox_field_e()
        unsigned char icon_type = iconType->value;
        if (icon_type == 0) continue;
        const ecs_entity_t mouse_data = zox_get_value(icon_mouse_follow, UserDataLink)
        if (!mouse_data && !userDataLink->value) continue; // if both empty
        const unsigned char is_clicked_empty = !userDataLink->value;
        // const unsigned char is_mouse_empty = !mouse_data;
        // check matches mouse's icon type
        const unsigned char mouse_icon_type = zox_get_value(icon_mouse_follow, IconType)
        if (mouse_icon_type > zox_icon_type_action && icon_type > zox_icon_type_action && icon_type != mouse_icon_type) {
            zox_log(" ! cannot place [%i] in [%i] slot\n", mouse_icon_type, icon_type)
            continue; // didn't match
        }
        ecs_entity_t character = 0;
        if (mouse_data) character = zox_get_value(mouse_data, UserLink)
        if (userDataLink->value) character = zox_get_value(userDataLink->value, UserLink)
        // what icon frame is clicked?
        // const ecs_entity_t icon_frame = zox_get_value(e, ParentLink)
        // swap with icon_mouse_follow:
        // q: is all data on icon??
        // swap icon with mouse icon
        if (!is_clicked_empty) {
            if (icon_type == zox_icon_type_action) icon_type = process_icon_type_action(world, userDataLink->value);
            zox_set(icon_mouse_follow, IconType, { icon_type })
        } else {
            zox_set(icon_mouse_follow, IconType, { 0 })
        }
        zox_set(icon_mouse_follow, UserDataLink, { userDataLink->value })
        zox_set(icon_mouse_follow, RenderDisabled, { is_clicked_empty })
        userDataLink->value = mouse_data;
        swap_textures(world, e, icon_mouse_follow);
        // new data placed in mouse_data
        // use iconType->value and iconIndex->value to set data on character
        // how to get character from icon? UserLink!
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
    }
} zox_declare_system(UserIconClickSystem)

// add_mouse_follow_components(world, e);
// zox_add_tag(e, MouseElement)
// zox_set(e, MouseLink, { mouse_entity })
/*zox_get_muter(zox_gett_value(e, ParentLink), Children, frame_children)
frame_children->value[0] = icon_mouse_follow;
zox_set(e, ParentLink, { canvasLink->value })
// add to canvas?
zox_get_muter(zox_gett_value(e, ParentLink), Children, canvas_children)
add_to_Children(canvas_children, e);*/
