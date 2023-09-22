typedef struct {
    GLint vertex_position;
    GLuint camera_matrix;
    GLuint position;
    GLuint angle;
    GLuint scale;
    GLuint brightness;
    GLint vertex_uv;
    GLuint texture;
} MaterialTextured2D;

const float shader_depth_multiplier = 0.001f; // 0.0001f;
const unsigned char disableTextureLoaded = 0;
GLuint2 shader2D_textured;
GLuint textured2D_material;
GLuint2 squareTexturedMesh;
GLuint squareTexturedModelUVs;
MaterialTextured2D shader2D_textured_attributes;

MaterialTextured2D initialize_material2D_textured(GLuint material) {
    MaterialTextured2D materialTextured2D;
    materialTextured2D.vertex_position = glGetAttribLocation(material, "vertex_position");
    materialTextured2D.vertex_uv = glGetAttribLocation(material, "vertex_uv");
    materialTextured2D.camera_matrix = glGetUniformLocation(material, "camera_matrix");
    materialTextured2D.position = glGetUniformLocation(material, "position");
    materialTextured2D.angle = glGetUniformLocation(material, "angle");
    materialTextured2D.scale = glGetUniformLocation(material, "scale");
    materialTextured2D.brightness = glGetUniformLocation(material, "brightness");
    materialTextured2D.texture = glGetUniformLocation(material, "tex");
    return materialTextured2D;
}

void dispose_shader2D_textured() {
    glDeleteBuffers(1, &squareTexturedMesh.x);
    glDeleteBuffers(1, &squareTexturedMesh.y);
    glDeleteBuffers(1, &squareTexturedModelUVs);
    // glDeleteTextures(1, &textureID);
    glDeleteShader(shader2D_textured.x);
    glDeleteShader(shader2D_textured.y);
    glDeleteProgram(textured2D_material);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("dispose_shader2D_textured");
    #endif
}

void initialize_shader2D_textured(GLuint material) {
    glGenBuffers(1, &squareTexturedMesh.x);
    glGenBuffers(1, &squareTexturedMesh.y);  // generate a new VBO and get the associated ID
    glGenBuffers(1, &squareTexturedModelUVs);  // generate a new VBO and get the associated ID
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedMesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedMesh.y);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indicies), square_indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareTexturedVerts), squareTexturedVerts, GL_STATIC_DRAW); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("initialize_shader2D_textured");
    #endif
}

int load_shader2D_textured() {
    shader2D_textured = spawn_gpu_shader_inline(shader2D_textured_vert_buffer, shader2D_textured_frag_buffer);
    textured2D_material = spawn_gpu_material_program((const GLuint2) { shader2D_textured.x, shader2D_textured.y });
    shader2D_textured_attributes = initialize_material2D_textured(textured2D_material);
    initialize_shader2D_textured(textured2D_material);
    return 0;
}

void opengl_upload_shader2D_textured(GLuint2 mesh_buffer, GLuint uv_buffer, const int *indicies, int indicies_length, const float2 *verts, const float2 *uvs, int verts_length) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float2), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float2), uvs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    #ifdef zoxel_catch_opengl_errors
        if (check_opengl_error("opengl_upload_shader2D_textured")) {
            zoxel_log("     > [%ix%i:%i]\n", mesh_buffer.x, mesh_buffer.y, uv_buffer);
        }
    #endif
}

void opengl_set_buffer_attributes2D(GLuint vertex_buffer, GLuint uv_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(shader2D_textured_attributes.vertex_position);
    glVertexAttribPointer(shader2D_textured_attributes.vertex_position, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glEnableVertexAttribArray(shader2D_textured_attributes.vertex_uv);
    glVertexAttribPointer(shader2D_textured_attributes.vertex_uv, 2, GL_FLOAT, GL_FALSE, 0, 0);
}