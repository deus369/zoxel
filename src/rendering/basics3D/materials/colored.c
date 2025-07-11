ecs_entity_t shader_colored3D;
ecs_entity_t material_colored3D;

typedef struct {
    GLint vertex_position;
    GLint vertex_color;
    GLuint transform_matrix;
    GLuint camera_matrix;
    GLuint brightness;
    GLuint fog_data;
} MaterialColored3D;
zox_custom_component(MaterialColored3D)

MaterialColored3D create_MaterialColored3D(const GLuint material) {
    return (MaterialColored3D) {
        glGetAttribLocation(material, "vertex_position"),
        glGetAttribLocation(material, "vertex_color"),
        glGetUniformLocation(material, "transform_matrix"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "brightness"),
        glGetUniformLocation(material, "fog_data")
    };
}

ecs_entity_t spawn_shader_colored3D(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "colored3D.vert");
    char* frag = get_shader_source(world, "colored3D.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
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