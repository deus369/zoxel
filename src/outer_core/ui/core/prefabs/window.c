ecs_entity_t window_prefab;

ecs_entity_t spawn_prefab_window(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "window_element_prefab");
    zoxel_add_tag(world, e, Window);
    zoxel_add_component(world, e, Children);
    zoxel_add_tag(world, e, FrameTexture);
    add_ui_plus_components(world, e);
    window_prefab = e;
    return e;
}

extern ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t parent, int2 pixel_position, float2 anchor, const char* text, int font_size);

ecs_entity_t spawn_window(ecs_world_t *world, const char *header_label, int2 position, int2 size, float2 anchor)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, window_prefab);
    initialize_ui_components(world, e, canvas, position, size, anchor);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 1);
    // spawn child header
    int font_size = 28;
    int header_margins = 4;
    children->value[0] = spawn_header(world, e, 
        (int2) { 0, - font_size / 2 - header_margins / 2 },
        (int2) { size.x, font_size + header_margins},
        (float2) { 0.5f, 1.0f },
        header_label, font_size, header_margins);
    ecs_modified(world, e, Children);
    return e;
}