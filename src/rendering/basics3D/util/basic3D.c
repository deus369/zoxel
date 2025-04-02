ecs_entity_t shader_basic3D;
ecs_entity_t material_basic3D;

ecs_entity_t spawn_shader_basic3D(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    shader_verts[shader_index] = shader_basic3D_vert_buffer;
    shader_frags[shader_index] = shader_basic3D_frag_buffer;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_basic3D")
    return e;
}

ecs_entity_t spawn_material_basic3D(ecs_world_t *world) {
    const ecs_entity_t shader = spawn_shader_basic3D(world);
    if (!shader) {
        return 0;
    }
    GLuint material;
    const ecs_entity_t e = spawn_material(world, shader, &material);
    zox_name("material_basic3D")
    zox_set(e, ShaderLink, { shader })
    const MaterialBasic3D attributes = create_MaterialBasic3D(material);
    zox_set_data(e, MaterialBasic3D, attributes)
    shader_basic3D = shader;
    material_basic3D = e;
    return e;
}
