ecs_entity_t prefab_button;

ecs_entity_t spawn_prefab_button(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_button")
    zox_add_tag(e, Button)
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 7 })
    zox_set(e, OutlineThickness, { 3 })
    zox_set(e, Color, {{ 35, 88, 66, 255 }})
    zox_add_tag(e, Selectable)
    zox_add_tag(e, Clickable)
    zox_set(e, ClickEvent, { NULL })
    zox_set(e, Children, { 0, NULL })
    add_ui_plus_components(world, e);
    zox_set(e, SelectableState, { 0 })
    zox_set(e, ClickableState, { 0 })
    ecs_defer_end(world);
    prefab_button = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab button [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_button(ecs_world_t *world, ecs_entity_t parent, int2 position, int2 padding, float2 anchor, const char* text, int font_size, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size, int2 canvas_size) {
    int2 zext_size = (int2) { font_size * strlen(text), font_size };
    int2 button_size = (int2) { zext_size.x + padding.x * 2, zext_size.y + padding.y * 2 };
    zox_instance(prefab_button)
    zox_name("button")
    float2 position2D = initialize_ui_components_2(world, e, parent, position, button_size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, 1);
    children.value[0] = spawn_zext(world, zext_prefab, e, (int2) { 0, 0 }, (float2) { 0.5f, 0.5f }, int2_to_byte2(padding), text, font_size, 0, (layer + 1), position2D, zext_size);
    zox_set_only(e, Children, { children.length, children.value })
    #ifdef zoxel_debug_spawns
        zoxel_log("Spawned button [%lu]\n", (long int) e);
    #endif
    return e;
}