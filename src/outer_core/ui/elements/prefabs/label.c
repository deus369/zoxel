ecs_entity_t label_prefab;
extern ecs_entity_t zext_prefab;
extern ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t parent, int2 pixel_position, float2 anchor,
    const char* text, int font_size, unsigned char layer, float2 parent_position2D, int2 parent_pixel_size);

ecs_entity_t spawn_prefab_label(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, zext_prefab);
    ecs_add_id(world, e, EcsPrefab);
    ecs_set_name(world, e, "prefab_label");
    zoxel_add_tag(world, e, Label);
    // ecs_entity_t e = ecs_new_prefab(world, "label_prefab");
    // zoxel_add_component(world, e, Children);
    // zoxel_add_tag(world, e, FrameTexture);
    // add_ui_plus_components(world, e);
    ecs_defer_end(world);
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab label [%lu].\n", (long int) (e));
    #endif
    label_prefab = e;
    return e;
}

ecs_entity_t spawn_label(ecs_world_t *world, ecs_entity_t prefab, ecs_entity_t parent,
    int2 position, float2 anchor, const char* text, int font_size, unsigned char layer,
    float2 parent_position2D, int2 parent_pixel_size)
{
    ecs_entity_t e = spawn_zext(world, prefab, parent,
        position, anchor,
        text, font_size, layer,
        parent_position2D, parent_pixel_size);
    return e;
}
    // int textLength = strlen(text);
    // int2 pixel_size = (int2) { font_size * textLength, font_size };
    /*ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab);
    float2 position2D = initialize_ui_components_2(world, e, parent, position, pixel_size, anchor, layer,
        parent_position2D, parent_pixel_size);
    ecs_defer_end(world);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 1);
    children->value[0] = spawn_zext(world, e,
        (int2) { 0, 0 },
        (float2) { 0.5f, 0.5f },
        text, font_size, (layer + 1),
        position2D, pixel_size);
    ecs_modified(world, e, Children);*/