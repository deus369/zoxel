ecs_entity_t spawn_prefab_skybox(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("skybox")
    zox_add_tag(e, Skybox)
    zox_prefab_set(e, Position3D, { float3_zero })
    zox_prefab_set(e, Rotation3D, { float4_identity })
    zox_prefab_set(e, Scale1D, { 1 })
    zox_prefab_set(e, TransformMatrix, { float4x4_identity })
    zox_prefab_add(e, ColorRGB)
    zox_prefab_add(e, SecondaryColorRGB)
    zox_prefab_set(e, Brightness, { 1 })
    zox_prefab_set(e, MeshDirty, { mesh_state_trigger_slow })
    if (!headless) {
        zox_prefab_add(e, MeshIndicies)
        zox_prefab_add(e, MeshVertices)
        add_gpu_mesh(world, e);
        zox_prefab_set(e, ShaderLink, { 0 })
        add_gpu_material(world, e);
        prefab_set_mesh_indicies(world, e, cube_indicies_inverted, cube_indicies_length);
        prefab_set_mesh_vertices_float(world, e, cube_vertices_inverted, cube_vertices_f_length);
        //prefab_set_mesh_indicies(world, e, cube2_indicies, cube2_indicies_length);
        //prefab_set_mesh_vertices_float3(world, e, cube2_vertices, cube2_vertices_length);
    }
    prefab_skybox = e;
    return e;
}

void set_skybox_colors(ecs_world_t *world, const color_rgb top_color, const color_rgb bottom_color) {
    if (headless || !skybox) {
        return;
    }
    zox_set(skybox, ColorRGB, { top_color })
    zox_set(skybox, SecondaryColorRGB, { bottom_color })
    zox_geter_value(skybox, MaterialGPULink, uint, material)
    set_skybox_material_color(world, material, top_color, bottom_color);
}

ecs_entity_t spawn_skybox(ecs_world_t *world, const ecs_entity_t shader) {
    zox_instance(prefab_skybox)
    skybox = e;
    zox_name("skybox")
    zox_set(e, Scale1D, { skybox_size })
    if (render_backend == zox_render_backend_opengl && shader) {
        zox_add_tag(e, MeshBasic3D)
        spawn_gpu_mesh(world, e);
        zox_set(e, ShaderLink, { shader })
        uint2 shader_skybox_value = get_shader_value(world, shader);
        uint material = spawn_gpu_material(world, e, shader_skybox_value);
        set_skybox_material_color(world, material, menu_sky_color, menu_sky_bottom_color);
    }
    return e;
}