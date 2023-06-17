void add_ui_components(ecs_world_t *world, ecs_entity_t e) {
    zox_add_tag(e, Element)
    if (!headless) zox_add_tag(e, ElementRender)
    zox_set(e, PixelPosition, { int2_zero })
    zox_set(e, PixelSize, { int2_zero })
    zox_set(e, CanvasPixelPosition, { int2_zero })
    zox_set(e, Anchor, { { 0 } })
    zox_set(e, CanvasLink, { 0 })
    zox_set(e, Layer2D, { 0 })
    zox_set(e, InitializeEntityMesh, { 1 })
}

void add_ui_mesh_components(ecs_world_t *world, ecs_entity_t e) {
    zox_set(e, MeshDirty, { 0 })
    zox_set(e, Brightness, { 1 })
    add_gpu_mesh(world, e);
    add_gpu_material(world, e);
    add_gpu_texture(world, e);
    prefab_set_mesh_indicies(world, e, square_indicies, 6);
    prefab_set_mesh2D_vertices(world, e, square_vertices, 4);
    prefab_set_mesh_uvs(world, e, square_uvs, 4);
}

void add_ui_plus_components(ecs_world_t *world, ecs_entity_t e) {
    add_seed(world, e, 666);
    add_dirty(world, e);
    add_transform2Ds(world, e);
    add_texture(world, e, int2_zero, 0);
    add_ui_components(world, e);
    if (!headless) add_ui_mesh_components(world, e);
}

void add_ui_plus_components_invisible(ecs_world_t *world, ecs_entity_t e) {
    add_seed(world, e, 666);
    add_transform2Ds(world, e);
    add_ui_components(world, e);
}