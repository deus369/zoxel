// the ui text entity that holds zigels.
ecs_entity_t spawn_zext_prefab(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "zext_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab zext [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Zext);
    zoxel_add_component(world, e, ZextData);
    zoxel_add_component(world, e, ZextSize);
    zoxel_add_component(world, e, AnimateZext);
    zoxel_add_component(world, e, ZextDirty);
    zoxel_add_component(world, e, Children);
    add_transform2Ds(world, e);
    // add_ui_components(world, e);
    add_ui_plus_components(world, e);
    ecs_defer_end(world);
    return e;
}

ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t parent, int2 position, float2 anchor,
    const char* text, int font_size, unsigned char layer,
    float2 parent_position2D, int2 parent_pixel_size)
{
    ecs_defer_begin(world);
    int textLength = strlen(text);
    int2 zext_size = (int2) { font_size * textLength, font_size };
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, zext_prefab);
    ecs_set(world, e, ZextSize, { font_size });
    ecs_set(world, e, ZextDirty, { 1 });
    float2 position2D = initialize_ui_components_2(world, e,
        parent, position, zext_size, anchor, layer,
        parent_position2D, parent_pixel_size);
    ecs_defer_end(world);
    ZextData *zextData = ecs_get_mut(world, e, ZextData);
    initialize_memory_component(zextData, unsigned char, textLength);
    for (int i = 0; i < textLength; i++)
    {
        unsigned char zigel_index = convert_ascii(text[i]);
        zextData->value[i] = zigel_index;
    }
    ecs_modified(world, e, ZextData);
    // childrens
    Children *children = ecs_get_mut(world, e, Children);
    spawn_zext_zigels(world, e, children, zextData, font_size, layer,
        position2D, zext_size);
    ecs_modified(world, e, Children);
    return e;
}