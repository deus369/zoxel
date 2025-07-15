ecs_entity_t shader_textured3D;
ecs_entity_t material_textured3D;

typedef struct {
    GLint vertex_position;
    GLint vertex_uv;
    GLint vertex_color;
    uint transform_matrix;
    uint camera_matrix;
    uint texture;
    uint fog_data;
    uint brightness;
} MaterialTextured3D;
zox_custom_component(MaterialTextured3D)

MaterialTextured3D create_MaterialTextured3D(const uint material) {
    return (MaterialTextured3D) {
        glGetAttribLocation(material, "vertex_position"),
        glGetAttribLocation(material, "vertex_uv"),
        glGetAttribLocation(material, "vertex_color"),
        glGetUniformLocation(material, "transform_matrix"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "tex"),
        glGetUniformLocation(material, "fog_data"),
        glGetUniformLocation(material, "brightness") };
}

ecs_entity_t spawn_shader_textured3D(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "textured3D.vert");
    char* frag = get_shader_source(world, "textured3D.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_textured3D")
    return e;
}

ecs_entity_t spawn_material_textured3D(ecs_world_t *world) {
    const ecs_entity_t shader = spawn_shader_textured3D(world);
    if (!shader) {
        return 0;
    }
    uint material;
    const ecs_entity_t e = spawn_material(world, shader, &material);
    zox_set(e, ShaderLink, { shader })
    const MaterialTextured3D attributes = create_MaterialTextured3D(material);
    zox_set_data(e, MaterialTextured3D, attributes)
    material_textured3D = e;
    shader_textured3D = shader;
    return e;
}