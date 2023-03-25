ecs_entity_t header_prefab;

ecs_entity_t spawn_prefab_header(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "");
    set_unique_entity_name(world, e, "prefab_header");
    add_ui_plus_components(world, e);
    zoxel_add_tag(world, e, Header);
    zoxel_add_tag(world, e, FrameTexture);
    zoxel_add(world, e, Children);
    zoxel_add_tag(world, e, Selectable);
    zoxel_set(world, e, SelectableState, { 0 });
    zoxel_add_tag(world, e, Dragable);
    zoxel_set(world, e, DragableState, { 0 });
    zoxel_set(world, e, DraggerLink, { 0 });
    zoxel_set(world, e, DraggingDelta, {{ 0, 0 }});
    ecs_defer_end(world);
    header_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab header [%lu].\n", (long int) (e));
    #endif
    return e;
}