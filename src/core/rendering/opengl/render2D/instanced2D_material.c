GLuint2 shader2D_basic;
GLuint square2DMaterial;
Material2D material2D;
GLuint2 squareMesh;

void dispose_shader2D_instance_material() {
    glDeleteShader(shader2D_basic.x);
    glDeleteShader(shader2D_basic.y);
    glDeleteBuffers(1, &squareMesh.x);
    glDeleteBuffers(1, &squareMesh.y);
    glDeleteProgram(square2DMaterial);
}

void initialize_mesh(GLuint material) {
    glGenBuffers(1, &squareMesh.x);
    glGenBuffers(1, &squareMesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareMesh.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indicies), square_indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, squareMesh.y);
    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(material2D.vertex_position);
    glVertexAttribPointer(material2D.vertex_position, 2, GL_FLOAT, GL_FALSE, 8, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("initialize_mesh");
    #endif
}

int load_instance2D_material() {
    shader2D_basic = spawn_gpu_shader_inline(shader2D_basic_vert_buffer, shader2D_basic_frag_buffer);
    square2DMaterial = spawn_gpu_material_program((const GLuint2) { shader2D_basic.x, shader2D_basic.y });
    initialize_material2D_properties(&material2D, square2DMaterial);
    initialize_mesh(square2DMaterial);
    return 0;
}

void shader2D_instance_begin(const float4x4 viewMatrix) {
    if (square2DMaterial == 0) {
        // printf("shader2D_instance_begin square2DMaterial is 0.\n");
        return;
    }
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(square2DMaterial);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareMesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareMesh.y);            // for vertex coordinates
    glEnableVertexAttribArray(material2D.vertex_position);
    glVertexAttribPointer(material2D.vertex_position, 2, GL_FLOAT, GL_FALSE, 8, 0);  // 2 * 4
    glUniformMatrix4fv(material2D.camera_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
}

// does this per material!
void render_instance2D(float2 position, float angle, float scale, float brightness) {
    // set variables, can this be done using a filtered / system ?
    glUniform1f(material2D.positionX, position.x);
    glUniform1f(material2D.positionY, position.y);
    glUniform1f(material2D.scale, scale);
    glUniform1f(material2D.angle, angle);
    glUniform1f(material2D.brightness, brightness);
    opengl_render(6);
}

void shader2D_instance_end() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    opengl_disable_opengl_program();
}