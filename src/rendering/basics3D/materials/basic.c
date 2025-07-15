ecs_entity_t shader_basic3D;
ecs_entity_t material_basic3D;

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

ecs_entity_t spawn_shader_basic3D(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "basic3D.vert");
    char* frag = get_shader_source(world, "basic3D.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    zox_name("shader_basic3D")
    return e;
}

ecs_entity_t spawn_material_basic3D(ecs_world_t *world) {
    /*if (load_shader3D_basic(world)) {
        zox_log("    ! error loading [shader3D_basic]\n");
    }*/
    const ecs_entity_t shader = spawn_shader_basic3D(world);
    if (!shader) {
        return 0;
    }
    uint material;
    const ecs_entity_t e = spawn_material(world, shader, &material);
    zox_name("material_basic3D")
    zox_set(e, ShaderLink, { shader })
    const MaterialBasic3D attributes = create_MaterialBasic3D(material);
    zox_set_data(e, MaterialBasic3D, attributes)
    shader_basic3D = shader;
    material_basic3D = e;
    return e;
}
