ecs_entity_t zext_prefab;

// the ui text entity that holds zigels.
ecs_entity_t spawn_zext_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "zext_prefab");
    zoxel_add_tag(world, e, Zext);
    zoxel_add_component(world, e, ZextData);
    zoxel_add_component(world, e, Children);
    add_transform2Ds(world, e);
    zext_prefab = e;
    return e;
}

ecs_entity_t spawn_zext(ecs_world_t *world, float2 position2D, const char* text)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, zext_prefab);
    ecs_set(world, e, Position2D, { position2D });
    ZextData *zextData = ecs_get_mut(world, e, ZextData);
    int textLength = strlen(text);
    initialize_memory_component(zextData, unsigned char, textLength);
    for (int i = 0; i < textLength; i++)
    {
        // convert normal char here to unsigned char!
        zextData->value[i] = text[i];
        // printf("[%i]: %i\n", i, (int) zextData->value[i]);
    }
    ecs_modified(world, e, ZextData);
    return e;
}