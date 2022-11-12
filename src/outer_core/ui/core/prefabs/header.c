ecs_entity_t header_prefab;

ecs_entity_t spawn_prefab_header(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "ui_prefab_header");
    zoxel_add_component(world, e, Children);
    zoxel_add_tag(world, e, Header);
    zoxel_add_tag(world, e, FrameTexture);
    add_ui_plus_components(world, e);
    header_prefab = e;
    return e;
}

extern ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t parent, int2 pixel_position, float2 anchor, const char* text, int font_size);

ecs_entity_t spawn_header(ecs_world_t *world, ecs_entity_t parent,
    int2 position, int2 size, float2 anchor,
    const char* text, int font_size, int header_margins)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, button_prefab);
    initialize_ui_components(world, e, parent, position, size, anchor);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 2);
    int string_length = strlen(text);
    children->value[0] = spawn_zext(world, e,
        (int2) { ((font_size * string_length) / 2) + header_margins / 2, 0 },
        (float2) { 0, 0.5f },
        text, font_size);
    children->value[1] = spawn_button(world, e,
        (int2) { - (font_size / 2) - header_margins / 2, 0 },
        (int2) { font_size, font_size },
        (float2) { 1.0f, 0.5f },
        "X", font_size);
    ecs_modified(world, e, Children);
    return e;
}