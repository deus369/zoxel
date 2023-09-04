void add_ui_components_world(ecs_world_t *world, ecs_entity_t e) {
    add_seed(world, e, 666);
    add_dirty(world, e);
    add_texture(world, e, int2_zero, 0);
    add_ui_components(world, e);
    add_transform3Ds(world, e);
    zox_set(e, Brightness, { 1 })
    zox_set(e, MeshDirty, { 0 })
    // add_gpu_instanced_material(world, e);
    if (!headless) {
        add_gpu_mesh(world, e);
        add_gpu_uvs(world, e);
        add_gpu_colors(world, e);
        add_gpu_texture(world, e);
        prefab_set_mesh_indicies(world, e, square_indicies, 6);
        prefab_set_mesh3D_vertices(world, e, square_vertices, 4);
        prefab_set_mesh_uvs(world, e, square_uvs, 4);
        prefab_set_mesh_colors_rgb(world, e, (color_rgb) { 255, 155, 155 }, 4);
    }
}