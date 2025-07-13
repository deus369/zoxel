void add_element3D_transform(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    // element components
    zox_add_tag(e, Element)
    zox_prefab_set(e, InitializeElement, { 1 })
    zox_prefab_set(e, PixelPosition, { int2_zero })
    zox_prefab_set(e, PixelSize, { int2_zero })
    zox_prefab_set(e, Anchor, { float2_zero })
    zox_prefab_set(e, CanvasPosition, { int2_zero })
    zox_prefab_set(e, Layer2D, { 0 })
    zox_prefab_set(e, CanvasLink, { 0 })
}

void add_element3D_child(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, LocalPosition3D, { float3_zero })
    zox_prefab_set(e, LocalRotation3D, { quaternion_identity })
    zox_prefab_set(e, ParentLink, { 0 })
}

void add_ui_components_world(ecs_world_t *world, const ecs_entity_t e, const float2 mesh_scale) {
    add_element3D_transform(world, e);
    zox_prefab_set(e, MeshDirty, { 0 })
    zox_prefab_set(e, Brightness, { 1 })
    zox_prefab_set(e, RenderDisabled, { 1 })
    prefab_add_texture_generated(world, e, int2_zero, zox_generate_texture_trigger);
    if (!headless) {
        add_gpu_texture(world, e);
        add_gpu_mesh(world, e);
        add_gpu_uvs(world, e);
        add_gpu_colors(world, e);
        zox_prefab_add(e, MeshIndicies)
        zox_prefab_add(e, MeshVertices)
        zox_prefab_add(e, MeshUVs)
        zox_prefab_add(e, MeshColorRGBs)
        prefab_set_mesh_indicies(world, e, square_indicies, 6);
        prefab_set_mesh3D_vertices(world, e, square_vertices, 4, mesh_scale);
        prefab_set_mesh_uvs_float2(world, e, square_uvs, 4);
        prefab_set_mesh_colors_rgb(world, e, (color_rgb) { 255, 255, 255 }, 4);
    }
}
