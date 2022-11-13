ecs_entity_t zigel_prefab;

// an individual text character entity.
ecs_entity_t spawn_zigel_prefab(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "zigel_prefab");
    printf("spawn_prefab zigel [%lu].\n", (long int) (e));
    zoxel_add_tag(world, e, Zigel);
    zoxel_add_component(world, e, ZigelIndex);
    zoxel_add_tag(world, e, FontTexture);
    add_ui_plus_components(world, e);
    // zoxel_set_component(world, e, SelectableState, { 0 });
    zigel_prefab = e;
    return e;
}

ecs_entity_t spawn_zigel(ecs_world_t *world, ecs_entity_t zext, unsigned char index,
    int2 position, int2 size, float2 anchor, unsigned char layer)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, zigel_prefab);
    zoxel_set_component(world, e, ZigelIndex, { index });
    initialize_ui_components(world, e, zext, position, size, anchor, layer);
    return e;
}