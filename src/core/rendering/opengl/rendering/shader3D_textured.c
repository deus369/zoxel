extern GLuint2 get_shader_value(ecs_world_t *world, ecs_entity_t shader);
extern ecs_entity_t spawn_shader(ecs_world_t *world, const GLchar* vert_buffer, const GLchar* frag_buffer);
extern ecs_entity_t spawn_material(ecs_world_t *world, GLuint2 shader);
extern GLuint get_material_value(ecs_world_t *world, ecs_entity_t material);
extern void restore_shader(ecs_world_t *world, ecs_entity_t e, const GLchar* vert_buffer, const GLchar* frag_buffer);
extern void restore_material(ecs_world_t *world, ecs_entity_t e, GLuint2 shader);
ecs_entity_t shader3D_textured;
ecs_entity_t textured3D_material;
// GLuint2 shader3D_textured2;
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

GLuint2 get_shader3D_textured_value(ecs_world_t *world) {
    return get_shader_value(world, shader3D_textured);
    // return ecs_get(world, shader3D_textured, ShaderGPULink)->value;
}

GLuint get_textured3D_material_value(ecs_world_t *world) {
    return get_material_value(world, textured3D_material);
}

void dispose_shader3D_textured(ecs_world_t *world) {
    // shaders will be deleted on ecs closing
    // zox_delete(shader3D_textured)
    // zox_delete(textured3D_material)
}

void restore_textured3D_shader(ecs_world_t *world) {
    restore_shader(world, shader3D_textured, shader3D_textured_vert_buffer, shader3D_textured_frag_buffer);
    restore_material(world, textured3D_material, get_shader3D_textured_value(world));
}

int load_shader3D_textured(ecs_world_t *world) {
    if (shader3D_textured == 0) {
        shader3D_textured = spawn_shader(world, shader3D_textured_vert_buffer, shader3D_textured_frag_buffer);
        textured3D_material = spawn_material(world, get_shader3D_textured_value(world));
        spawn_attributes_textured3D(textured3D_material);
    }
    #ifdef zoxel_debug_opengl
        zoxel_log(" > loaded shader3D textured\n");
    #endif
    return 0;
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

/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indicies), cube_indicies, GL_STATIC_DRAW);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(cube_uvs), cube_uvs, GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, 0);*/
// zoxel_log(" > sizes: %ix%ix%i\n", sizeof(cube_vertices), sizeof(cube_uvs), sizeof(cube_colors));

/*void opengl_set_texture(GLuint texture_buffer, unsigned char isBlend) {
    if (isBlend) {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
    } else {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_BLEND);
    }
    glBindTexture(GL_TEXTURE_2D, texture_buffer);
}*/
    // glDeleteShader(shader3D_textured.x);
    // glDeleteShader(shader3D_textured.y);
    // glDeleteProgram(textured3D_material);