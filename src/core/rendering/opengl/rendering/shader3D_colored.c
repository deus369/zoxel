GLuint2 shader3D_colored;
GLuint colored3D_material;
MaterialColored3D attributes_colored3D;

void spawn_material3D_colored_properties(GLuint material) {
    attributes_colored3D = (MaterialColored3D) {
        .vertex_position = glGetAttribLocation(material, "vertex_position"),
        .vertex_color = glGetAttribLocation(material, "vertex_color"),
        .camera_matrix = glGetUniformLocation(material, "camera_matrix"),
        .position = glGetUniformLocation(material, "position"),
        .rotation = glGetUniformLocation(material, "rotation"),
        .scale = glGetUniformLocation(material, "scale"),
        .fog_data = glGetUniformLocation(material, "fog_data"),
        .brightness = glGetUniformLocation(material, "brightness")
    };
    #ifdef zoxel_debug_opengl
        zoxel_log(" > created attributes_colored3D [%i]: vertex_position [%i] vertex_color [%i]\n", material, attributes_colored3D.vertex_position, attributes_colored3D.vertex_color);
        if (attributes_colored3D.vertex_color == -1) {
            zoxel_log(" ! error with vertex_color\n");
            attributes_colored3D.vertex_color = 1;
        }
    #endif
}

void dispose_shader3D_colored() {
    glDeleteShader(shader3D_colored.x);
    glDeleteShader(shader3D_colored.y);
    glDeleteProgram(colored3D_material);
}

int load_shader3D_colored() {
    #ifndef zox_debug_color_shader
        shader3D_colored = spawn_gpu_shader_inline(shader3D_colored_vert_buffer, shader3D_colored_frag_buffer);
    #else
        shader3D_colored = spawn_gpu_shader_inline(debug_shader3D_colored_vert_buffer, debug_shader3D_colored_frag_buffer);
    #endif
    // glBindAttribLocation(shader3D_colored.x, 0, "vertex_position");
    // glBindAttribLocation(shader3D_colored.x, 1, "vertex_color");
    colored3D_material = spawn_gpu_material_program(shader3D_colored);
    spawn_material3D_colored_properties(colored3D_material);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("load_shader3D_colored");
    #endif
    return 0;
}

void opengl_upload_mesh_colors(GLuint2 mesh, GLuint color_buffer, const int *indicies, int indicies_length, const float3 *verts, const color_rgb *color_rgbs, int verts_length) {
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