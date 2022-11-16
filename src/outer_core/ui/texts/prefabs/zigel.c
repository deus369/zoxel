// an individual text character entity.
ecs_entity_t spawn_zigel_prefab(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "zigel_prefab");
    #ifdef zoxel_debug_prefabs
    printf("spawn_prefab zigel [%lu].\n", (long int) (e));
    #endif
    zoxel_add_tag(world, e, Zigel);
    zoxel_set(world, e, ZigelIndex, { 0 });
    zoxel_add_tag(world, e, FontTexture);
    add_ui_plus_components(world, e);
    ecs_defer_end(world);
    // zoxel_set(world, e, SelectableState, { 0 });
    return e;
}