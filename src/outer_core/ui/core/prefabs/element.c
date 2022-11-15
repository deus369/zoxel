ecs_entity_t element_prefab;

ecs_entity_t spawn_prefab_element(ecs_world_t *world)
{
    ecs_entity_t e = ecs_new_prefab(world, "element_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab element [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, FrameTexture);
    zoxel_set(world, e, SelectableState, { 0 });
    add_ui_plus_components(world, e);
    // printf("Spawned test_custom_mesh [%lu].\n", (long int) (e));
    // zoxel_add_tag(world, e, SaveTexture);
    element_prefab = e;
    return e;
}

ecs_entity_t spawn_element(ecs_world_t *world, ecs_entity_t parent, int2 position, int2 size, float2 anchor)
{
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, element_prefab);
    initialize_ui_components(world, e, parent, position, size, anchor, 0);
    // printf("Texture ratio: %f - ScaleRatio: %f\n", (size.x / (float) size.y), (scaledSize2D.x / scaledSize2D.y));
    //printf("UI Element Spawned - Position [%ix%i] - Size [%ix%i] - Position(Real) [%fx%f] - ScaledSize [%fx%f]\n",
    //    position.x, position.y, size.x, size.y, position2D.x, position2D.y, scaledSize2D.x, scaledSize2D.y);
    return e;
}