// Print All Supported Extensions
void print_opengl_functions() {
    GLint numExtensions;
    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
    zox_log("+ OpenGL Extensions: %d", numExtensions);
    const GLubyte *extensions = glGetString(GL_EXTENSIONS);
    if (!extensions) {
        zox_log_error("Could not retrieve extensions [%s]", SDL_GetError())
    } else {
        // zox_log(" - gl extensions: %s", extensions);
        /*for (int i = 0; i < numExtensions; ++i) {
            zox_log("%s\n", glGetStringi(GL_EXTENSIONS, i))
        }*/
    }
}

void print_opengl() {
    zox_log(" > OpenGL")
    zox_log("     + version   [%s]", glGetString(GL_VERSION))
    zox_log("     + glsl      [%s]", glGetString(GL_SHADING_LANGUAGE_VERSION))
    zox_log("     + vendor    [%s]", glGetString(GL_VENDOR))
    zox_log("     + renderer  [%s]", glGetString(GL_RENDERER))
    /*GLint memory_used, memory_total;
    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &memory_used);
    glGetIntegerv(GL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX, &memory_total);
    zoxel_log("     + GPU Memory Usage [%d MB / %d MB]\n", memory_used / 1024, memory_total / 1024);
    check_opengl_error("[print_opengl Error]");*/
    print_opengl_functions();
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

void opengl_disable_texture(byte blend) {
    if (blend) {
        glDisable(GL_BLEND);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void opengl_set_defaults(byte is_3D) {
    if (is_3D) {
        glEnable(GL_DEPTH_TEST);        // cull for 3D things
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
        glDisable(GL_BLEND);
    } else {
        glDisable(GL_DEPTH_TEST);        // cull for 3D things
        glDisable(GL_CULL_FACE);
        glEnable(GL_BLEND);
    }
    // glCullFace(GL_BACK); // defaults to this
    // glDisable(GL_BLEND); // Disable blending
}

void opengl_clear(const float3 clear_color) { // const float3 clear_color) {
    if (headless) {
        return;
    }
    // const float3 clear_color = viewport_clear_color;
    glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
    // glClearDepth(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void opengl_clear_viewport_depth() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

void clear_depth_buffer(GLuint fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Bind the default framebuffer
}

GLuint spawn_gpu_texture_buffer() {
    const int texture_type = GL_NEAREST; // GL_NEAREST | GL_LINEAR
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_type);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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

void opengl_set_matrix_array(GLuint shader_index, const float4x4* values, int count) {
    glUniformMatrix4fv(shader_index, count, GL_FALSE, (float*) values);
}

void opengl_set_float3_array(GLuint shader_index, const float3* values, int count) {
    // glUniform3fv(shader_index, count, GL_FALSE, (float*) values);
    // glUniform3fv(shader_index, count, (const GLfloat*)values);
    glUniform3fv(shader_index, count, (const GLfloat*)values);
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
}

void opengl_render(GLint indicies_length) {
    glDrawElements(GL_TRIANGLES, indicies_length, GL_UNSIGNED_INT, NULL);
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
