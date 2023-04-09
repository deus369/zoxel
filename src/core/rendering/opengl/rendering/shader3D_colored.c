GLuint2 shader3D_colored;
GLuint colored3D_material;
MaterialColored3D materialColored3D;

void dispose_shader3D_colored() {
    glDeleteShader(shader3D_colored.x);
    glDeleteShader(shader3D_colored.y);
    glDeleteProgram(colored3D_material);
}

int load_shader3D_colored() {
    shader3D_colored = spawn_gpu_shader_inline(shader3D_colored_vert_buffer, shader3D_colored_frag_buffer);
    colored3D_material = spawn_gpu_material_program(shader3D_colored);
    materialColored3D = spawn_material3D_colored_properties(colored3D_material);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("load_shader3D_colored");
    #endif
    return 0;
}

void set_gpu_mesh_colors(GLuint2 mesh, GLuint color_buffer, const int *indicies, int indicies_length,
    const float3 *verts, int verts_length, const color *colors) {
    // Bind the index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    // Bind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);
    // Bind the UV buffer
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(color), colors, GL_STATIC_DRAW);
    // Unbind the buffers
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void opengl_set_buffer_attributes_colors(GLuint vertex_buffer, GLuint color_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(materialColored3D.vertexPosition);
    glVertexAttribPointer(materialColored3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, 0); // sizeof(float3), 0);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glEnableVertexAttribArray(materialColored3D.vertexColor);
    glVertexAttribPointer(materialColored3D.vertexColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0); // 4 * sizeof(GLubyte), 0);
}

int opengl_set_material3D_colors_properties(float3 position, float4 rotation) {
    glUniform3f(materialColored3D.position, position.x, position.y, position.z);
    glUniform4f(materialColored3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_set_material3D_colors_properties");
    #endif
    return 0;
}

// todo: remove this combined from here
/*void set_gpu_mesh_colors(GLuint2 mesh, GLuint material, const int *indicies, int indicies_length,
    const float3 *verts, int verts_length, const color *colors) {
    tri_count += indicies_length / 3;
    // zoxel_log("set_gpu_mesh_colors - adding tris\n");
    int float_per_data = 7;
    int floats_length = verts_length * float_per_data;
    float combined_verts[floats_length];
    for (int i = 0; i < verts_length; i++) {
        float3 vert = verts[i];
        color vert_color = colors[i];
        float4 vert_color_float4 = color_to_float4(vert_color);
        combined_verts[i * float_per_data + 0] = vert.x;
        combined_verts[i * float_per_data + 1] = vert.y;
        combined_verts[i * float_per_data + 2] = vert.z;
        combined_verts[i * float_per_data + 3] = vert_color_float4.x;
        combined_verts[i * float_per_data + 4] = vert_color_float4.y;
        combined_verts[i * float_per_data + 5] = vert_color_float4.z;
        combined_verts[i * float_per_data + 6] = vert_color_float4.w;
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glEnableVertexAttribArray(materialColored3D.vertexPosition);
    glEnableVertexAttribArray(materialColored3D.vertexColor);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * 4, indicies, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, floats_length * 4, combined_verts, GL_STATIC_DRAW);
    glVertexAttribPointer(materialColored3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 4 * float_per_data, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(materialColored3D.vertexColor, 4, GL_FLOAT, GL_FALSE, 4 * float_per_data, (GLvoid*)(3 * sizeof(float)));
    // printf("Setting Vertex Attribute Pointer for [%ix%i] Mesh.\n", mesh.x, mesh.y);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}*/

//, float scale, float brightness) {
// MaterialColored3D materialColored3D = spawn_material3D_colored_properties(material);
/*glEnableVertexAttribArray(materialColored3D.vertexPosition);
glEnableVertexAttribArray(materialColored3D.vertexColor);
glVertexAttribPointer(materialColored3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 4 * 7, 0);
glVertexAttribPointer(materialColored3D.vertexColor, 4, GL_FLOAT, GL_FALSE, 4 * 7, (GLvoid*)(3 * sizeof(float)));*/
// glUniform1f(materialColored3D.scale, scale);
// glUniform1f(materialColored3D.brightness, brightness);
    // vertex array
    /*glVertexAttribPointer(materialColored3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(materialColored3D.vertexPosition);
    // color arrays
    glVertexAttribPointer(materialColored3D.vertexColor, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, (GLvoid*)(sizeof(float3) * verts_length));
    glEnableVertexAttribArray(materialColored3D.vertexColor);*/

/*void set_color_vertex_layout() {
    int total_size = 3 * sizeof(float) + 4 * sizeof(GLubyte);
    glEnableVertexAttribArray(materialColored3D.vertexPosition);
    glEnableVertexAttribArray(materialColored3D.vertexColor);
    glVertexAttribPointer(materialColored3D.vertexPosition, 3, GL_FLOAT, GL_FALSE, total_size, 0);
    // glVertexAttribPointer(materialColored3D.vertexColor, 4, GL_FLOAT, GL_FALSE, 4 * 7, (GLvoid*)(3 * sizeof(float)));
    glVertexAttribPointer(materialColored3D.vertexColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, total_size, (GLvoid*)(3 * sizeof(float)));
}*/