ecs_entity_t shader_textured2D = 0;
ecs_entity_t material_textured2D = 0;

ecs_entity_t spawn_shader_textured2D(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "textured2D.vert");
    char* frag = get_shader_source(world, "textured2D.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_textured2D")
    return e;
}

ecs_entity_t spawn_material_textured2D(ecs_world_t *world) {
    const ecs_entity_t shader = spawn_shader_textured2D(world);
    if (!shader) return 0;
    GLuint material;
    const ecs_entity_t e = spawn_material(world, shader, &material);
    zox_set(e, ShaderLink, { shader })
    const MaterialTextured2D attributes = create_MaterialTextured2D(material);
    zox_set_data(e, MaterialTextured2D, attributes)
    material_textured2D = e;
    shader_textured2D = shader;
    return e;
}
