/*void initialize_cube_mesh(GLuint material, const int *cube_indicies, const int cube_indicies_length, const float *cube_vertices, const int cube_vertices_length) {
    glGenBuffers(1, &materialInstance3D_mesh.x);
    glGenBuffers(1, &materialInstance3D_mesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, materialInstance3D_mesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, materialInstance3D_mesh.y);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube_indicies_length * sizeof(int), cube_indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, cube_vertices_length * sizeof(float), cube_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(material3D.vertex_position);
    glVertexAttribPointer(material3D.vertex_position, 2, GL_FLOAT, GL_FALSE, 8, 0);
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", materialInstance3D_mesh.x, materialInstance3D_mesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}*/

void opengl_upload_mesh(GLuint2 mesh, GLuint material, const int *indicies, int indicies_length, const float3 *verts, int verts_length) {
    GLint vertex_attribute_position = glGetAttribLocation(material, "vertex_position");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glEnableVertexAttribArray(vertex_attribute_position);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(vertex_attribute_position, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(0 * sizeof(float)));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}