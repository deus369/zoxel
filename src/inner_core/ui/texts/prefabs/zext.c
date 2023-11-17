ecs_entity_t zext_prefab;

ecs_entity_t spawn_zext_prefab(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("zext_prefab")
    add_transform2Ds(world, e);
    add_ui_plus_components_invisible(world, e);
    zox_add_tag(e, Zext)
    zox_prefab_set(e, ZextSize, { 0 })
    zox_prefab_set(e, ZextPadding, { byte2_zero })
    zox_prefab_set(e, ZextDirty, { 0 })
    zox_prefab_set(e, ZextData, { 0, NULL })
    zox_prefab_set(e, Children, { 0, NULL })
    zext_prefab = e;
#ifdef zoxel_debug_prefabs
    zox_log(" > spawn_prefab zext [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t parent, ecs_entity_t canvas, int2 pixel_position, float2 anchor, byte2 padding, const char* text, int font_size, unsigned char alignment, unsigned char layer, int2 parent_pixel_position_global, int2 parent_pixel_size, unsigned char render_disabled) {
    int2 canvas_size = zox_get_value(main_canvas, PixelSize)
    int textLength = strlen(text);
    unsigned char zigel_layer = layer + 1;
    int2 pixel_size = (int2) { font_size * textLength, font_size };
    zox_instance(prefab)
    zox_name("zext")
    zox_set(e, RenderDisabled, { render_disabled })
    zox_set(e, ZextSize, { font_size })
    zox_set(e, ZextPadding, { padding })
    zox_set(e, MeshAlignment, { alignment })
    int2 pixel_position_global = get_element_pixel_position_global(parent_pixel_position_global, parent_pixel_size, pixel_position, anchor);
    float2 position2D = get_element_position(pixel_position_global, canvas_size);
    initialize_ui_components_3(world, e, parent, canvas, pixel_position, pixel_size, anchor, layer, position2D, pixel_position_global);
    ZextData *zextData = zox_get_mut(e, ZextData)
    resize_memory_component(ZextData, zextData, unsigned char, textLength)
    for (int i = 0; i < textLength; i++) zextData->value[i] = convert_ascii(text[i]);
    zox_modified(e, ZextData)
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, textLength)
    for (int i = 0; i < textLength; i++) {
        unsigned char zigel_index = zextData->value[i];
        ecs_entity_t zigel = spawn_zext_zigel(world, e, canvas, zigel_layer, i, textLength, zigel_index, font_size, alignment, padding, pixel_position_global, pixel_size, canvas_size);
        zox_set(zigel, RenderDisabled, { render_disabled })
        children->value[i] = zigel;
    }
    zox_modified(e, Children)
    // zox_set(e, ZextDirty, { 1 })
#ifdef zoxel_debug_spawns
    zox_log("   > spawned zext [%lu]\n", e)
#endif
    return e;
}
