// make everything a child of realm
extern ecs_entity_t local_realm;

void add_all_prefabs(ecs_world_t *world,
    ecs_entity_t_array_d* entities,
    text_group_dynamic_array_d* labels,
    const ecs_entity_t canvas)
{
    ecs_entity_t realm = local_realm;
    // prefabs
    add_entity_to_labels(world, prefab_app, labels, entities, 0);
    add_entity_to_labels(world, prefab_window, labels, entities, 0);
    add_entity_to_labels(world, prefab_button, labels, entities, 0);
    add_entity_to_labels(world, prefab_zext, labels, entities, 0);
    add_entity_to_labels(world, prefab_zigel, labels, entities, 0);
    add_entity_to_labels(world, prefab_realm, labels, entities, 0);
    add_entity_to_labels(world, prefab_block, labels, entities, 0);
    add_entity_to_labels(world, prefab_texture, labels, entities, 0);
    // add game entities
    add_entity_to_labels(world, realm, labels, entities, 0);
    add_to_labels_voxel_links(world, realm, labels, entities, 0);
#ifdef zox_mod_stats
    add_to_labels_stat_links(world, realm, labels, entities, 0);
#endif
    add_entity_to_labels(world, local_music, labels, entities, 0);
    for (int k = 0; k < main_cameras_count; k++) {
        add_entity_to_labels(world, main_cameras[k], labels, entities, 0);
        add_entity_to_labels(world, ui_cameras[k], labels, entities, 0);
    }
    // add_entity_children_to_labels(world, zox_players[0], labels, entities, 0);
    add_entity_children_to_labels(world, local_keyboard, labels, entities, 0);
    if (local_mouse) {
        add_entity_children_to_labels(world, local_mouse, labels, entities, 0);
    }
    add_entity_children_to_labels(world, gamepad_entity, labels, entities, 0);
    add_entity_children_to_labels(world, local_touchscreen, labels, entities, 0);
    // add_entity_children_to_labels(world, local_character3D, labels, entities, 0);
    add_entity_to_labels(world, local_terrain, labels, entities, 0);
    add_entity_children_to_labels(world, canvas, labels, entities, 0);
}

void HierarchyRefreshSystem(ecs_iter_t *it) {
    const byte is_header = 1;
    const byte is_scrollbar = 1;
    const byte list_start = is_header + is_scrollbar;
    const ClickEvent click_event = (ClickEvent) { &button_event_clicked_hierarchy };
    // const ecs_entity_t realm = local_realm;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(Position2D)
    zox_sys_in(CanvasPosition)
    zox_sys_in(Layer2D)
    zox_sys_in(Anchor)
    zox_sys_in(ListUIMax)
    zox_sys_in(ElementFontSize)
    zox_sys_in(CanvasLink)
    zox_sys_out(HierarchyUIDirty)
    zox_sys_out(PixelPosition)
    zox_sys_out(PixelSize)
    zox_sys_out(TextureSize)
    zox_sys_out(Children)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(Position2D, position2D)
        zox_sys_i(CanvasPosition, canvasPosition)
        zox_sys_i(Layer2D, layer2D)
        zox_sys_i(Anchor, anchor)
        zox_sys_i(ListUIMax, listUIMax)
        zox_sys_i(ElementFontSize, elementFontSize)
        zox_sys_i(CanvasLink, canvasLink)
        zox_sys_o(PixelPosition, pixelPosition)
        zox_sys_o(PixelSize, pixelSize)
        zox_sys_o(TextureSize, textureSize)
        zox_sys_o(HierarchyUIDirty, hierarchyUIDirty)
        zox_sys_o(Children, children)
        if (!hierarchyUIDirty->value || !children->value || children->length < 2) {
            continue; // children issues
        }
        const ecs_entity_t header = children->value[0];
        const ecs_entity_t scrollbar = children->value[is_header];
        if (!header || !scrollbar) {
            continue; // no scrollbar
        }
        const ecs_entity_t canvas = canvasLink->value;
        zox_geter_value(canvas, PixelSize, int2, canvas_size)
        const int elements_visible = listUIMax->value;
        const int font_size = elementFontSize->value * zox_ui_scale;
        const byte button_layer = layer2D->value + 1;
        const int scrollbar_margins = zox_gett_value(scrollbar, ElementMargins).x;
        const int scrollbar_width = zox_gett_value(scrollbar, PixelSize).x;
        const byte2 button_padding = (byte2) { (int) (font_size * 0.46f), (int) (font_size * 0.3f) };
        const int2 list_margins = (int2) { (int) (font_size * 0.8f), (int) (font_size * 0.8f) };
        const int button_inner_margins = (int) (font_size * 0.5f);
        // our label data
        ecs_entity_t_array_d* entities = create_ecs_entity_t_array_d(32);
        text_group_dynamic_array_d* labels = create_text_group_dynamic_array_d(32);
        add_all_prefabs(world, entities, labels, canvas);
        // resize window
        int labels_count = labels->size;
        // first pass, limit it, some reason flecs table glitches here
#ifdef zox_glitch_fix_hierarchy_labels
        if (is_first_hierarchy_spawn) { // children->length == 2
            is_first_hierarchy_spawn = 0;
            labels_count = int_min(max_hierarchy_labels, labels_count);
        }
#endif
        const int max_characters = get_max_characters_d("hierarchy", labels);
        const float2 window_position = position2D->value;
        const int2 window_pixel_position_global = canvasPosition->value;
        const int2 old_window_size = pixelSize->value;
        // const int window_width = get_max_width(header_label, scaled_header_font_size, header_margins, labels, elements_count, scaled_font_size, button_padding.x + list_margins.x);
        int2 new_window_size = { (font_size) * max_characters + button_padding.x * 2 + list_margins.x * 2, old_window_size.y };
        if (is_scrollbar) {
            new_window_size.x += scrollbar_width + scrollbar_margins * 2;
        }
        if (new_window_size.x != old_window_size.x) {
            int header_height = zox_gett_value(header, PixelSize).y;
            reverse_anchor_element_position2D_with_header(&pixelPosition->value, anchor->value, old_window_size, header_height);
            pixelSize->value = new_window_size;
            textureSize->value = new_window_size;
            // on_resized_element(world, e, new_window_size, int2_to_float2(canvas_size));
            // set position based on new size
            anchor_element_position2D_with_header(&pixelPosition->value, anchor->value, pixelSize->value, header_height);
        }
        // refresh elements
        set_ui_list_hierarchy(world,
            children,
            e,
            canvas,
            elements_visible,
            labels,
            entities,
            labels_count,
            click_event,
            button_layer,
            button_padding,
            button_inner_margins,
            font_size,
            list_start,
            list_margins,
            is_scrollbar,
            scrollbar_width,
            scrollbar_margins,
            window_position,
            window_pixel_position_global,
            new_window_size,
            canvas_size);
        // dispose allocated things
        for (int j = 0; j < labels->size; j++) {
            free(labels->data[j].text);
        }
        dispose_text_group_dynamic_array_d(labels);
        dispose_ecs_entity_t_array_d(entities);
        hierarchyUIDirty->value = 0;
    }
} zox_declare_system(HierarchyRefreshSystem)