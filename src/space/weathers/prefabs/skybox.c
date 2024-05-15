const float skybox_scale = 1024.0f;
ecs_entity_t prefab_skybox;
ecs_entity_t skybox;

ecs_entity_t spawn_prefab_skybox(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_skybox")
    zox_add_tag(e, Skybox)
    add_transform3Ds(world, e);
    zox_add(e, ColorRGB)
    zox_add(e, SecondaryColorRGB)
    zox_add(e, Brightness)
    zox_prefab_set(e, MeshDirty, { 1 })
    if (!headless) {
        zox_prefab_set(e, MeshIndicies, { 0, NULL })
        zox_prefab_set(e, MeshVertices, { 0, NULL })
        prefab_set_mesh_indicies(world, e, cube_indicies_inverted, 36);
        prefab_set_mesh_vertices(world, e, cube_vertices_singles, cube_vertices_singles_length);
        add_gpu_mesh(world, e);
        zox_prefab_set(e, ShaderLink, { 0 })
        add_gpu_material(world, e);
    }
    zox_set(e, Position3D, { float3_zero })
    zox_set(e, Brightness, { 1 })
    prefab_skybox = e;
    return e;
}

void set_sky_color(ecs_world_t *world, float3 top_color, float3 bottom_color) {
    if (headless) return;
    GLuint material = zox_get_value(skybox, MaterialGPULink)
    opengl_set_material(material);
    opengl_set_float3(glGetUniformLocation(material, "sky_top_color"), top_color);
    opengl_set_float3(glGetUniformLocation(material, "sky_bottom_color"), bottom_color);
    opengl_set_material(0);
    zox_set(skybox, ColorRGB, { color_rgb_from_float3(top_color) })
    zox_set(skybox, SecondaryColorRGB, { color_rgb_from_float3(bottom_color) })
}

ecs_entity_t spawn_skybox(ecs_world_t *world) {
    zox_instance(prefab_skybox)
    skybox = e;
    zox_name("skybox")
    zox_set(e, Scale1D, { skybox_scale })
    if (!headless && !is_using_vulkan) {
        spawn_gpu_mesh(world, e);
        GLuint2 shader_skybox_value = get_shader_value(world, shader_skybox);
        spawn_gpu_material(world, e, shader_skybox_value);
        set_sky_color(world, menu_sky_color, menu_sky_bottom_color);
        zox_set(e, ShaderLink, { shader_skybox })
    }
    return e;
}
