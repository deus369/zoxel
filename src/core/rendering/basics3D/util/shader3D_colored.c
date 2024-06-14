ecs_entity_t shader_colored3D;
ecs_entity_t material_colored3D;

ecs_entity_t spawn_shader_colored3D(ecs_world_t *world) {
    const unsigned char shader_index = get_new_shader_source_index();
    shader_verts[shader_index] = shader3D_colored_vert_buffer;
    shader_frags[shader_index] = shader3D_colored_frag_buffer;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_colored3D")
    return e;
}

ecs_entity_t spawn_material_colored3D(ecs_world_t *world) {
    const ecs_entity_t shader = spawn_shader_colored3D(world);
    if (!shader) return 0;
    GLuint material;
    const ecs_entity_t e = spawn_material(world, shader, &material);
    zox_set(e, ShaderLink, { shader })
    const MaterialColored3D attributes = create_MaterialColored3D(material);
    zox_set_data(e, MaterialColored3D, attributes)
    material_colored3D = e;
    shader_colored3D = shader;
    return e;
}
