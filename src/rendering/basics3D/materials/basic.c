entity shader_basic3D;
entity material_basic3D;

typedef struct {
    GLint vertex_position;
    uint transform_matrix;
    uint camera_matrix;
    uint fog_data;
    uint brightness;
} MaterialBasic3D;
zox_custom_component(MaterialBasic3D)

MaterialBasic3D create_MaterialBasic3D(const uint material) {
    return (MaterialBasic3D) {
        glGetAttribLocation(material, "vertex_position"),
        glGetUniformLocation(material, "transform_matrix"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "fog_data"),
        glGetUniformLocation(material, "brightness")
    };
}

entity spawn_shader_basic3D(ecs *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "basic3D.vert");
    char* frag = get_shader_source(world, "basic3D.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const entity e = spawn_shader(world, shader_index);
    if (!e) {
        zox_log_error("[shader_basic3D] failed to spawn")
        return 0;
    }
    zox_name("shader_basic3D")
    return e;
}

entity spawn_material_basic3D(ecs *world) {
    /*if (load_shader3D_basic(world)) {
        zox_log("    ! error loading [shader3D_basic]\n");
    }*/
    const entity shader = spawn_shader_basic3D(world);
    if (!shader) {
        return 0;
    }
    uint material;
    const entity e = spawn_material(world, shader, &material);
    zox_name("material_basic3D")
    zox_set(e, ShaderLink, { shader })
    const MaterialBasic3D attributes = create_MaterialBasic3D(material);
    zox_set_data(e, MaterialBasic3D, attributes)
    shader_basic3D = shader;
    material_basic3D = e;
    return e;
}
