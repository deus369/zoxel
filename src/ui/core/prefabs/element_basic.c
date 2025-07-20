ecs_entity_t spawn_prefab_element_shell(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("element_basic")
    // texture
    zox_add_tag(e, Texture)
    zox_prefab_set(e, TextureData, { 0, NULL })
    zox_prefab_set(e, TextureSize, { int2_zero })
    // zox_prefab_set(e, TextureDirty, { 0 })
    // zox_prefab_set(e, Color, { color_white })   // do i need this here? does basic lack texture info for generation?
    // # Rendering#
    zox_add_tag(e, ElementRender)
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, Brightness, { 1 })
    zox_prefab_set(e, Alpha, { 1 })
    if (!headless) {
        zox_prefab_set(e, MeshDirty, { mesh_state_trigger })
        zox_prefab_set(e, MeshAlignment, { zox_mesh_alignment_centred })
        zox_prefab_add(e, MeshIndicies)
        zox_prefab_add(e, MeshVertices2D)
        zox_prefab_add(e, MeshUVs)
        zox_prefab_set(e, MeshGPULink, { { 0, 0 } })
        zox_prefab_set(e, TextureGPULink, { 0 })
        zox_prefab_set(e, UvsGPULink, { 0 })
        prefab_set_mesh_indicies(world, e, square_indicies, 6);
        // prefab_set_mesh2D_vertices(world, e, square_vertices, 4);
        prefab_set_mesh2D_vertices(world, e, NULL, 0);
        prefab_set_mesh_uvs_float2(world, e, square_uvs, 4);
    }
    return e;
}

ecs_entity_t spawn_prefab_element_ready(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("element_ready")
    zox_prefab_set(e, TextureDirty, { 0 })
    zox_prefab_set(e, Color, { color_white })   // do i need this here? does basic lack texture info for generation?
    return e;
}