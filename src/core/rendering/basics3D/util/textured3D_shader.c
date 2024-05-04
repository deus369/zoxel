ecs_entity_t shader_textured3D;
ecs_entity_t material_textured3D;

ecs_entity_t spawn_shader_textured3D(ecs_world_t *world) {
    const unsigned char shader_index = get_new_shader_source_index();
    shader_verts[shader_index] = shader3D_textured_vert_buffer;
    shader_frags[shader_index] = shader3D_textured_frag_buffer;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_textured3D")
    return e;
}

ecs_entity_t spawn_material_textured3D(ecs_world_t *world) {
    const ecs_entity_t shader = spawn_shader_textured3D(world);
    const ecs_entity_t e = spawn_material(world, shader);
    zox_set(e, ShaderLink, { shader })
    const GLuint material = zox_get_value(e, MaterialGPULink)
    const MaterialTextured3D attributes = create_MaterialTextured3D(material);
    zox_set_data(e, MaterialTextured3D, attributes)
    material_textured3D = e;
    shader_textured3D = shader;
    return e;
}
