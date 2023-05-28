ecs_entity_t header_prefab;

ecs_entity_t spawn_prefab_header(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_header")
    add_ui_plus_components(world, e);
    zox_add_tag(e, Header);
    zox_add_tag(e, FrameTexture);
    zox_set(e, Color, {{ 77, 44, 33, 255 }});
    zox_add(e, Children);
    zox_add_tag(e, Selectable);
    zox_set(e, SelectableState, { 0 });
    zox_add_tag(e, Dragable);
    zox_set(e, DragableState, { 0 });
    zox_set(e, DraggerLink, { 0 });
    zox_set(e, DraggingDelta, {{ 0, 0 }});
    ecs_defer_end(world);
    header_prefab = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab header [%lu].\n", (long int) (e));
    #endif
    return e;
}