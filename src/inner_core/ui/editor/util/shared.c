void set_entity_label_with_zext(ecs_world_t *world, ecs_entity_t e, unsigned char *value, int length) {
    const Children *name_label_children = zox_get(e, Children)
    ecs_entity_t zext_entity = name_label_children->value[0];
    ZextData *zextData = zox_get_mut(zext_entity, ZextData)
    if (zextData->value) free(zextData->value);
    zextData->value = memcpy(malloc(length), value, length);
    zextData->length = length;
    zox_modified(zext_entity, ZextData)
    // zox_set(zext_entity, ZextDirty, { 1 })
    ZextDirty *zextDirty = zox_get_mut(zext_entity, ZextDirty)
    zextDirty->value = 1;
    zox_modified(zext_entity, ZextDirty)
}

void set_entity_label_with_text(ecs_world_t *world, ecs_entity_t e, const char* text) {
    const Children *name_label_children = zox_get(e, Children)
    const ecs_entity_t zext_entity = name_label_children->value[0];
    ZextDirty *zextDirty = zox_get_mut(zext_entity, ZextDirty)
    if (zextDirty->value) return;
    ZextData *zextData = zox_get_mut(zext_entity, ZextData)
    if (is_zext(zextData, text)) return;
    set_zext(zextData, text);
    zextDirty->value = 1;
    zox_modified(zext_entity, ZextData)
    zox_modified(zext_entity, ZextDirty)
    // zox_set(zext_entity, ZextDirty, { 1 })
}

// int2 label_position = (int2) { 0, (int) (window_size.y / 2) - (j + 0.5f) * (font_size + button_padding.y * 2) - list_margins.y - j * button_inner_margins };
// if (is_scrollbar) label_position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;

int2 get_element_label_position(int index, const unsigned char font_size, const int2 button_padding, const int button_inner_margins, const int2 window_size, const int2 list_margins, const unsigned char is_scrollbar, const int scrollbar_width, const int scrollbar_margins) {
    int2 label_position = (int2) { 0, (int) (window_size.y / 2) - (index + 0.5f) * (font_size + button_padding.y * 2) - list_margins.y - index * button_inner_margins };
    if (is_scrollbar) label_position.x -= (scrollbar_width + scrollbar_margins * 2) / 2;
    return label_position;
}


void resize_window_scrollbar(Children *children, const int2 window_size, const int2 canvas_size, const int elements_visible, const int labels_count) {
    const ecs_entity_t scrollbar = children->value[1];
    const ecs_entity_t scrollbar_front = zox_gett_value(scrollbar, Children)[0];
    const int scrollbar_height = (int) window_size.y * ( float_min(1, (float) elements_visible / (float) labels_count));
    const int2 scrollbar_size = (int2) { zox_gett_value(scrollbar, PixelSize).x, scrollbar_height };
    zox_set(scrollbar_front, PixelSize, { scrollbar_size })
    zox_set(scrollbar_front, TextureSize, { scrollbar_size })
    zox_set(scrollbar_front, DraggableLimits, { (int2) { 0, (window_size.y / 2) - scrollbar_height / 2 } })
    zox_set(scrollbar_front, PixelPosition, { (int2) { 0, (window_size.y - scrollbar_height) / 2 } })
    on_resized_element(world, scrollbar_front, scrollbar_size, int2_to_float2(canvas_size));
}
