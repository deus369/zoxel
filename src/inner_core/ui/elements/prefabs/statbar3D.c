ecs_entity_t prefab_statbar3D;

ecs_entity_t spawn_prefab_statbar3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_element_world)
    zox_name("prefab_statbar")
    // zox_add_tag(e, Statbar)
    zox_set(e, Children, { 0, NULL })
    ecs_defer_end(world);
    prefab_statbar3D = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab statbar [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_statbar3D(ecs_world_t *world, ecs_entity_t ui_holder) {
    int2 pixel_size = (int2) { 1, 1 }; // 12, 6
    zox_instance(prefab_statbar3D)
    zox_set_only(e, UIHolderLink, { ui_holder })
    zox_set_only(e, CameraLink, { main_cameras[0] })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, PixelSize, { pixel_size })
    zox_set_only(e, TextureSize, { pixel_size })
    // spawn child, percentage overlay
    Children children = { };
    initialize_memory_component_non_pointer(children, ecs_entity_t, 1);
    children.value[0] = spawn_element3D_attach(world, ui_holder, e, (float3) { 0, 0.0f, 0.010f }); // 0.006
    zox_set_only(e, Children, { children.length, children.value })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned prefab element_world [%lu]\n", (long int) e);
    #endif
    return e;
}