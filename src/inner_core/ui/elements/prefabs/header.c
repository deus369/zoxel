extern void button_event_close_window(ecs_world_t *world, ecs_entity_t trigger_entity);
ecs_entity_t header_prefab;

ecs_entity_t spawn_prefab_header(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_header")
    zox_add_tag(e, Header)
    zox_add_tag(e, FrameTexture)
    add_selectable_components(world, e);
    add_draggable_components(world, e);
    // add_clickable_components(world, e);
    zox_prefab_set(e, Color, {{ 77, 44, 33, 255 }})
    zox_prefab_set(e, FrameCorner, { 7 })
    zox_prefab_set(e, OutlineThickness, { 3 })
    zox_prefab_set(e, Children, { 0, NULL })
    add_ui_plus_components(world, e);
    header_prefab = e;
    #ifdef zoxel_debug_prefabs
        zox_log(" > spawn_prefab header [%lu].\n", (long int) (e))
    #endif
    return e;
}

ecs_entity_t spawn_header(ecs_world_t *world, ecs_entity_t parent, int2 position, int2 size, float2 anchor, const char* text, int font_size, int header_margins, unsigned char layer, float2 parent_position2D,int2 parent_pixel_size, unsigned char is_close_button, int2 canvas_size) {
    int string_length = strlen(text);
    int2 zext_position = (int2) { ((font_size * string_length) / 2) + header_margins / 2, 0 };
    float2 zext_anchor = (float2) { 0, 0.5f };
    if (!is_close_button) {
        zext_anchor.x = 0.5f;
        zext_position.x = 0;
    }
    int2 padding = (int2) { (int) (font_size * 0.3f), (int) (font_size * 0.3f) };
    zox_instance(header_prefab)
    zox_name("header")
    zox_set(e, DraggedLink, { parent })
    float2 position2D = initialize_ui_components_2(world, e, parent, position, size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    int children_length = 1;
    if (is_close_button) children_length++;
    Children *children = zox_get_mut(e, Children)
    resize_memory_component(Children, children, ecs_entity_t, children_length)
    children->value[0] = spawn_zext(world, zext_prefab, e, zext_position, zext_anchor, int2_to_byte2(padding), text, font_size, 0, layer + 1, position2D, size, 0);
    if (is_close_button) {
        int2 close_button_position = (int2) { - (font_size / 2) - header_margins / 2, 0 };
        ecs_entity_t close_button = spawn_button(world, e, close_button_position, padding, (float2) { 1.0f, 0.5f }, "X", font_size, layer + 1, position2D, size, canvas_size, 0);
        zox_set(close_button, ClickEvent, { &button_event_close_window })
        zox_add_tag(close_button, CloseButton)
        children->value[1] = close_button;
    }
    zox_modified(e, Children)
    #ifdef zoxel_debug_spawns
        zox_log("    > spawned header [%lu]\n", (long int) e)
    #endif
    return e;
}
