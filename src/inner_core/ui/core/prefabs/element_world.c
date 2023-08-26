ecs_entity_t prefab_element_world;
// todo: remove any canvas elements, these will just be world transform uis

void add_ui_components_world(ecs_world_t *world, ecs_entity_t e) {
    add_seed(world, e, 666);
    add_dirty(world, e);
    add_texture(world, e, int2_zero, 0);
    add_ui_components(world, e);
    add_transform3Ds(world, e);
    zox_set(e, Brightness, { 1 })
    zox_set(e, MeshDirty, { 0 })
    add_gpu_mesh(world, e);
    // add_gpu_instanced_material(world, e);
    add_gpu_uvs(world, e);
    add_gpu_colors(world, e);
    add_gpu_texture(world, e);
    prefab_set_mesh_indicies(world, e, square_indicies, 6);
    prefab_set_mesh3D_vertices(world, e, square_vertices, 4);
    prefab_set_mesh_uvs(world, e, square_uvs, 4);
    prefab_set_mesh_colors_rgb(world, e, (color_rgb) { 255, 155, 155 }, 4);
}

ecs_entity_t spawn_prefab_element3D(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_add_tag(e, Element3D)
    zox_add_tag(e, ElementBillboard)
    add_ui_components_world(world, e);
    zox_add_tag(e, FrameTexture)
    zox_set(e, FrameCorner, { 0 })
    zox_set(e, OutlineThickness, { 1 })
    zox_set(e, SelectableState, { 0 })
    zox_set(e, Color, {{ 125, 125, 125, 255 }})
    zox_add_tag(e, SingleMaterial)
    zox_set(e, CameraLink, { 0 })
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
    int2 pixel_size = (int2) { 32, 8 }; // 8
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