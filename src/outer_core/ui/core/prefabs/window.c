ecs_entity_t window_prefab;

ecs_entity_t spawn_prefab_window(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "window_element_prefab");
    zoxel_add_tag(world, e, Window);
    zoxel_add_component(world, e, Children);
    // generic
    add_seed(world, e, 222);
    add_dirty(world, e);
    add_texture(world, e, (int2) { });
    add_texture_frame(world, e);
    #ifdef zoxel_transforms2D
    add_transform2Ds(world, e);
    #endif
    add_unique_mesh_components(world, e);
    add_ui_components(world, e);
    window_prefab = e;
    return e;
}

extern ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t parent, int2 pixel_position, float2 anchor, const char* text, int font_size);

ecs_entity_t spawn_window(ecs_world_t *world, const char *header_label, int2 position, int2 size, float2 anchor)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, element_prefab);
    initialize_ui_components(world, e, canvas, position, size, anchor);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 2);
    // spawn child header
    int font_size = 28;
    children->value[0] = spawn_zext(world, e,
        (int2) { (font_size * 3) - font_size / 2, - font_size / 2 },
        (float2) { 0, 1.0f },
        header_label, font_size);
    children->value[1] = spawn_button(world, e,
        (int2) { - font_size / 2, - font_size / 2 },
        (int2) { font_size, font_size },
        (float2) { 1.0f, 1.0f },
        "X", font_size);
    ecs_modified(world, e, Children);
    return e;
}