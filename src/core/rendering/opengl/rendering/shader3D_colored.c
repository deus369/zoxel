uint2 shader3D_colored;
uint colored3D_material;
MaterialColored3D attributes_colored3D;

void spawn_material3D_colored_properties(uint material) {
    attributes_colored3D = (MaterialColored3D) {
        .view_matrix = glGetUniformLocation(material, "camera_matrix"),
        .position = glGetUniformLocation(material, "position"),
        .rotation = glGetUniformLocation(material, "rotation"),
        .scale = glGetUniformLocation(material, "scale"),
        .brightness = glGetUniformLocation(material, "brightness"),
        .vertex_position = glGetAttribLocation(material, "vertex_position"),
        .vertex_color = glGetAttribLocation(material, "vertex_color"),
        .fog_data = glGetAttribLocation(material, "fog_data")
    };
}

void dispose_shader3D_colored() {
    glDeleteShader(shader3D_colored.x);
    glDeleteShader(shader3D_colored.y);
    glDeleteProgram(colored3D_material);
}

int load_shader3D_colored() {
    shader3D_colored = spawn_gpu_shader_inline(shader3D_colored_vert_buffer, shader3D_colored_frag_buffer);
    colored3D_material = spawn_gpu_material_program(shader3D_colored);
    spawn_material3D_colored_properties(colored3D_material);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("load_shader3D_colored");
    #endif
    return 0;
}

void opengl_upload_mesh_colors(uint2 mesh, uint color_buffer, const int *indicies, int indicies_length, const float3 *verts, const color_rgb *color_rgbs, int verts_length) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(color_rgb), color_rgbs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_upload_mesh_colors");
    #endif
}

void opengl_set_colored3D_buffers(uint vertex_buffer, uint color_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(attributes_colored3D.vertex_position);
    glVertexAttribPointer(attributes_colored3D.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glEnableVertexAttribArray(attributes_colored3D.vertex_color);
    glVertexAttribPointer(attributes_colored3D.vertex_color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void render_character3D(int mesh_indicies_length, uint2 mesh, uint color_buffer, float3 position, float4 rotation) {
    opengl_set_mesh_indicies(mesh.x);
    opengl_set_colored3D_buffers(mesh.y, color_buffer);
    glUniform3f(attributes_colored3D.position, position.x, position.y, position.z);
    glUniform4f(attributes_colored3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    #ifndef zox_disable_render_characters
        opengl_draw_triangles(mesh_indicies_length);
    #endif
}