void RenderMaterial2DSystem(ecs_iter_t *it) {
    if (!squareTexturedMesh.x || !squareTexturedMesh.y) {
        if (!squareTexturedMesh.x) {
            zox_log_error("squareTexturedMesh.x 0")
        }
        if (!squareTexturedMesh.y) {
            zox_log_error("squareTexturedMesh.y 0")
        }
        return;
    }
    zox_sys_begin()
    zox_sys_in(Position2D)
    zox_sys_in(Rotation2D)
    zox_sys_in(Scale1D)
    zox_sys_in(Brightness)
    zox_sys_in(MaterialGPULink)
    zox_sys_in(TextureGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Position2D, position2D)
        zox_sys_i(Rotation2D, rotation2D)
        zox_sys_i(Scale1D, scale1D)
        zox_sys_i(Brightness, brightness)
        zox_sys_i(MaterialGPULink, materialGPULink)
        zox_sys_i(TextureGPULink, textureGPULink)
        const uint material = materialGPULink->value;
        if (!material) {
            zox_log_error("invalid material2D")
            continue;
        }

        const MaterialTextured2D attributes = create_MaterialTextured2D(material);
        zox_enable_material(material);
        opengl_enable_blend();
        glBindTexture(GL_TEXTURE_2D, textureGPULink->value);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, squareTexturedMesh.x);    // for indices
        glBindBuffer(GL_ARRAY_BUFFER, squareTexturedMesh.y);            // for vertex buffer data
        glEnableVertexAttribArray(attributes.vertex_position);
        glEnableVertexAttribArray(attributes.vertex_uv);
        glVertexAttribPointer(attributes.vertex_position, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(0 * sizeof(float)));
        glVertexAttribPointer(attributes.vertex_uv, 2, GL_FLOAT, GL_FALSE, 16, (GLvoid*)(2 * sizeof(float)));
        glUniformMatrix4fv(attributes.camera_matrix, 1, GL_FALSE, (const GLfloat*) ((float*) &render_camera_matrix));
        zox_gpu_float3(attributes.position, (float3) { position2D->value.x, position2D->value.y, 0 });
        zox_gpu_float(attributes.angle, rotation2D->value);
        zox_gpu_float(attributes.scale, scale1D->value);
        zox_gpu_float(attributes.brightness, brightness->value);
        zox_gpu_float(attributes.alpha, 1);
        zox_gpu_render(6);
        glBindTexture(GL_TEXTURE_2D, 0);
        opengl_disable_blend();
        zox_disable_material();
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" ! RenderMaterial2DSystem [%lu]\n", it->entities[i])
            break;
        }
#endif
    }
} zox_declare_system(RenderMaterial2DSystem)
