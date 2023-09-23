ecs_entity_t prefab_statbar3D;
ecs_entity_t prefab_statbar3D_front;
const float2 statbar_front_mesh_scale = (float2) { 0.17f, 0.028f };

// todo: link to health stat, in health system, update percentge when heath value updates
// todo: in another system, regen the health value up to max of the stat max

ecs_entity_t spawn_prefab_statbar3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_element_world)
    zox_prefab_name("prefab_statbar")
    zox_set(e, ElementBar, { 1 })
    zox_set(e, ElementBarSize, { float2_zero })
    // zox_add_tag(e, Statbar)
    zox_set(e, Children, { 0, NULL })
    ecs_defer_end(world);
    prefab_statbar3D = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab statbar [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_prefab_statbar3D_front(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_element_world)
    zox_prefab_name("prefab_statbar_front")
    zox_remove(e, ElementBillboard)
    zox_remove(e, UIHolderLink)
    // zox_add_tag(e, Statbar)
    zox_set(e, ParentLink, { 0 })
    zox_set(e, LocalPosition3D, { float3_zero })
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, statbar_front_mesh_scale);
    ecs_defer_end(world);
    prefab_statbar3D_front = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log("spawn_prefab statbar [%lu].\n", (long int) (e));
    #endif
    return e;
}

// used atm for statbar front bar
ecs_entity_t spawn_statbar3D_front(ecs_world_t *world, ecs_entity_t ui_holder, ecs_entity_t parent, float3 offset) {
    int2 pixel_size = (int2) { 1, 1 };
    zox_instance(prefab_statbar3D_front)
    zox_set_only(e, CameraLink, { main_cameras[0] })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, PixelSize, { pixel_size })
    zox_set_only(e, TextureSize, { pixel_size })
    zox_set_only(e, Color, {{ 188, 25, 25, 255 }})
    zox_set(e, ParentLink, { parent })
    zox_set(e, LocalPosition3D, { offset })
    // zoxel_log("has ui holder link still? %i \n", ecs_has(world, e, UIHolderLink));
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned prefab element_world [%lu]\n", (long int) e);
    #endif
    return e;
}

ecs_entity_t spawn_statbar3D(ecs_world_t *world, ecs_entity_t ui_holder) {
    const float depth_difference = 0.012f;
    float percentage_test = 0.02f + 0.98f * ((rand() % 100) * 0.01f);
    // zoxel_log(" > percentage_test [%f]\n", percentage_test);
    int2 pixel_size = (int2) { 1, 1 }; // 12, 6
    zox_instance(prefab_statbar3D)
    zox_set_only(e, UIHolderLink, { ui_holder })
    zox_set_only(e, CameraLink, { main_cameras[0] })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, PixelSize, { pixel_size })
    zox_set_only(e, TextureSize, { pixel_size })
    zox_set_only(e, ElementBar, { percentage_test })
    zox_set_only(e, ElementBarSize, { statbar_front_mesh_scale })
    // spawn child, percentage overlay
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 1)
    children->value[0] = spawn_statbar3D_front(world, ui_holder, e, (float3) { 0, 0, depth_difference });
    ecs_modified(world, e, Children);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned prefab element_world [%lu]\n", (long int) e);
    #endif
    return e;
}