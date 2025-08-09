// when scroll_front_drags, get window, move elements by amount
//      > e->parent->parent->children[2+] for list elements - if vertical scrollbar
void ScrollbarSystem(iter *it) {
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(DraggableState)
    zox_sys_in(PixelPosition)
    zox_sys_in(PixelSize)
    zox_sys_in(ParentLink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DraggableState, draggableState)
        zox_sys_i(PixelPosition, pixelPosition)
        zox_sys_i(PixelSize, pixelSize)
        zox_sys_i(ParentLink, parentLink)
        if (!draggableState->value) {
            continue;
        }
        const entity scrollbar = parentLink->value;
        const PixelSize *scrollbar_size = zox_get(scrollbar, PixelSize)
        if (scrollbar_size->value.y == pixelSize->value.y) continue;
        entity list_ui = zox_get_value(scrollbar, ParentLink)
        const ElementFontSize *elementFontSize = zox_get(list_ui, ElementFontSize)
        int scaled_font_size = elementFontSize->value * zox_ui_scale;
        int scrollbar_offset = scrollbar_size->value.y - pixelSize->value.y;
        int anchored_position_y = -pixelPosition->value.y + scrollbar_offset / 2;
        float scroll_percentage = anchored_position_y / (float) scrollbar_offset;
        // scrollview_spawn - scrollview_shown gives us scrollview_scroll
        const Children *list_elements = zox_get(list_ui, Children)
        int list_start = 2;

        zox_geter_value(list_ui, ListUIMax, int, elements_visible)
        zox_geter_value(list_ui, PixelSize, int2, window_size)
        int scrollview_scroll = list_elements->length - list_start - elements_visible;
        int scrollview_index_offset = round(scrollview_scroll * scroll_percentage);
        const int scrollbar_margins = zox_gett_value(scrollbar, ElementMargins).x;
        const int scrollbar_width = scrollbar_size->value.x;
        byte2 button_padding = (byte2) { (int) (scaled_font_size * 0.46f), (int) (scaled_font_size * 0.3f) };
        int2 list_margins = (int2) { (int) (scaled_font_size * 0.8f), (int) (scaled_font_size * 0.8f) };
        int button_inner_margins = (int) (scaled_font_size * 0.5f);
        for (int j = list_start; j < list_elements->length; j++) {
            int normal_j = j - list_start;
            // set list position to scrollview_index_offset
            const entity list_element = list_elements->value[j];
            int k = normal_j - scrollview_index_offset;

            int2 position = (int2) {
                0,
                (int) (window_size.y / 2) - (k + 0.5f) * (scaled_font_size + button_padding.y * 2) - list_margins.y - k * button_inner_margins
            };

            position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;

            PixelPosition *element_pixel_position = zox_get_mut(list_element, PixelPosition)
            if (!int2_equals(element_pixel_position->value, position)) {
                element_pixel_position->value = position;
                zox_modified(list_element, PixelPosition)
            }
            byte render_enabled = normal_j >= scrollview_index_offset && normal_j < scrollview_index_offset + elements_visible;
            disable_element_rendering(world, list_element, !render_enabled);
        }
    }
} zoxd_system(ScrollbarSystem)
