const unsigned char isDebugRenderMaterial2DSystem = 0;

void render_entity_material2D(const float4x4 viewMatrix, GLuint material, GLuint texture, float2 position, float angle, float scale, float brightness) {
    if (material == 0) return;
    MaterialTextured2D materialTextured2D = initialize_material2D_textured(material);
    glUseProgram(material);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedMesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedMesh.y);            // for vertex buffer data
    glEnableVertexAttribArray(materialTextured2D.vertex_position);
    glEnableVertexAttribArray(materialTextured2D.vertex_uv);
    glVertexAttribPointer(materialTextured2D.vertex_position, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(materialTextured2D.vertex_uv, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
    glUniformMatrix4fv(materialTextured2D.camera_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform3f(materialTextured2D.position, position.x, position.y, 0);
    // glUniform1f(materialTextured2D.positionY, position.y);
    glUniform1f(materialTextured2D.angle, angle);
    glUniform1f(materialTextured2D.scale, scale);
    glUniform1f(materialTextured2D.brightness, brightness);
    opengl_render(6);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glUseProgram(0);
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("render_entity_material2D");
    #endif
}

void RenderMaterial2DSystem(ecs_iter_t *it) {
    Position2D *position2Ds = ecs_field(it, Position2D, 1);
    Rotation2D *rotation2Ds = ecs_field(it, Rotation2D, 2);
    Scale1D *scale2Ds = ecs_field(it, Scale1D, 3);
    Brightness *brightnesses = ecs_field(it, Brightness, 4);
    MaterialGPULink *materialGPULinks = ecs_field(it, MaterialGPULink, 5);
    TextureGPULink *textureGPULinks = ecs_field(it, TextureGPULink, 6);
    for (int i = 0; i < it->count; i++) {
        const Position2D *position = &position2Ds[i];
        const Rotation2D *rotation2D = &rotation2Ds[i];
        const Scale1D *scale1D = &scale2Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const MaterialGPULink *materialGPULink = &materialGPULinks[i];
        const TextureGPULink *textureGPULink = &textureGPULinks[i];
        if (isDebugRenderMaterial2DSystem) {
            if (materialGPULink->value == 0) {
                zoxel_log("RenderMaterial2DSystem Material Error: At [%i]. Entity [%lu].\n", i, (long int) (it->entities[i]));
                continue;
            } else {
                zoxel_log("RenderMaterial2DSystem Material: At [%i]. Entity [%lu].\n", i, (long int) (it->entities[i]));
            }
        }
        float4x4 viewMatrix;
        if (!ecs_has(it->world, it->entities[i], ElementRender)) {
            viewMatrix = render_camera_matrix;
        } else {
            viewMatrix = ui_camera_matrix;
        }
        render_entity_material2D(viewMatrix, materialGPULink->value, textureGPULink->value, position->value, rotation2D->value, scale1D->value, brightness->value);
    }
} zox_declare_system(RenderMaterial2DSystem)