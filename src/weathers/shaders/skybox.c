ecs_entity_t spawn_shader_skybox(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "skybox.vert");
    char* frag = get_shader_source(world, "skybox.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_skybox")
    return e;
}

void set_skybox_material_color(ecs_world_t *world, const GLuint material, const color_rgb top_color, const color_rgb bottom_color) {
    if (headless || !skybox) {
        return;
    }
    const float3 top_colorf = color_rgb_to_float3(top_color);
    const float3 bottom_colorf = color_rgb_to_float3(bottom_color);
    opengl_set_material(material);
    opengl_set_float3(glGetUniformLocation(material, "sky_top_color"), top_colorf);
    opengl_set_float3(glGetUniformLocation(material, "sky_bottom_color"), bottom_colorf);
    opengl_set_material(0);
}