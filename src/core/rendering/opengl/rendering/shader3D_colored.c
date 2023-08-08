uint2 shader3D_colored;
uint colored3D_material;
MaterialColored3D materialColored3D;

MaterialColored3D spawn_material3D_colored_properties(uint material) {
    MaterialColored3D materialColored3D;
    materialColored3D.view_matrix = glGetUniformLocation(material, "camera_matrix");
    materialColored3D.position = glGetUniformLocation(material, "position");
    materialColored3D.rotation = glGetUniformLocation(material, "rotation");
    materialColored3D.scale = glGetUniformLocation(material, "scale");
    materialColored3D.brightness = glGetUniformLocation(material, "brightness");
    materialColored3D.vertex_position = glGetAttribLocation(material, "vertex_position");
    materialColored3D.vertex_color = glGetAttribLocation(material, "vertex_color");
    materialColored3D.fog_data = glGetAttribLocation(material, "fog_data");
    return materialColored3D;
}

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

void opengl_upload_mesh_colors(uint2 mesh, uint color_buffer, const int *indicies, int indicies_length, const float3 *verts, int verts_length, const color_rgb *color_rgbs) {
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

void render_colored3D(uint2 mesh, uint color_buffer, uint mesh_indicies_length, float3 position, float4 rotation) {
    // if (check_opengl_error("[render_colored3D Error]")) return;
    opengl_set_mesh_indicies(mesh.x);
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);
    glEnableVertexAttribArray(materialColored3D.vertex_position);
    glVertexAttribPointer(materialColored3D.vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glEnableVertexAttribArray(materialColored3D.vertex_color);
    glVertexAttribPointer(materialColored3D.vertex_color, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glUniform3f(materialColored3D.position, position.x, position.y, position.z);
    glUniform4f(materialColored3D.rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    #ifndef zox_disable_render3D_colored
        // zoxel_log(" > mesh_indicies_length: %i\n", mesh_indicies_length);
        opengl_draw_triangles(mesh_indicies_length);
    #endif
}