// make everything a child of realm
extern ecs_entity_t local_realm;

void HierarchyRefreshSystem(ecs_iter_t *it) {
    const byte is_header = 1;
    const byte is_scrollbar = 1;
    const byte list_start = is_header + is_scrollbar;
    const ecs_entity_t realm = local_realm;
    zox_field_world()
    zox_field_in(Position2D, position2Ds, 2)
    zox_field_in(CanvasPosition, canvasPositions, 3)
    zox_field_in(Layer2D, layer2Ds, 4)
    zox_field_in(Anchor, anchors, 5)
    zox_field_in(ListUIMax, listUIMaxs, 6)
    zox_field_in(ElementFontSize, elementFontSizes, 7)
    zox_field_in(CanvasLink, canvasLinks, 8)
    zox_field_out(HierarchyUIDirty, hierarchyUIDirtys, 9)
    zox_field_out(PixelPosition, pixelPositions, 10)
    zox_field_out(PixelSize, pixelSizes, 11)
    zox_field_out(TextureSize, textureSizes, 12)
    zox_field_out(Children, childrens, 13)
    for (int i = 0; i < it->count; i++) {
        const ecs_entity_t e = it->entities[i];
        zox_field_o(HierarchyUIDirty, hierarchyUIDirtys, hierarchyUIDirty)
        if (!hierarchyUIDirty->value) continue;
        zox_field_o(Children, childrens, children)
        if (!children->value || children->length < 2) continue; // children issues
        const ecs_entity_t scrollbar = children->value[1];
        if (!scrollbar) continue; // no scrollbar
        const ecs_entity_t header = children->value[0];
        zox_field_i(Position2D, position2Ds, position2D)
        zox_field_i(CanvasPosition, canvasPositions, canvasPosition)
        zox_field_i(Layer2D, layer2Ds, layer2D)
        zox_field_i(Anchor, anchors, anchor)
        zox_field_i(ListUIMax, listUIMaxs, listUIMax)
        zox_field_i(ElementFontSize, elementFontSizes, elementFontSize)
        zox_field_i(CanvasLink, canvasLinks, canvasLink)
        zox_field_o(PixelPosition, pixelPositions, pixelPosition)
        zox_field_o(PixelSize, pixelSizes, pixelSize)
        zox_field_o(TextureSize, textureSizes, textureSize)
        const ecs_entity_t canvas = canvasLink->value;
        const int2 canvas_size = zox_get_value(canvas, PixelSize)
        const int elements_visible = listUIMax->value;
        const int font_size = elementFontSize->value * zox_ui_scale;
        const byte button_layer = layer2D->value + 1;
        const int scrollbar_margins = zox_gett_value(scrollbar, ElementMargins).x;
        const int scrollbar_width = zox_gett_value(scrollbar, PixelSize).x;
        const ClickEvent click_event = (ClickEvent) { &button_event_clicked_hierarchy };
            const byte2 button_padding = (byte2) { (int) (font_size * 0.46f), (int) (font_size * 0.3f) };
            const int2 list_margins = (int2) { (int) (font_size * 0.8f), (int) (font_size * 0.8f) };
            const int button_inner_margins = (int) (font_size * 0.5f);
        // our label data
        ecs_entity_t_array_d* entities = create_ecs_entity_t_array_d(32);
        text_group_dynamic_array_d* labels = create_text_group_dynamic_array_d(32);
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
        add_entity_children_to_labels(world, keyboard_entity, labels, entities, 0);
        if (mouse_entity) add_entity_children_to_labels(world, mouse_entity, labels, entities, 0);
        add_entity_children_to_labels(world, gamepad_entity, labels, entities, 0);
        add_entity_children_to_labels(world, touchscreen_entity, labels, entities, 0);
        // add_entity_children_to_labels(world, local_character3D, labels, entities, 0);
        add_entity_to_labels(world, local_terrain, labels, entities, 0);
        add_entity_children_to_labels(world, canvas, labels, entities, 0);
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
        int2 new_window_size = { (font_size) * max_characters + button_padding.x * 2 + list_margins.x * 2, old_window_size.y };
        if (is_scrollbar) new_window_size.x += scrollbar_width + scrollbar_margins * 2;
        if (new_window_size.x != old_window_size.x) {
            int header_height = zox_gett_value(header, PixelSize).y;
            reverse_anchor_element_position2D_with_header(&pixelPosition->value, anchor->value, old_window_size, header_height);
            pixelSize->value = new_window_size;
            textureSize->value = new_window_size;
            on_resized_element(world, e, new_window_size, int2_to_float2(canvas_size));
            // set position based on new size
            anchor_element_position2D_with_header(&pixelPosition->value, anchor->value, pixelSize->value, header_height);
        }
        // refresh elements
        set_ui_list_hierarchy(world, children, e, canvas,
            elements_visible, labels, entities, labels_count, click_event,
            button_layer, button_padding, button_inner_margins, font_size,
            list_start, list_margins,
            is_scrollbar, scrollbar_width, scrollbar_margins,
            window_position, window_pixel_position_global, new_window_size, canvas_size);
        // dispose allocated things
        for (int j = 0; j < labels->size; j++) free(labels->data[j].text);
        dispose_text_group_dynamic_array_d(labels);
        dispose_ecs_entity_t_array_d(entities);
        hierarchyUIDirty->value = 0;
    }
} zox_declare_system(HierarchyRefreshSystem)
