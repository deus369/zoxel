void add_ui_components(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, Element)
    zox_add_tag(e, ElementRender)
    zox_prefab_set(e, RenderDisabled, { 0 })
    zox_prefab_set(e, PixelPosition, { int2_zero })
    zox_prefab_set(e, PixelSize, { int2_zero })
    zox_prefab_set(e, CanvasPixelPosition, { int2_zero })
    zox_prefab_set(e, Anchor, { { 0 } })
    zox_prefab_set(e, CanvasLink, { 0 })
    zox_prefab_set(e, Layer2D, { 0 })
    zox_prefab_set(e, MeshAlignment, { 0 })
    zox_prefab_set(e, InitializeEntityMesh, { 1 })
}

void add_ui_mesh_components(ecs_world_t *world, ecs_entity_t e) {
    zox_prefab_set(e, Brightness, { 1 })
    zox_prefab_set(e, Alpha, { 1 })
    zox_prefab_set(e, MeshDirty, { 0 })
    zox_prefab_set(e, MeshIndicies, { 0, NULL })
    zox_prefab_set(e, MeshVertices2D, { 0, NULL })
    zox_prefab_set(e, MeshUVs, { 0, NULL })
    add_gpu_mesh(world, e);
    add_gpu_instanced_material(world, e);
    add_gpu_texture(world, e);
    add_gpu_uvs(world, e);
    prefab_set_mesh_indicies(world, e, square_indicies, 6);
    prefab_set_mesh2D_vertices(world, e, square_vertices, 4);
    prefab_set_mesh_uvs(world, e, square_uvs, 4);
}

void add_ui_plus_components(ecs_world_t *world, ecs_entity_t e) {
    add_seed(world, e, 666);
    add_transform2Ds(world, e);
    add_ui_components(world, e);
    add_texture(world, e, int2_zero, 0);
    if (!headless) add_ui_mesh_components(world, e);
}

void add_ui_plus_components_invisible(ecs_world_t *world, ecs_entity_t e) {
    add_seed(world, e, 666);
    add_transform2Ds(world, e);
    add_ui_components(world, e);
}

void add_clickable_components(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, Clickable)
    zox_prefab_set(e, ClickState, { 0 })
    zox_prefab_set(e, ClickEvent, { NULL })
}

void add_selectable_components(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, Selectable)
    zox_prefab_set(e, SelectState, { 0 })
}

void add_draggable_components(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, Dragable)
    zox_prefab_set(e, DraggableState, { 0 })
    zox_prefab_set(e, DraggingDelta, {{ 0, 0 }})
    zox_prefab_set(e, DraggerLink, { 0 })
    zox_prefab_set(e, DraggedLink, { 0 })
}

void add_frame_texture_type(ecs_world_t *world, ecs_entity_t e, color primary, unsigned char corner, unsigned char thickness) {
    zox_add_tag(e, FrameTexture)
    zox_prefab_set(e, FrameCorner, { corner })
    zox_prefab_set(e, OutlineThickness, { thickness })
    zox_prefab_set(e, Color, { primary })
}
