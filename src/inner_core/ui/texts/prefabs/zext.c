ecs_entity_t zext_prefab;

ecs_entity_t spawn_zext_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("zext_prefab")
    zox_add_tag(e, Zext)
    zox_add(e, ZextData)
    zox_add(e, ZextSize)
    zox_add(e, ZextPadding)
    zox_prefab_set(e, ZextDirty, { 0 })
    zox_set(e, Children, { 0, NULL })
    add_transform2Ds(world, e);
    add_ui_plus_components_invisible(world, e);
    zext_prefab = e;
    #ifdef zoxel_debug_prefabs
        zox_log(" > spawn_prefab zext [%lu]\n", e)
    #endif
    return e;
}

unsigned char is_zext(ZextData *zextData, const char* text) {
    unsigned char text_length = strlen(text);
    if (zextData->length != text_length) return 0;
    for (int i = 0; i < text_length; i++) if (convert_ascii(text[i]) != zextData->value[i]) return 0;
    return 1;
}

void set_zext(ZextData *zextData, const char* text) {
    unsigned char text_length = strlen(text);
    if (zextData->length != text_length) resize_memory_component(ZextData, zextData, unsigned char, text_length)
    for (unsigned char i = 0; i < text_length; i++) zextData->value[i] = convert_ascii(text[i]);
}

ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t parent, int2 position, float2 anchor, byte2 padding, const char* text, int font_size, unsigned char alignment, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size, unsigned char render_disabled) {
    int2 canvas_size = zox_get_value(main_canvas, PixelSize)
    int textLength = strlen(text);
    int2 zext_size = (int2) { font_size * textLength, font_size };
    zox_instance(prefab)
    zox_name("zext")
    zox_set(e, RenderDisabled, { render_disabled })
    zox_set(e, ZextSize, { font_size })
    zox_set(e, ZextPadding, { padding })
    zox_set(e, MeshAlignment, { alignment })
    float2 position2D = initialize_ui_components_2(world, e, parent, position, zext_size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    unsigned char zigel_layer = layer + 1;
    ZextData *zextData = zox_get_mut(e, ZextData)
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(ZextData, zextData, unsigned char, textLength)
    resize_memory_component(Children, children, ecs_entity_t, textLength)
    for (int i = 0; i < textLength; i++) {
        unsigned char zigel_index = convert_ascii(text[i]);
        zextData->value[i] = zigel_index;
        children->value[i] = spawn_zext_zigel(world, e, zigel_layer, i, textLength, zigel_index, font_size, alignment, padding, position2D, zext_size, canvas_size);
        zox_set(children->value[i], RenderDisabled, { render_disabled })
    }
    zox_modified(e, ZextData)
    zox_modified(e, Children)
    #ifdef zoxel_debug_spawns
        zox_log("   > spawned zext [%lu]\n", e)
    #endif
    return e;
}
