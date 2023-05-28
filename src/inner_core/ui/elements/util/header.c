extern void button_event_close_window(ecs_world_t *world, ecs_entity_t trigger_entity);

ecs_entity_t spawn_header(ecs_world_t *world, ecs_entity_t parent, int2 position, int2 size, float2 anchor, const char* text, int font_size,
    int header_margins, unsigned char layer, float2 parent_position2D,int2 parent_pixel_size, unsigned char is_close_button, int2 canvas_size) {
    int children_length = 1;
    if (is_close_button) {
        children_length++;
    }
    int string_length = strlen(text);
    int2 zext_position = (int2) { ((font_size * string_length) / 2) + header_margins / 2, 0 };
    float2 zext_anchor = (float2) { 0, 0.5f };
    if (!is_close_button) {
        zext_anchor.x = 0.5f;
        zext_position.x = 0;
    }
    int2 padding = (int2) { (int) (font_size * 0.3f), (int) (font_size * 0.3f) };
    ecs_defer_begin(world);
    zox_instance(header_prefab)
    zox_name("header")
    float2 position2D = initialize_ui_components_2(world, e, parent, position, size, anchor, layer, parent_position2D, parent_pixel_size, canvas_size);
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, children_length)
    children.value[0] = spawn_zext(world, zext_prefab, e, zext_position, zext_anchor, int2_to_byte2(padding), text, font_size, 0, layer + 1, position2D, size);
    if (is_close_button) {
        children.value[1] = spawn_button(world, e, (int2) { - (font_size / 2) - header_margins / 2, 0 },
            padding, (float2) { 1.0f, 0.5f }, "X", font_size, layer + 1, position2D, size, canvas_size);
        zox_add_tag(children.value[1], CloseButton);
        zox_set(children.value[1], ClickEvent, { &button_event_close_window });
        /*printf("--- Spawned close button [%lu] ---\n", (long int) children.value[1]);
        printf("--- Spawned header [%lu] ---\n", (long int) e);
        printf("    size [%ix%i]\n", size.x, size.y);*/
    }
    zox_set_only(e, Children, { children.length, children.value })
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        printf("Spawned header [%lu]\n", (long int) e);
    #endif
    // printf("Header, with layer of [%i]\n ", layer);
    return e;
}