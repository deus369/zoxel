ecs_entity_t zext_prefab;

// the ui text entity that holds zigels.
ecs_entity_t spawn_zext_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "zext_prefab");
    zoxel_add_tag(world, e, Zext);
    zoxel_add_component(world, e, ZextData);
    zoxel_add_component(world, e, ZextDirty);
    zoxel_add_component(world, e, Children);
    add_transform2Ds(world, e);
    zext_prefab = e;
    return e;
}

ecs_entity_t spawn_zext(ecs_world_t *world, int2 pixel_position, float2 anchor, const char* text)
{
    int font_size = 32;
    int2 zigel_size = (int2) { font_size, font_size };
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, zext_prefab);
    ecs_set(world, e, ZextDirty, { 1 });
    // ecs_set(world, e, Position2D, { position2D });
    ZextData *zextData = ecs_get_mut(world, e, ZextData);
    Children *children = ecs_get_mut(world, e, Children);
    int textLength = strlen(text);
    initialize_memory_component(zextData, unsigned char, textLength);
    initialize_memory_component(children, ecs_entity_t, textLength);
    for (int i = 0; i < textLength; i++)
    {
        // convert normal char here to unsigned char!
        unsigned char zigel_index = convert_ascii(text[i]);
        zextData->value[i] = zigel_index;
        children->value[i] = spawn_zigel(world, e, zigel_index,
            (int2) {
                pixel_position.x + (zigel_size.x * i) - zigel_size.x * (textLength / 2),
                pixel_position.y - zigel_size.y / 2 },
            zigel_size, anchor);
        // printf("[%i]: %i\n", i, (int) zextData->value[i]);
    }
    ecs_modified(world, e, ZextData);
    ecs_modified(world, e, Children);
    return e;
}