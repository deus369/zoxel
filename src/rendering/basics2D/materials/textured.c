ecs_entity_t shader_textured2D = 0;
ecs_entity_t material_textured2D = 0;

typedef struct {
    GLint vertex_position;
    GLint vertex_uv;
    uint position;
    uint angle;
    uint scale;
    uint camera_matrix;
    uint texture;
    uint brightness;
    uint alpha;
} MaterialTextured2D;
zox_custom_component(MaterialTextured2D)

MaterialTextured2D create_MaterialTextured2D(const uint material) {
    return (MaterialTextured2D) {
        glGetAttribLocation(material, "vertex_position"),
        glGetAttribLocation(material, "vertex_uv"),
        glGetUniformLocation(material, "position"),
        glGetUniformLocation(material, "angle"),
        glGetUniformLocation(material, "scale"),
        glGetUniformLocation(material, "camera_matrix"),
        glGetUniformLocation(material, "texture"),
        glGetUniformLocation(material, "brightness"),
        glGetUniformLocation(material, "alpha") };
}

ecs_entity_t spawn_shader_textured2D(ecs_world_t *world) {
    const byte shader_index = get_new_shader_source_index();
    char* vert = get_shader_source(world, "textured2D.vert");
    char* frag = get_shader_source(world, "textured2D.frag");
    shader_verts[shader_index] = vert;
    shader_frags[shader_index] = frag;
    const ecs_entity_t e = spawn_shader(world, shader_index);
    if (!e) {
        zox_log_error("[textured2D] failed to spawn")
        return 0;
    }
    zox_name("shader_textured2D")
    return e;
}

ecs_entity_t spawn_material_textured2D(ecs_world_t *world) {
    const ecs_entity_t shader = spawn_shader_textured2D(world);
    if (!shader) {
        return 0;
    }
    uint material;
    const ecs_entity_t e = spawn_material(world, shader, &material);
    zox_set(e, ShaderLink, { shader })
    const MaterialTextured2D attributes = create_MaterialTextured2D(material);
    zox_set_data(e, MaterialTextured2D, attributes)
    material_textured2D = e;
    shader_textured2D = shader;
    return e;
}

// todo: refactor this into entity, and just link other ones to it for mesh, MeshLink?
uint2 squareTexturedMesh;
uint squareTexturedModelUVs;

void dispose_square_mesh() {
    glDeleteBuffers(1, &squareTexturedMesh.x);
    glDeleteBuffers(1, &squareTexturedMesh.y);
    glDeleteBuffers(1, &squareTexturedModelUVs);
    // glDeleteTextures(1, &textureID);
    #ifdef zoxel_catch_opengl_errors
    check_opengl_error("dispose_shader2D_textured");
    #endif
}

void initialize_square_mesh_textured() {
    glGenBuffers(1, &squareTexturedMesh.x);
    glGenBuffers(1, &squareTexturedMesh.y);  // generate a new VBO and get the associated ID
    glGenBuffers(1, &squareTexturedModelUVs);  // generate a new VBO and get the associated ID
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedMesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedMesh.y);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indicies), square_indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareTexturedVerts), squareTexturedVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
