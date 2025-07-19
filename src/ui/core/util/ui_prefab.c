void add_ui_mesh(ecs_world_t *world, const ecs_entity_t e) {
    // this is more mesh stuff
    zox_add_tag(e, ElementRender)
    zox_prefab_set(e, RenderDisabled, { 0 })
    if (!headless) {
        zox_prefab_set(e, MeshDirty, { mesh_state_trigger })
        zox_prefab_set(e, MeshAlignment, { zox_mesh_alignment_centred })
        zox_prefab_add(e, MeshIndicies)
        zox_prefab_set(e, MeshVertices2D, { 0, NULL })
        zox_prefab_add(e, MeshUVs)
        zox_prefab_set(e, MeshGPULink, { { 0, 0 } })
        zox_prefab_set(e, TextureGPULink, { 0 })
        zox_prefab_set(e, UvsGPULink, { 0 })
        prefab_set_mesh_indicies(world, e, square_indicies, 6);
        // prefab_set_mesh2D_vertices(world, e, square_vertices, 4);
        prefab_set_mesh2D_vertices(world, e, NULL, 0);
        prefab_set_mesh_uvs_float2(world, e, square_uvs, 4);
    }
}

void add_ui_plus_components(ecs_world_t *world, const ecs_entity_t e) {
    // layout2D
    zox_prefab_set(e, Position2D, { float2_zero })
    zox_prefab_set(e, Rotation2D, { 0 })
    zox_prefab_set(e, Scale1D, { 1 })
    // Elements
    zox_add_tag(e, Element)
    zox_prefab_set(e, InitializeElement, { 1 })
    zox_prefab_set(e, PixelPosition, { int2_zero })
    zox_prefab_set(e, PixelSize, { int2_zero })
    zox_prefab_set(e, Anchor, { float2_zero })
    zox_prefab_set(e, CanvasPosition, { int2_zero })
    zox_prefab_set(e, Layer2D, { 0 })
    zox_prefab_set(e, CanvasLink, { 0 })
    // Rendering
    zox_prefab_set(e, Brightness, { 1 })
    zox_prefab_set(e, Alpha, { 1 })
    add_ui_mesh(world, e);
    // texture
    zox_add_tag(e, Texture)
    zox_prefab_set(e, TextureData, { 0, NULL })
    zox_prefab_set(e, TextureSize, { int2_zero })
    zox_prefab_set(e, TextureDirty, { 0 })
    zox_prefab_set(e, Seed, { 666 })
    zox_prefab_set(e, GenerateTexture, { zox_generate_texture_trigger })
}