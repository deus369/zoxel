ecs_entity_t header_prefab;
extern ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t parent, int2 pixel_position, float2 anchor,
    const char* text, int font_size, unsigned char layer);
    
ecs_entity_t spawn_prefab_header(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "header_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab header [%lu].\n", (long int) (e));
    #endif
    zoxel_add_component(world, e, Children);
    zoxel_add_tag(world, e, Header);
    zoxel_add_tag(world, e, FrameTexture);
    add_ui_plus_components(world, e);
    zoxel_set_component(world, e, SelectableState, { 0 });
    header_prefab = e;
    return e;
}

ecs_entity_t spawn_header(ecs_world_t *world, ecs_entity_t parent,
    int2 position, int2 size, float2 anchor,
    const char* text, int font_size, int header_margins,
    unsigned char layer)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, button_prefab);
    initialize_ui_components(world, e, parent, position, size, anchor, layer);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 2);
    int string_length = strlen(text);
    children->value[0] = spawn_zext(world, e,
        (int2) { ((font_size * string_length) / 2) + header_margins / 2, 0 },
        (float2) { 0, 0.5f },
        text, font_size, layer + 1);
    children->value[1] = spawn_button(world, e,
        (int2) { - (font_size / 2) - header_margins / 2, 0 },
        (int2) { font_size, font_size },
        (float2) { 1.0f, 0.5f },
        "X", font_size, layer + 1);
    ecs_modified(world, e, Children);
    return e;
}