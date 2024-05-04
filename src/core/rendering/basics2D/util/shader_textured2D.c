ecs_entity_t shader_textured2D;
ecs_entity_t material_textured2D;

ecs_entity_t spawn_shader_textured2D(ecs_world_t *world) {
    const unsigned char shader_index = get_new_shader_source_index();
    shader_verts[shader_index] = shader2D_textured_vert_buffer;
    shader_frags[shader_index] = shader2D_textured_frag_buffer;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_textured2D")
    return e;
}

ecs_entity_t spawn_material_textured2D(ecs_world_t *world) {
    const ecs_entity_t shader = spawn_shader_textured2D(world);
    const ecs_entity_t e = spawn_material(world, shader);
    zox_set(e, ShaderLink, { shader })
    const GLuint material = zox_get_value(e, MaterialGPULink)
    const MaterialTextured2D attributes = create_MaterialTextured2D(material);
    zox_set_data(e, MaterialTextured2D, attributes)
    material_textured2D = e;
    shader_textured2D = shader;
    return e;
}
