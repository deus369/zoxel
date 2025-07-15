uint2 shader2D_basic;
uint square2DMaterial;
Material2D material2D;
uint2 squareMesh;

void dispose_shader2D_instance_material() {
    glDeleteShader(shader2D_basic.x);
    glDeleteShader(shader2D_basic.y);
    glDeleteBuffers(1, &squareMesh.x);
    glDeleteBuffers(1, &squareMesh.y);
    glDeleteProgram(square2DMaterial);
}

void initialize_mesh(uint material) {
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

int load_instance2D_material(ecs_world_t *world) {
    char* vert = get_shader_source(world, "basic2D.vert");
    char* frag = get_shader_source(world, "basic2D.frag");
    shader2D_basic = spawn_gpu_shader_inline(vert, frag);
    square2DMaterial = spawn_gpu_material_program((const uint2) { shader2D_basic.x, shader2D_basic.y });
    if (!square2DMaterial) {
        zox_log_error("square2DMaterial failed to initialize")
        return EXIT_FAILURE;
    }
    initialize_material2D_properties(&material2D, square2DMaterial);
    initialize_mesh(square2DMaterial);
    return EXIT_SUCCESS;
}

void shader2D_instance_begin(const float4x4 viewMatrix) {
    if (square2DMaterial == 0) {
        return;
    }
    //! This sets the materials actually, would be best to group entities per material here?
    zox_enable_material(square2DMaterial);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareMesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareMesh.y);            // for vertex coordinates
    glEnableVertexAttribArray(material2D.vertex_position);
    glVertexAttribPointer(material2D.vertex_position, 2, GL_FLOAT, GL_FALSE, 8, 0);  // 2 * 4
    glUniformMatrix4fv(material2D.camera_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
}

// does this per material!
void render_instance2D(float2 position, float angle, float scale, float brightness) {
    // set variables, can this be done using a filtered / system ?
    glUniform3f(material2D.position, position.x, position.y, 0);
    glUniform1f(material2D.scale, scale);
    glUniform1f(material2D.angle, angle);
    glUniform1f(material2D.brightness, brightness);
    zox_gpu_render(6);
}

void shader2D_instance_end() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    zox_disable_material();
}
