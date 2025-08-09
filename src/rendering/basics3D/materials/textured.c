entity shader_textured3D;
entity material_textured3D;

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
zoxc_custom(MaterialTextured3D);

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

entity spawn_shader_textured3D(ecs *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "textured3D.vert");
    char* frag = get_shader_source(world, "textured3D.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const entity e = spawn_shader(world, shader_index);
    if (!e) {
        zox_log_error("[shader_textured3D] failed to spawn")
        return 0;
    }
    zox_name("shader_textured3D")
    return e;
}

entity spawn_material_textured3D(ecs *world) {
    const entity shader = spawn_shader_textured3D(world);
    if (!shader) {
        return 0;
    }
    uint material;
    const entity e = spawn_material(world, shader, &material);
    zox_set(e, ShaderLink, { shader })
    const MaterialTextured3D attributes = create_MaterialTextured3D(material);
    zox_set_data(e, MaterialTextured3D, attributes)
    material_textured3D = e;
    shader_textured3D = shader;
    return e;
}