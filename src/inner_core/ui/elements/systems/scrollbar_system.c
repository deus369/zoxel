// when scroll_front_drags, get window, move elements by amount
//      > e->parent->parent->children[2+] for list elements
// if vertical scrollbar
void ScrollbarSystem(ecs_iter_t *it) {
    ecs_world_t *world = it->world;
    zox_field_in(DraggableState, draggableStates, 2)
    zox_field_in(PixelPosition, pixelPositions, 3)
    zox_field_in(PixelSize, pixelSizes, 4)
    zox_field_in(ParentLink, parentLinks, 5)
    for (int i = 0; i < it->count; i++) {
        const DraggableState *draggableState = &draggableStates[i];
        if (!draggableState->value) continue;
        const PixelPosition *pixelPosition = &pixelPositions[i];
        // ecs_entity_t e = it->entities[i];
        const PixelSize *pixelSize = &pixelSizes[i];
        const ParentLink *parentLink = &parentLinks[i];
        // const PixelSize *pixelSize = zox_get(e, PixelSize)
        ecs_entity_t scrollbar = parentLink->value;
        const PixelSize *scrollbar_size = zox_get(scrollbar, PixelSize)
        if (scrollbar_size->value.y == pixelSize->value.y) continue;
        ecs_entity_t list_ui = zox_get_value(scrollbar, ParentLink)

        const ElementFontSize *elementFontSize = zox_get(list_ui, ElementFontSize) // &elementFontSizes[i];
        int font_size = elementFontSize->value * default_ui_scale;
        int scrollbar_offset = scrollbar_size->value.y - pixelSize->value.y;
        int anchored_position_y = -pixelPosition->value.y + scrollbar_offset / 2;
        float scroll_percentage = anchored_position_y / (float) scrollbar_offset;
        // scrollview_spawn - scrollview_shown gives us scrollview_scroll
        const Children *list_elements = zox_get(list_ui, Children)
        int list_start = 2;
        int elements_visible = zox_get_value(list_ui, ListUIMax)
        int2 window_size = zox_get_value(list_ui, PixelSize)
        int scrollview_scroll = list_elements->length - list_start - elements_visible;
        int scrollview_index_offset = round(scrollview_scroll * scroll_percentage);
        const int scrollbar_margins = zox_gett_value(scrollbar, ElementMargins).x; // 8 * ui_scale;
        const int scrollbar_width = scrollbar_size->value.x; // 8 * ui_scale;
        // const int font_size = 24 * default_ui_scale;
        int2 button_padding = (int2) { (int) (font_size * 0.46f), (int) (font_size * 0.3f) };
        int2 list_margins = (int2) { (int) (font_size * 0.8f), (int) (font_size * 0.8f) };
        int button_inner_margins = (int) (font_size * 0.5f);
        for (int j = list_start; j < list_elements->length; j++) {
            int normal_j = j - list_start;
            // set list position to scrollview_index_offset
            ecs_entity_t list_element = list_elements->value[j];
            int list_index = normal_j - scrollview_index_offset;
            int2 element_position = (int2) { 0, (int) (window_size.y / 2) - (list_index + 0.5f) * (font_size + button_padding.y * 2) - list_margins.y - list_index * button_inner_margins };
            element_position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;
            PixelPosition *element_pixel_position = zox_get_mut(list_element, PixelPosition)
            if (!int2_equals(element_pixel_position->value, element_position)) {
                element_pixel_position->value = element_position;
                zox_modified(list_element, PixelPosition)
            }
            unsigned char render_enabled = normal_j >= scrollview_index_offset && normal_j < scrollview_index_offset + elements_visible;
            disable_element_rendering(world, list_element, !render_enabled);
        }
    }
} zox_declare_system(ScrollbarSystem)
