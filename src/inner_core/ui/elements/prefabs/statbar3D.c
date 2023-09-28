ecs_entity_t prefab_statbar3D;
ecs_entity_t prefab_statbar3D_front;
const float2 statbar_front_mesh_scale = (float2) { 0.17f, 0.028f };
// todo: link to health stat, in health system, update percentge when heath value updates
// todo: in another system, regen the health value up to max of the stat max

ecs_entity_t spawn_prefab_statbar3D(ecs_world_t *world) {
    color bar_color = (color) { 66, 12, 12, 0 };
    // color bar_color = (color) { 222, 166, 166, 0 };
    zox_prefab_child(prefab_element_world)
    zox_prefab_name("prefab_statbar")
    zox_set(e, ElementBar, { 1 })
    zox_set(e, ElementBarSize, { float2_zero })
    zox_set(e, Children, { 0, NULL })
    zox_set_only(e, PixelSize, { int2_one })
    zox_set_only(e, TextureSize, { int2_one })
    zox_set_only(e, Color, { bar_color })
    prefab_statbar3D = e;
    #ifdef zoxel_debug_prefabs
        zox_log("   > spawn_prefab statbar [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_prefab_statbar3D_front(ecs_world_t *world) {
    color bar_color = (color) { 188, 25, 25, 255 };
    zox_prefab_child(prefab_element_world_child)
    zox_prefab_name("prefab_statbar_front")
    zox_add_tag(e, FillTexture)
    zox_set_only(e, Color, { bar_color })
    zox_set_only(e, PixelSize, { int2_one })
    zox_set_only(e, TextureSize, { int2_one })
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, statbar_front_mesh_scale);
    // zox_set_only(e, Color, {{ 188, 25, 25, 255 }})
    // prefab_set_mesh_colors_rgb(world, e, (color_rgb) { bar_color.r, bar_color.g, bar_color.b }, 4);
    prefab_statbar3D_front = e;
    #ifdef zoxel_debug_prefabs
        zox_log("   > spawn_prefab statbar [%lu].\n", e)
    #endif
    return e;
}

// used atm for statbar front bar
ecs_entity_t spawn_statbar3D_front(ecs_world_t *world, ecs_entity_t ui_holder, ecs_entity_t parent, float3 offset) {
    zox_instance(prefab_statbar3D_front)
    zox_set_only(e, CameraLink, { main_cameras[0] })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, ParentLink, { parent })
    zox_set_only(e, LocalPosition3D, { offset })
    // zoxel_log("has ui holder link still? %i \n", ecs_has(world, e, UIHolderLink));
    #ifdef zoxel_debug_spawns
        zox_log("   > spawned statbar3D_front [%lu]\n", e)
    #endif
    return e;
}

ecs_entity_t spawn_statbar3D(ecs_world_t *world, ecs_entity_t ui_holder, float percentage) {
    const float depth_difference = 0.012f;
    // float percentage_test = 0.08f + 0.98f * ((rand() % 100) * 0.01f);
    zox_instance(prefab_statbar3D)
    zox_set_only(e, UIHolderLink, { ui_holder })
    zox_set_only(e, CameraLink, { main_cameras[0] })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, ElementBar, { percentage })
    zox_set_only(e, ElementBarSize, { statbar_front_mesh_scale })
    // spawn child, percentage overlay
    Children *children = ecs_get_mut(world, e, Children);
    initialize_memory_component(children, ecs_entity_t, 1)
    children->value[0] = spawn_statbar3D_front(world, ui_holder, e, (float3) { 0, 0, depth_difference });
    ecs_modified(world, e, Children);
    #ifdef zoxel_debug_spawns
        zox_log(" > spawned statbar3D [%lu]\n", e)
    #endif
    return e;
}