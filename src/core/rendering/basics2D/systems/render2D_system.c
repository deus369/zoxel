void render_entity_material2D(const float4x4 viewMatrix, GLuint material, GLuint texture, float2 position, float angle, float scale, float brightness) {
    if (!material) {
        zox_log(" ! invalid material 2D\n")
        return;
    }
    // zox_log("rendering 2D at %fx%f scale %f\n", position.x, position.y, scale)
    const MaterialTextured2D attributes = create_MaterialTextured2D(material);
    glUseProgram(material);
    opengl_enable_blend();
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedMesh.x);    // for indices
    glBindBuffer(GL_ARRAY_BUFFER, squareTexturedMesh.y);            // for vertex buffer data
    glEnableVertexAttribArray(attributes.vertex_position);
    glEnableVertexAttribArray(attributes.vertex_uv);
    glVertexAttribPointer(attributes.vertex_position, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
    glVertexAttribPointer(attributes.vertex_uv, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
    glUniformMatrix4fv(attributes.camera_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &viewMatrix));
    glUniform3f(attributes.position, position.x, position.y, 0);
    glUniform1f(attributes.angle, angle);
    glUniform1f(attributes.scale, scale);
    glUniform1f(attributes.brightness, brightness);
    glUniform1f(attributes.alpha, 1);
    opengl_render(6);
    glBindTexture(GL_TEXTURE_2D, 0);
    // glDisable(GL_BLEND);
    opengl_disable_blend();
    glUseProgram(0);
#ifdef zoxel_catch_opengl_errors
    check_opengl_error("render_entity_material2D");
#endif
}

void RenderMaterial2DSystem(ecs_iter_t *it) {
    // zox_log("rendering 2D: %i\n", it->count)
    zox_field_in(Position2D, position2Ds, 1)
    zox_field_in(Rotation2D, rotation2Ds, 2)
    zox_field_in(Scale1D, scale1Ds, 3)
    zox_field_in(Brightness, brightnesss, 4)
    zox_field_in(MaterialGPULink, materialGPULinks, 5)
    zox_field_in(TextureGPULink, textureGPULinks, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Position2D, position2Ds, position2D)
        zox_field_i(Rotation2D, rotation2Ds, rotation2D)
        zox_field_i(Scale1D, scale1Ds, scale1D)
        zox_field_i(Brightness, brightnesss, brightness)
        zox_field_i(MaterialGPULink, materialGPULinks, materialGPULink)
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        render_entity_material2D(render_camera_matrix, materialGPULink->value, textureGPULink->value, position2D->value, rotation2D->value, scale1D->value, brightness->value);
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" ! RenderMaterial2DSystem [%lu]\n", it->entities[i])
            break;
        }
#endif
    }
} zox_declare_system(RenderMaterial2DSystem)
