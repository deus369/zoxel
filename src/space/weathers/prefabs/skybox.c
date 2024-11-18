ecs_entity_t spawn_prefab_skybox(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_skybox")
    zox_add_tag(e, Skybox)
    add_transform3Ds(world, e, 1);
    zox_add(e, ColorRGB)
    zox_add(e, SecondaryColorRGB)
    zox_add(e, Brightness)
    zox_prefab_set(e, MeshDirty, { mesh_state_trigger })
    if (!headless) {
        zox_prefab_add(e, MeshIndicies)
        zox_prefab_add(e, MeshVertices)
        prefab_set_mesh_indicies(world, e, cube_indicies_inverted, cube_indicies_length);
        prefab_set_mesh_vertices_float(world, e, cube_vertices_singles, cube_vertices_singles_length);
        add_gpu_mesh(world, e);
        zox_prefab_set(e, ShaderLink, { 0 })
        add_gpu_material(world, e);
    }
    zox_set(e, Position3D, { float3_zero })
    zox_set(e, Brightness, { 1 })
    prefab_skybox = e;
    return e;
}

void set_sky_color_2(ecs_world_t *world, const GLuint material, const float3 top_color, const float3 bottom_color) {
    if (headless || !skybox) return;
    zox_set(skybox, ColorRGB, { color_rgb_from_float3(top_color) })
    zox_set(skybox, SecondaryColorRGB, { color_rgb_from_float3(bottom_color) })
    opengl_set_material(material);
    opengl_set_float3(glGetUniformLocation(material, "sky_top_color"), top_color);
    opengl_set_float3(glGetUniformLocation(material, "sky_bottom_color"), bottom_color);
    opengl_set_material(0);
}

void set_sky_color(ecs_world_t *world, const float3 top_color, const float3 bottom_color) {
    if (headless || !skybox) return;
    GLuint material = zox_get_value(skybox, MaterialGPULink)
    set_sky_color_2(world, material, top_color, bottom_color);
}

ecs_entity_t spawn_skybox(ecs_world_t *world, const ecs_entity_t shader) {
    zox_instance(prefab_skybox)
    skybox = e;
    zox_name("skybox")
    zox_set(e, Scale1D, { skybox_scale })
    if (!headless && !is_using_vulkan && shader) {
        spawn_gpu_mesh(world, e);
        GLuint2 shader_skybox_value = get_shader_value(world, shader);
        GLuint material = spawn_gpu_material(world, e, shader_skybox_value);
        set_sky_color_2(world, material, menu_sky_color, menu_sky_bottom_color);
        zox_set(e, ShaderLink, { shader })
    }
    return e;
}
