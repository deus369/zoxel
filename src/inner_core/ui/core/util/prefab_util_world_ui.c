void add_ui_components_world(ecs_world_t *world, const ecs_entity_t e, const float2 mesh_scale) {
    prefab_add_texture_generated(world, e, int2_zero, 0);
    add_ui_components(world, e);
    add_transform3Ds(world, e, 0);
    zox_prefab_set(e, TransformMatrix, { float4x4_identity() })
    zox_prefab_set(e, Brightness, { 1 })
    zox_prefab_set(e, MeshDirty, { 0 })
    zox_prefab_set(e, RenderDisabled, { 1 })
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
        prefab_set_mesh_uvs(world, e, square_uvs, 4);
        prefab_set_mesh_colors_rgb(world, e, (color_rgb) { 255, 255, 255 }, 4);
    }
}
