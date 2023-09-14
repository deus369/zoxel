ecs_entity_t prefab_element_world;
// todo: remove any canvas elements, these will just be world transform uis

ecs_entity_t spawn_prefab_element3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_add_tag(e, Element3D)
    add_ui_components_world(world, e, (float2) { 0.2f, 0.05f });
    zox_add_tag(e, FillTexture)
    // zox_set(e, FrameCorner, { 0 })
    // zox_set(e, OutlineThickness, { 1 })
    // zox_set(e, SelectState, { 0 })
    zox_set(e, Color, {{ 66, 12, 12, 0 }}) // todo: add alpha to a texture3D shader variant
    zox_add_tag(e, SingleMaterial)
    zox_set(e, CameraLink, { 0 })
    zox_add_tag(e, ElementBillboard)
    zox_set(e, UIHolderLink, { 0 })
    zox_set(e, UITrail, {{ 0, 0.33f, 0 }})
    ecs_defer_end(world);
    prefab_element_world = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawned prefab element_world [%lu].\n", (long int) (e));
    #endif
    return e;
}

// , ecs_entity_t camera, float3 offset
ecs_entity_t spawn_element3D(ecs_world_t *world, ecs_entity_t ui_holder) {
    int2 pixel_size = (int2) { 32, 8 };
    zox_instance(prefab_element_world)
    zox_set_only(e, UIHolderLink, { ui_holder })
    zox_set_only(e, CameraLink, { main_cameras[0] })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, PixelSize, { pixel_size })
    zox_set_only(e, TextureSize, { pixel_size })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned prefab element_world [%lu]\n", (long int) e);
    #endif
    return e;
}

// used atm for statbar front bar
ecs_entity_t spawn_element3D_attach(ecs_world_t *world, ecs_entity_t ui_holder, ecs_entity_t parent, float3 offset) {
    int2 pixel_size = (int2) { 1, 1 };
    float2 mesh_scale = (float2) { 0.17f, 0.028f };
    zox_instance(prefab_element_world)
    zox_set(e, ParentLink, { parent })
    zox_set(e, LocalPosition3D, { offset })
    zox_set_only(e, CameraLink, { main_cameras[0] })
    zox_set_only(e, CanvasLink, { main_canvas })
    zox_set_only(e, PixelSize, { pixel_size })
    zox_set_only(e, TextureSize, { pixel_size })
    zox_set_only(e, Color, {{ 188, 25, 25, 255 }})
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4, mesh_scale);
    // remove from normal prefab
    zox_remove(e, ElementBillboard)
    zox_remove(e, UIHolderLink)
    // zoxel_log("has ui holder link still? %i \n", ecs_has(world, e, UIHolderLink));
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned prefab element_world [%lu]\n", (long int) e);
    #endif
    return e;
}

//zox_set_only(e, UIHolderLink, { ui_holder })
//zox_set(e, UITrail, { offset })