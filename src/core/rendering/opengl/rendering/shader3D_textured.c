GLuint2 shader3D_textured;
GLuint textured3D_material;
Material3DTextured attributes_textured3D;

void spawn_attributes_textured3D(GLuint material) {
    attributes_textured3D = (Material3DTextured) { 
        .vertex_position = glGetAttribLocation(material, "vertex_position"),
        .vertex_uv = glGetAttribLocation(material, "vertex_uv"),
        .vertex_color = glGetAttribLocation(material, "vertex_color"),
        .camera_matrix = glGetUniformLocation(material, "camera_matrix"),
        .position = glGetUniformLocation(material, "position"),
        .rotation = glGetUniformLocation(material, "rotation"),
        .scale = glGetUniformLocation(material, "scale"),
        .fog_data = glGetUniformLocation(material, "fog_data"),
        .texture = glGetUniformLocation(material, "tex"),
        .brightness = glGetUniformLocation(material, "brightness")
    };
    #ifdef zoxel_debug_opengl
        zoxel_log(" > created attributes_textured3D [%i]: vertex_position [%i] vertex_uv [%i] vertex_color [%i]\n", material, attributes_textured3D.vertex_position, attributes_textured3D.vertex_uv, attributes_textured3D.vertex_color);
    #endif
}

void dispose_shader3D_textured() {
    glDeleteShader(shader3D_textured.x);
    glDeleteShader(shader3D_textured.y);
    glDeleteProgram(textured3D_material);
}

int load_shader3D_textured() {
    shader3D_textured = spawn_gpu_shader_inline(shader3D_textured_vert_buffer, shader3D_textured_frag_buffer);
    textured3D_material = spawn_gpu_material_program(shader3D_textured);
    spawn_attributes_textured3D(textured3D_material);
    #ifdef zoxel_debug_opengl
        zoxel_log(" > loaded shader3D textured\n");
    #endif
    return 0;
}

void opengl_bind_texture(GLuint texture_buffer) {
    glBindTexture(GL_TEXTURE_2D, texture_buffer);
}

void opengl_set_texture(GLuint texture_buffer, unsigned char isBlend) {
    if (isBlend) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    } else {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_BLEND);
    }
    glBindTexture(GL_TEXTURE_2D, texture_buffer);
}

void opengl_set_material3D_uvs_properties(float4 rotation, float scale, float brightness, Material3DTextured *attributes) {
    // glUniform3f(materialTextured3D->position, position.x, position.y, position.z);
    glUniform4f(attributes->rotation, rotation.x, rotation.y, rotation.z, rotation.w);
    glUniform1f(attributes->scale, scale);
    glUniform1f(attributes->brightness, brightness);
}

void opengl_set_material3D_uvs_position(float3 position, Material3DTextured *attributes) {
    glUniform3f(attributes->position, position.x, position.y, position.z);
}

void opengl_upload_shader3D_textured(GLuint2 mesh_buffer, GLuint uv_buffer, GLuint color_buffer, const int *indicies, int indicies_length, const float3 *verts, int verts_length, const float2 *uvs, const color_rgb *color_rgbs) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float2), uvs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(color_rgb), color_rgbs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_upload_shader3D_textured");
    #endif
}