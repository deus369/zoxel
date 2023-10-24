// when scroll_front_drags, get window, move elements by amount
//      > e->parent->parent->children[2+] for list elements
void ScrollbarSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    // 1 is ScrollButtoon
    const DraggableState *draggableStates = ecs_field(it, DraggableState, 2);
    const PixelPosition *pixelPositions = ecs_field(it, PixelPosition, 3);
    for (int i = 0; i < it->count; i++) {
        const DraggableState *draggableState = &draggableStates[i];
        if (!draggableState->value) continue;
        const PixelPosition *pixelPosition = &pixelPositions[i];
        // if vertical scrollbar
        // convert pixel position offset to a float
        ecs_entity_t e = it->entities[i];
        const PixelSize *pixelSize = zox_get(e, PixelSize)
        ecs_entity_t scrollbar = zox_get_value(e, ParentLink)
        const PixelSize *scrollbar_size = zox_get(scrollbar, PixelSize)
        // zox_log("   > button %lu scrollbar %lu]\n", e, scrollbar)
        // zox_log("   > scrollbar_size %i pixelSize %i]\n", scrollbar_size->value.y, pixelSize->value.y)
        if (scrollbar_size->value.y == pixelSize->value.y) continue;
        int scrollbar_offset = scrollbar_size->value.y - pixelSize->value.y;
        // zox_log("   > dragging scroll button [%ix%i] - scrollbar_offset [%i]\n", pixelPosition->value.x, pixelPosition->value.y, scrollbar_offset)
        int anchored_position_y = -pixelPosition->value.y + scrollbar_offset / 2;
        float scroll_percentage = anchored_position_y / (float) scrollbar_offset;
        // zox_log("   > dragging scroll button [%i] [%i] anchored_position_y [%i] %f\n", pixelPosition->value.y, scrollbar_offset, anchored_position_y, scroll_percentage)
        // scrollview_spawn - scrollview_shown gives us scrollview_scroll
        // int scrollview_scroll = 2; // set for now
        ecs_entity_t list_ui = zox_get_value(scrollbar, ParentLink)
        const Children *list_elements = zox_get(list_ui, Children)
        int list_start = 2;
        int elements_visible = zox_get_value(list_ui, ListUIMax)
        int scrollview_scroll = list_elements->length - list_start - elements_visible;
        int scrollview_index_offset = round(scrollview_scroll * scroll_percentage);
        const int scrollbar_margins = zox_gett_value(scrollbar, ElementMargins).x; // 8 * ui_scale;
        const int scrollbar_width = scrollbar_size->value.x; // 8 * ui_scale;
        const int font_size = 18 * default_ui_scale;
        int2 button_padding = (int2) { (int) (font_size * 0.46f), (int) (font_size * 0.3f) };
        int2 list_margins = (int2) { (int) (font_size * 0.2f), (int) (font_size * 0.2f) };
        // zox_log("   > dragging [%i]\n", scrollview_index_offset)
        // now from a new index, repoosition all elements in the list
        // zox_log("   list_elements->length %lu:%i\n", list_ui, list_elements->length)
        /*if (list_elements->value == NULL || list_elements->length > 250) {
            zox_log("   > %lu list_elements issues: :%p:%i\n", list_ui, list_elements->value, list_elements->length)
            continue;
        }
        zox_log("   > %lu list_elements length:%i\n", list_ui, list_elements->length)*/
        // int elements_visible = 4;
        for (int j = list_start; j < list_elements->length; j++) {
            // set list position to scrollview_index_offset
            // zox_log("       > list_element %i\n", j)
            ecs_entity_t list_element = list_elements->value[j];
            // zox_log("   list_element %lu\n", list_element)
            int list_index = j - list_start - scrollview_index_offset;
            // zox_log("   [%i] is %i\n", j, list_index)
            int2 element_position = (int2) { 0, - list_index * (font_size + button_padding.y * 2 + list_margins.y) - list_margins.y };
            element_position.y += (scrollbar_size->value.y - font_size - button_padding.y * 2) / 2;
            element_position.x -= (scrollbar_width / 2) - scrollbar_margins;
            zox_set(list_element, PixelPosition, { element_position })
            unsigned char render_enabled = (j - list_start) >= scrollview_index_offset && (j - list_start) < scrollview_index_offset + elements_visible;
            // zox_set(list_element, RenderDisabled, { !render_enabled })
            disable_element_rendering(world, list_element, !render_enabled);
        }
    }
} zox_declare_system(ScrollbarSystem)
