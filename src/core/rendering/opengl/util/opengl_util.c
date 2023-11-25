unsigned char has_gl_extension(const GLubyte *extensions, const char *target) {
    const char *token = strtok((char *)extensions, " ");
    while (token != NULL) {
        if (strcmp(token, target) == 0) return 1; // Extension found
        token = strtok(NULL, " ");
    }
    return 0; // Extension not found
}

unsigned char has_opengl_extensions() {
    unsigned char has_extension = 1;
    const GLubyte *extensions = glGetString(GL_EXTENSIONS);
    /*if (extensions != NULL) printf("        > gl extensions: %s\n", extensions);
    else fprintf(stderr, "Error retrieving extensions\n");*/
    if (!has_gl_extension(extensions, "GL_ARB_shader_objects")) {
        zox_logg("   > no glCreateShader\n")
        has_extension = 0;
    }
    if (!has_extension) exit(0);
    return has_extension;
}

void print_opengl_functions() {
    // Print All Supported Extensions
    GLint numExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
    printf("    > number of Extensions: %d\n", numExtensions);
    /*for (int i = 0; i < numExtensions; ++i) {
        zox_log("%s\n", glGetStringi(GL_EXTENSIONS, i))
    }*/
    const GLubyte *extensions = glGetString(GL_EXTENSIONS);
    if (extensions != NULL) {
        printf("        > gl extensions: %s\n", extensions);
    } else {
        fprintf(stderr, "Error retrieving extensions\n");
    }
    /*if (!has_gl_extension(extensions, "GL_ARB_shader_objects")) {
        zox_logg("   > no glCreateShader\n")
        exit(0);
    }*/
}

void print_opengl() {
#ifdef zox_print_opengl
    zox_logg(" > opengl\n")
    zox_log("     + version   [%s]\n", glGetString(GL_VERSION))
    zox_log("     + glsl      [%s]\n", glGetString(GL_SHADING_LANGUAGE_VERSION))
    zox_log("     + vendor    [%s]\n", glGetString(GL_VENDOR))
    zox_log("     + renderer  [%s]\n", glGetString(GL_RENDERER))
    /*GLint memory_used, memory_total;
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &memory_used);
    glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &memory_total);
    zoxel_log("     + GPU Memory Usage [%d MB / %d MB]\n", memory_used / 1024, memory_total / 1024);
    check_opengl_error("[print_opengl Error]");*/
    print_opengl_functions();
#endif
}

void opengl_bind_texture(GLuint texture_buffer) {
    glBindTexture(GL_TEXTURE_2D, texture_buffer);
}

void opengl_enable_blend() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void opengl_disable_blend() {
    glDisable(GL_BLEND);
}

void opengl_disable_texture(unsigned char isBlend) {
    if (isBlend) glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void opengl_clear() {
    glClearColor(opengl_clear_color.x, opengl_clear_color.y, opengl_clear_color.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       // Clears the buffer ?
    glEnable(GL_DEPTH_TEST);        // cull for 3D things
    glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK); // defaults to this
}

GLuint spawn_gpu_texture_buffers() {
    const int textureType = GL_NEAREST; // GL_LINEAR
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureType);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureType);
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureID;
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

void opengl_disable_opengl_program() {
    glUseProgram(0);
}

void opengl_enable_vertex_buffer(GLuint shader_index, GLuint vertex_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(shader_index);
    glVertexAttribPointer(shader_index, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void opengl_enable_uv_buffer(GLuint shader_index, GLuint uv_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glEnableVertexAttribArray(shader_index);
    glVertexAttribPointer(shader_index, 2, GL_FLOAT, GL_FALSE,  0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void opengl_enable_color_buffer(GLuint shader_index, GLuint color_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glEnableVertexAttribArray(shader_index);
    glVertexAttribPointer(shader_index, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void opengl_disable_buffer(GLuint shader_index) {
    glDisableVertexAttribArray(shader_index);
}

void opengl_set_matrix(GLuint shader_index, const float4x4 value) {
    glUniformMatrix4fv(shader_index, 1, GL_FALSE, (float*) &value);
}

void opengl_set_float4(GLuint shader_index, const float4 value) {
    glUniform4f(shader_index, value.x, value.y, value.z, value.w);
}

void opengl_set_float3(GLuint shader_index, const float3 value) {
    glUniform3f(shader_index, value.x, value.y, value.z);
}

void opengl_set_float(GLuint shader_index, const float value) {
    glUniform1f(shader_index, value);
}

void opengl_set_material(GLuint material) {
    glUseProgram(material);
/*#ifdef zoxel_catch_opengl_errors
    check_opengl_error("opengl_set_material");
#endif*/
}

void opengl_render(GLint indicies_length) {
    glDrawElements(GL_TRIANGLES, indicies_length, GL_UNSIGNED_INT, NULL);
/*#ifdef zoxel_catch_opengl_errors
    check_opengl_error("opengl_render");
#endif*/
}

/*
Multiple textures:

    https://learnopengl.com/Getting-started/textures

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // glActiveTexture(GL_TEXTURE0);
    // glUniform1i(texture, 0);
    // glEnableTexture(texture);
    // glActiveTexture(GL_TEXTURE0);
    // glUniform1i(texture, 0);
    // Error 0x500/1280 means GL_INVALID_ENUM

*/
