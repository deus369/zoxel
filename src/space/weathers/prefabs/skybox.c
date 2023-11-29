const float skybox_scale = 1024.0f;
ecs_entity_t prefab_skybox;
ecs_entity_t skybox;

ecs_entity_t spawn_prefab_skybox(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_skybox")
#ifdef zoxel_transforms3D
    add_transform3Ds(world, e);
#endif
#ifdef zoxel_rendering
    zox_add(e, ColorRGB)
    zox_add(e, SecondaryColorRGB)
    zox_add(e, Brightness)
    zox_prefab_set(e, MeshDirty, { 1 })
    if (!headless) {
        zox_prefab_set(e, MeshIndicies, { 0, NULL })
        zox_prefab_set(e, MeshVertices, { 0, NULL })
        prefab_set_mesh_indicies(world, e, cube_indicies_inverted, 36);
        prefab_set_mesh_vertices(world, e, cube_vertices_singles, cube_vertices_singles_length);
    }
    add_gpu_mesh(world, e);
    add_gpu_material(world, e);
#endif
    zox_set(e, Position3D, { float3_zero })
    zox_set(e, Brightness, { 1 })
    prefab_skybox = e;
#ifdef zoxel_debug_prefabs
    zox_log(" + spawned prefab skybox [%lu]\n", e)
#endif
    return e;
}

ecs_entity_t spawn_skybox(ecs_world_t *world) {
    zox_instance(prefab_skybox)
    zox_name("skybox")
    zox_set(e, Scale1D, { skybox_scale })
    if (!headless) {
        spawn_gpu_mesh(world, e);
        GLuint2 shader_skybox_value = get_shader_value(world, shader_skybox);
        spawn_gpu_material(world, e, shader_skybox_value);
    }
    skybox = e;
    set_sky_color(world, menu_sky_color, menu_sky_bottom_color);
#ifdef zoxel_debug_spawns
    zox_log(" + spawned skybox [%lu]\n", e)
#endif
    return e;
}
