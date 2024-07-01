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

void UserIconClickSystem(ecs_iter_t *it) {
    zox_iter_world()
    zox_field_in(ClickState, clickStates, 1)
    zox_field_in(CanvasLink, canvasLinks, 2)
    zox_field_out(UserDataLink, userDataLinks, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(ClickState, clickStates, clickState)
        if (clickState->value != zox_click_state_clicked_this_frame) continue;
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        zox_field_o(UserDataLink, userDataLinks, userDataLink)
        zox_field_e()
        // swap with icon_mouse_follow:
        // q: is all data on icon??
        // swap icon with mouse icon
        const ecs_entity_t previous_data = zox_get_value(icon_mouse_follow, UserDataLink)
        zox_set(icon_mouse_follow, UserDataLink, { userDataLink->value })
        userDataLink->value = previous_data;
        swap_textures(world, e, icon_mouse_follow);

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
