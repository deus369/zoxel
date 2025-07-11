ecs_entity_t shader_render_texture;
ecs_entity_t material_render_texture;

ecs_entity_t spawn_shader_render_texture(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "render_texture.vert");
    char* frag = get_shader_source(world, "render_texture.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_render_texture")
    return e;
}

ecs_entity_t spawn_material_render_texture(ecs_world_t *world) {
    const ecs_entity_t shader = spawn_shader_render_texture(world);
    if (!shader) return 0;
    GLuint material;
    const ecs_entity_t e = spawn_material(world, shader, &material);
    zox_set(e, ShaderLink, { shader })
    const MaterialAttributesRenderTexture attributes = create_MaterialAttributesRenderTexture(material);
    zox_set_data(e, MaterialAttributesRenderTexture, attributes)
    material_render_texture = e;
    shader_render_texture = shader;
    return e;
}
