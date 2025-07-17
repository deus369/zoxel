static inline void opengl_bind_texture(uint texture_buffer) {
    glBindTexture(GL_TEXTURE_2D, texture_buffer);
}

static inline void zox_gpu_blend_enable() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static inline void zox_gpu_blend_disable() {
    glDisable(GL_BLEND);
}

static inline void opengl_disable_texture(byte blend) {
    if (blend) {
        glDisable(GL_BLEND);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

static inline void opengl_set_defaults(byte is_3D) {
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

static inline void opengl_clear(const float3 clear_color) {
    if (!headless) {
        glClearColor(clear_color.x, clear_color.y, clear_color.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
}

static inline void opengl_clear_viewport_depth() {
    glClear(GL_DEPTH_BUFFER_BIT);
}

static inline void clear_depth_buffer(uint fbo) {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Bind the default framebuffer
}

static inline uint spawn_gpu_texture_buffer() {
    const int texture_type = GL_NEAREST; // GL_NEAREST | GL_LINEAR
    uint textureID;
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
uint2 spawn_gpu_mesh_buffers() {
    uint2 mesh;
    glGenBuffers(1, &mesh.x);
    glGenBuffers(1, &mesh.y);
#ifdef zoxel_catch_opengl_errors
    check_opengl_error("spawn_gpu_mesh_buffers");
#endif
    return mesh;
}

static inline uint spawn_gpu_generic_buffer() {
    uint buffer;
    glGenBuffers(1, &buffer);
    return buffer;
}

static inline void opengl_bind_mesh(uint2 mesh) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, mesh.y);            // for vertex coordinates
}

static inline void opengl_set_mesh_indicies(uint indices_buffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer);    // for indices
}

static inline void opengl_set_mesh_uvs(uint uv_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);         // for UV coordinates
}

static inline void opengl_unset_mesh() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static inline void opengl_enable_vertex_buffer(uint shader_index, uint vertex_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(shader_index);
    glVertexAttribPointer(shader_index, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static inline void opengl_enable_uv_buffer(uint shader_index, uint uv_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glEnableVertexAttribArray(shader_index);
    glVertexAttribPointer(shader_index, 2, GL_FLOAT, GL_FALSE,  0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static inline void opengl_enable_color_buffer(uint shader_index, uint color_buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glEnableVertexAttribArray(shader_index);
    glVertexAttribPointer(shader_index, 3, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static inline void zox_gpu_disable_buffer(uint shader_index) {
    glDisableVertexAttribArray(shader_index);
}

static inline void zox_gpu_material(uint material) {
    glUseProgram(material);
}

static inline void zox_disable_material() {
    glUseProgram(0);
}

static inline void zox_gpu_render(uint length) {
    glDrawElements(GL_TRIANGLES, length, GL_UNSIGNED_INT, NULL);
}

static inline void zox_gpu_render_lines(uint length) {
    glDrawArrays(GL_LINES, 0, length);
}

static inline void zox_gpu_render_points(uint length) {
    glDrawArrays(GL_POINTS, 0, length);
}

void zox_gpu_buffer_byte(uint shader_index, uint buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glEnableVertexAttribArray(shader_index);
    glVertexAttribPointer(shader_index, 1, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
