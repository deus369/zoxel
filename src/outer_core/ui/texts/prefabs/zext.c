ecs_entity_t zext_prefab;

// the ui text entity that holds zigels.
ecs_entity_t spawn_zext_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "zext_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab zext [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Zext);
    zoxel_add_component(world, e, ZextData);
    zoxel_add_component(world, e, ZextDirty);
    zoxel_add_component(world, e, Children);
    add_transform2Ds(world, e);
    // add_ui_components(world, e);
    add_ui_plus_components(world, e);
    zext_prefab = e;
    return e;
}

ecs_entity_t spawn_zext(ecs_world_t *world, ecs_entity_t parent, int2 position, float2 anchor,
    const char* text, int font_size, unsigned char layer)
{
    int textLength = strlen(text);
    int2 zigel_size = (int2) { font_size, font_size };
    int2 zext_size = (int2) { font_size * textLength, font_size };
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, zext_prefab);
    initialize_ui_components(world, e, parent, position, zext_size, anchor, layer);
    ecs_set(world, e, ZextDirty, { 1 });
    ZextData *zextData = ecs_get_mut(world, e, ZextData);
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(zextData, unsigned char, textLength);
    initialize_memory_component(children, ecs_entity_t, textLength);
    // printf("layer %i\n", layer);
    for (int i = 0; i < textLength; i++)
    {
        // convert normal char here to unsigned char!
        unsigned char zigel_index = convert_ascii(text[i]);
        zextData->value[i] = zigel_index;
        int2 zigel_position = (int2) {
            (int) (((float) zigel_size.x * i) - (zigel_size.x * textLength) / 2.0f) + zigel_size.x / 2,
            0 };
        children->value[i] = spawn_zigel(world, e, zigel_index,
            zigel_position, zigel_size,
            (float2) { 0.5f, 0.5f }, layer + 1);
        // printf("[%i]: %i\n", i, (int) zextData->value[i]);
    }
    ecs_modified(world, e, ZextData);
    ecs_modified(world, e, Children);
    return e;
}