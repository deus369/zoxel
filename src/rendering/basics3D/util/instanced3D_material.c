GLuint2 shader3D;
GLuint materialInstance3D;
Material3D material3D;
GLuint2 materialInstance3D_mesh;

void dispose_shader3D_instance_material() {
    glDeleteShader(shader3D.x);
    glDeleteShader(shader3D.y);
    glDeleteBuffers(1, &materialInstance3D_mesh.x);
    glDeleteBuffers(1, &materialInstance3D_mesh.y);
    glDeleteProgram(materialInstance3D);
}

void initialize_cube_mesh(GLuint material) {
    glGenBuffers(1, &materialInstance3D_mesh.x);
    glGenBuffers(1, &materialInstance3D_mesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, materialInstance3D_mesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, materialInstance3D_mesh.y);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndicies3), cubeIndicies3, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices3), cubeVertices3, GL_STATIC_DRAW);
    glEnableVertexAttribArray(material3D.vertex_position);
    glVertexAttribPointer(material3D.vertex_position, 2, GL_FLOAT, GL_FALSE, 8, 0);
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", materialInstance3D_mesh.x, materialInstance3D_mesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int load_shader3D_basic() {
    shader3D = spawn_gpu_shader_inline(shader3D_vert_buffer, shader3D_frag_buffer);
    materialInstance3D = spawn_gpu_material_program((const GLuint2) { shader3D.x, shader3D.y });
    material3D = spawn_material3D_properties(materialInstance3D);
    initialize_cube_mesh(materialInstance3D);
    return 0;
}

void opengl_instance3D_begin(const float4x4 viewMatrix) {
    //! This sets the materials actually, would be best to group entities per material here?
    glUseProgram(materialInstance3D);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, materialInstance3D_mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, materialInstance3D_mesh.y);            // for vertex coordinates
    glEnableVertexAttribArray(material3D.vertex_position);
    glVertexAttribPointer(material3D.vertex_position, 2, GL_FLOAT, GL_FALSE, 8, 0);
    glUniformMatrix4fv(material3D.camera_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
}

//! Set variables, can this be done using a filtered / system ?
void render_entity_3D(float3 position, float4 rotation, float scale1D, float brightness) {
    glUniform3f(material3D.position, position.x, position.y, position.z);
    glUniform4f(material3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(material3D.scale, scale1D);
    glUniform1f(material3D.brightness, brightness);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    opengl_render(6);
}

void opengl_upload_mesh(GLuint2 mesh, GLuint material, const int *indicies, int indicies_length, const float3 *verts, int verts_length) {
    Material3D material3D = spawn_material3D_properties(material);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glEnableVertexAttribArray(material3D.vertex_position);
    // glVertexAttribPointer(material3D.vertex_position, 3, GL_FLOAT, GL_FALSE, 4 * 3, 0);
    // printf("Binding Data %i %i\n", indicies_length, verts_length);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * 4, indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float), verts, GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, floats_length * 4, combined_verts, GL_STATIC_DRAW);
    glVertexAttribPointer(material3D.vertex_position, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
    // glVertexAttribPointer(material3D.vertex_uv, 2, GL_FLOAT, GL_FALSE, 4 * 5, (GLvoid*)(3 * sizeof(float)));
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", mesh.x, mesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#ifdef zoxel_catch_opengl_errors
    check_opengl_error("opengl_upload_mesh");
#endif
}
