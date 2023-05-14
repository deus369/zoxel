void print_opengl() {
    #ifdef zoxel_debug_opengl
        zoxel_log(" > opengl\n");
        zoxel_log("     + version:  %s\n", glGetString(GL_VERSION));
        zoxel_log("     + glsl version:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
        zoxel_log("     + vendor:   %s\n", glGetString(GL_VENDOR));
        zoxel_log("     + renderer: %s\n", glGetString(GL_RENDERER));
        GLint memory_used, memory_total;
        glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &memory_used);
        glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &memory_total);
        zoxel_log("     + GPU Memory Usage [%d MB / %d MB]\n", memory_used / 1024, memory_total / 1024);
    #endif
}

void opengl_clear() {
    glClearColor(opengl_clear_color.x, opengl_clear_color.y, opengl_clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       // Clears the buffer ?
    glEnable(GL_DEPTH_TEST);        // cull for 3D things
    glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK); // defaults to this
}

//! Spawns the buffers for a mesh indicies and verts on the gpu.
GLuint2 spawn_gpu_mesh_buffers() {
    GLuint2 mesh;
    glGenBuffers(1, &mesh.x);
    glGenBuffers(1, &mesh.y);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("spawn_gpu_mesh_buffers");
    #endif
    return mesh;
}

GLuint spawn_gpu_generic_buffer() {
    GLuint buffer;
    glGenBuffers(1, &buffer);
    return buffer;
}

unsigned char opengl_set_material(GLuint material) {
    if (material == 0) {
        // printf("render_entity_material2D material is 0.\n");
        return 0;
    }
    glUseProgram(material);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_set_material");
    #endif
    return 1;
}

void opengl_bind_mesh(GLuint2 mesh) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);            // for vertex coordinates
}

void opengl_set_mesh_indicies(GLuint indices_buffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);    // for indices
}

void opengl_set_mesh_uvs(GLuint uv_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);         // for UV coordinates
}

void opengl_unset_mesh() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void opengl_draw_triangles(int indicies_length) {
    glDrawElements(GL_TRIANGLES, indicies_length, GL_UNSIGNED_INT, NULL);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_draw_triangles");
    #endif
}

void opengl_disable_opengl_program() {
    glUseProgram(0);
}

void opengl_set_camera_view_matrix(GLuint material, const float4x4 view_matrix) {
    GLuint view_matrix_location = glGetUniformLocation(material, "camera_matrix");
    // glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, (const GLfloat*) ((float*) &view_matrix));
    glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, (float*) &view_matrix);
}

/*
Multiple textures:

    https://learnopengl.com/Getting-started/textures

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

*/

// glActiveTexture(GL_TEXTURE0);
// glUniform1i(texture, 0);
// glEnableTexture(texture);
// glActiveTexture(GL_TEXTURE0);
// glUniform1i(texture, 0);
// Error 0x500/1280 means GL_INVALID_ENUM