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

ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t parent, int2 position, float2 anchor, byte2 padding, const char* text, int font_size, unsigned char alignment, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size, unsigned char render_disabled) {
    int2 canvas_size = zox_get_value(main_canvas, PixelSize)
    int textLength = strlen(text);
    unsigned char zigel_layer = layer + 1;
    int2 zext_size = (int2) { font_size * textLength, font_size };
    zox_instance(prefab)
    zox_name("zext")
    zox_set(e, RenderDisabled, { render_disabled })
    zox_set(e, ZextSize, { font_size })
    zox_set(e, ZextPadding, { padding })
    zox_set(e, MeshAlignment, { alignment })
    float2 position2D = initialize_ui_components_2(world, e, parent, position, zext_size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    ZextData *zextData = zox_get_mut(e, ZextData)
    resize_memory_component(ZextData, zextData, unsigned char, textLength)
    for (int i = 0; i < textLength; i++) zextData->value[i] = convert_ascii(text[i]);
    zox_modified(e, ZextData)
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, textLength)
    for (int i = 0; i < textLength; i++) {
        unsigned char zigel_index = zextData->value[i];
        ecs_entity_t zigel = spawn_zext_zigel(world, e, zigel_layer, i, textLength, zigel_index, font_size, alignment, padding, position2D, zext_size, canvas_size);
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
