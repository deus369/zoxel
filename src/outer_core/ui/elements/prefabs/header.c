ecs_entity_t header_prefab;

ecs_entity_t spawn_prefab_header(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_header");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab header [%lu].\n", (long int) (e));
    #endif
    add_ui_plus_components(world, e);
    zoxel_add_tag(world, e, Header);
    zoxel_add_tag(world, e, FrameTexture);
    zoxel_add(world, e, Children);
    zoxel_add_tag(world, e, Selectable);
    zoxel_set(world, e, SelectableState, { 0 });
    zoxel_add_tag(world, e, Dragable);
    zoxel_set(world, e, DragableState, { 0 });
    zoxel_set(world, e, DraggerLink, { 0 });
    zoxel_set(world, e, DraggingDelta, {{ 0, 0 }});
    ecs_defer_end(world);
    header_prefab = e;
    return e;
}

ecs_entity_t spawn_header(ecs_world_t *world, ecs_entity_t parent, int2 position, int2 size, float2 anchor,
    const char* text, int font_size, int header_margins, unsigned char layer,
    float2 parent_position2D,int2 parent_pixel_size, bool is_close_button)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, header_prefab);
    set_unique_entity_name(world, e, "header");
    float2 position2D = initialize_ui_components_2(world, e, parent, position, size, anchor, layer,
        parent_position2D, parent_pixel_size,
        ecs_get(world, main_canvas, PixelSize)->value);
    int children_length = 1;
    if (is_close_button)
    {
        children_length++;
    }
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, children_length);
    int string_length = strlen(text);
    int2 zext_position = (int2) { ((font_size * string_length) / 2) + header_margins / 2, 0 };
    float2 zext_anchor = (float2) { 0, 0.5f };
    if (!is_close_button)
    {
        zext_anchor.x = 0.5f;
        zext_position.x = 0;
    }
    children.value[0] = spawn_zext(world, zext_prefab, e,
        zext_position, zext_anchor,
        text, font_size, layer + 1,
        position2D, size);
    if (is_close_button)
    {
        children.value[1] = spawn_button(world, e,
            (int2) { - (font_size / 2) - header_margins / 2, 0 },
            (int2) { font_size, font_size },
            (float2) { 1.0f, 0.5f },
            "X", font_size, layer + 1,
            position2D, size);
        zoxel_add_tag(world, children.value[1], CloseButton);
    }
    ecs_set(world, e, Children, { children.length, children.value });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    printf("Spawned header [%lu]\n", (long int) e);
    #endif
    return e;
}