
extern GLuint2 get_shader_value(ecs_world_t *world, ecs_entity_t shader);
extern ecs_entity_t spawn_shader(ecs_world_t *world, const GLchar* vert_buffer, const GLchar* frag_buffer);
extern ecs_entity_t spawn_material(ecs_world_t *world, GLuint2 shader);
extern GLuint get_material_value(ecs_world_t *world, ecs_entity_t material);
extern void restore_shader(ecs_world_t *world, ecs_entity_t e, const GLchar* vert_buffer, const GLchar* frag_buffer);
extern void restore_material(ecs_world_t *world, ecs_entity_t e, GLuint2 shader);
ecs_entity_t textured3D_shader;
ecs_entity_t textured3D_material;

GLuint2 get_shader3D_textured_value(ecs_world_t *world) {
    return get_shader_value(world, textured3D_shader);
}

GLuint get_textured3D_material_value(ecs_world_t *world) {
    return get_material_value(world, textured3D_material);
}

const Textured3DAttributes* get_textured3D_material_attributes(ecs_world_t *world) {
    return ecs_get(world, textured3D_material, Textured3DAttributes);
}

void restore_shader_textured3D(ecs_world_t *world) {
    // todo: link shader code to the shader gpu link, use system for restoring them
    restore_shader(world, textured3D_shader, shader3D_textured_vert_buffer, shader3D_textured_frag_buffer);
    // todo: link shader link to the material gpu link, use system for restoring them
    restore_material(world, textured3D_material, get_shader3D_textured_value(world));
}

int load_shader3D_textured(ecs_world_t *world) {
    if (textured3D_shader == 0) {
        textured3D_shader = spawn_shader(world, shader3D_textured_vert_buffer, shader3D_textured_frag_buffer);
        textured3D_material = spawn_material(world, get_shader3D_textured_value(world));
        GLuint material = get_textured3D_material_value(world);
        zox_prefab_set(textured3D_material, Textured3DAttributes, { 
            .vertex_position = glGetAttribLocation(material, "vertex_position"),
            .vertex_uv = glGetAttribLocation(material, "vertex_uv"),
            .vertex_color = glGetAttribLocation(material, "vertex_color"),
            .position = glGetUniformLocation(material, "position"),
            .rotation = glGetUniformLocation(material, "rotation"),
            .scale = glGetUniformLocation(material, "scale"),
            .camera_matrix = glGetUniformLocation(material, "camera_matrix"),
            .fog_data = glGetUniformLocation(material, "fog_data"),
            .texture = glGetUniformLocation(material, "tex"),
            .brightness = glGetUniformLocation(material, "brightness") })
        /*
            const Textured3DAttributes *attributes_textured3D = get_textured3D_material_attributes(world);
            zoxel_log(" attributes_textured3D indexes:\n");
            zoxel_log("         1 [%ix%ix%i]\n", attributes_textured3D->vertex_position, attributes_textured3D->vertex_uv, attributes_textured3D->vertex_color);
            zoxel_log("         2 [%ix%ix%i]\n", attributes_textured3D->position, attributes_textured3D->rotation, attributes_textured3D->scale);
            zoxel_log("         3 [%ix%ix%i]\n", attributes_textured3D->camera_matrix, attributes_textured3D->fog_data, attributes_textured3D->texture, attributes_textured3D->brightness);
        */
    }
    #ifdef zoxel_debug_opengl
        zoxel_log(" > loaded shader3D textured\n");
    #endif
    return 0;
}

void opengl_upload_shader3D_textured(GLuint2 mesh_buffer, GLuint uv_buffer, GLuint color_buffer, const int *indicies, int indicies_length, const float3 *verts, int verts_length, const float2 *uvs, const color_rgb *color_rgbs) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_buffer.x);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_length * sizeof(int), indicies, GL_STATIC_DRAW);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_upload_shader3D_textured GL_ELEMENT_ARRAY_BUFFER");
    #endif
    glBindBuffer(GL_ARRAY_BUFFER, mesh_buffer.y);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float3), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);   
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(float2), uvs, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, verts_length * sizeof(color_rgb), color_rgbs, GL_STATIC_DRAW);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_upload_shader3D_textured");
    #endif
}