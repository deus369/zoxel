void add_ui_components(ecs_world_t *world, const ecs_entity_t e) {
    zox_add_tag(e, Element)
    zox_prefab_set(e, InitializeElement, { 1 })
    zox_prefab_set(e, PixelPosition, { int2_zero })
    zox_prefab_set(e, PixelSize, { int2_zero })
    zox_prefab_set(e, Anchor, { float2_zero })
    zox_prefab_set(e, CanvasPosition, { int2_zero })
    zox_prefab_set(e, Layer2D, { 0 })
    zox_prefab_set(e, CanvasLink, { 0 })
}

void add_ui_mesh(ecs_world_t *world, const ecs_entity_t e) {
    if (headless) return;
    add_gpu_mesh(world, e);
    add_gpu_texture(world, e);
    add_gpu_uvs(world, e);
    zox_prefab_set(e, MeshDirty, { 0 })
    zox_prefab_set(e, MeshAlignment, { zox_mesh_alignment_centred })
    zox_prefab_add(e, MeshIndicies)
    zox_prefab_add(e, MeshVertices2D)
    zox_prefab_add(e, MeshUVs)
    prefab_set_mesh_indicies(world, e, square_indicies, 6);
    prefab_set_mesh2D_vertices(world, e, square_vertices, 4);
    prefab_set_mesh_uvs_float2(world, e, square_uvs, 4);
    // this is more mesh stuff
    zox_add_tag(e, ElementRender)
    zox_prefab_set(e, RenderDisabled, { 0 })
}

void add_ui_mesh_components(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, Brightness, { 1 })
    zox_prefab_set(e, Alpha, { 1 })
    add_ui_mesh(world, e);
}

void add_components_ui_basic(ecs_world_t *world, const ecs_entity_t e) {
    add_transform2Ds(world, e);
    add_ui_components(world, e);
    add_ui_mesh_components(world, e);
    prefab_add_texture(world, e, int2_zero);
}

void add_ui_plus_components(ecs_world_t *world, const ecs_entity_t e) {
    add_transform2Ds(world, e);
    add_ui_components(world, e);
    add_ui_mesh_components(world, e);
    prefab_add_texture_generated(world, e, int2_zero, zox_generate_texture_trigger);
}

void add_ui_plus_components_invisible(ecs_world_t *world, const ecs_entity_t e) {
    add_seed(world, e, 666);
    add_transform2Ds(world, e);
    add_ui_components(world, e);
}

void add_clickable_components(ecs_world_t *world, const ecs_entity_t e) {
    zox_add_tag(e, Clickable)
    zox_prefab_set(e, ClickState, { 0 })
    zox_prefab_set(e, Clicker, { 0 })
    zox_prefab_set(e, ClickEvent, { NULL })
}

void add_selectable(ecs_world_t *world, const ecs_entity_t e) {
    zox_add_tag(e, Selectable)
}

void add_selectable_components(ecs_world_t *world, const ecs_entity_t e) {
    add_selectable(world, e);
    zox_prefab_set(e, SelectState, { zox_select_state_none })
}

void add_activatable_components(ecs_world_t *world, const ecs_entity_t e) {
    zox_prefab_set(e, ActiveState, { 0 })
}

void add_draggable_components(ecs_world_t *world, const ecs_entity_t e) {
    zox_add_tag(e, Dragable)
    zox_prefab_set(e, DraggableState, { 0 })
    zox_prefab_set(e, DraggingDelta, { int2_zero })
    zox_prefab_set(e, DraggerLink, { 0 })
    zox_prefab_set(e, DraggedLink, { 0 })
}

void add_mouse_follow_components(ecs_world_t *world, const ecs_entity_t e) {
    zox_add_tag(e, MouseElement)
    zox_prefab_set(e, ZeviceLink, { 0 })
}
