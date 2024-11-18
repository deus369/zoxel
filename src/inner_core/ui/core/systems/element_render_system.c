// extern ecs_entity_t get_root_canvas_camera(ecs_world_t *world, const ecs_entity_t e);
void ElementRenderSystem(ecs_iter_t *it) {
    if (!material_textured2D) return;
    const GLuint material_link = zox_get_value(material_textured2D, MaterialGPULink)
    const MaterialTextured2D *material_attributes = zox_get(material_textured2D, MaterialTextured2D)
    unsigned char has_set_material = 0;
    const float position_z = ((int) renderer_layer) * shader_depth_multiplier;
    // glUniform1f(attributes.depth, position_z);
    zox_field_in(Position2D, position2Ds, 1)
    zox_field_in(Rotation2D, rotation2Ds, 2)
    zox_field_in(Scale1D, scale1Ds, 3)
    zox_field_in(Layer2D, layer2Ds, 4)
    zox_field_in(RenderDisabled, renderDisableds, 5)
    zox_field_in(Brightness, brightnesses, 6)
    zox_field_in(Alpha, alphas, 7)
    zox_field_in(MeshGPULink, meshGPULinks, 8)
    zox_field_in(UvsGPULink, uvsGPULinks, 9)
    zox_field_in(TextureGPULink, textureGPULinks, 10)
    zox_field_in(MeshDirty, meshDirtys, 11)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Layer2D, layer2Ds, layer2D)
        if (layer2D->value != renderer_layer) continue;
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_e()
        // zox_field_i(MeshDirty, meshDirtys, meshDirty)
        // if (meshDirty->value) continue;
        if (get_root_canvas_camera(world, e) != renderer_camera) continue;
        zox_field_i(Position2D, position2Ds, position2D)
        zox_field_i(Rotation2D, rotation2Ds, rotation2D)
        zox_field_i(Scale1D, scale1Ds, scale1D)
        zox_field_i(Brightness, brightnesses, brightness)
        zox_field_i(Alpha, alphas, alpha)
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i(UvsGPULink, uvsGPULinks, uvsGPULink)
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        if (!meshGPULink->value.x || !meshGPULink->value.y || !uvsGPULink->value || !textureGPULink->value) continue;
        if (!has_set_material) {
            has_set_material = 1;
            opengl_enable_blend();
            opengl_set_material(material_link);
            opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        glBindBuffer(GL_ARRAY_BUFFER, meshGPULink->value.y);
        glEnableVertexAttribArray(material_attributes->vertex_position);
        glVertexAttribPointer(material_attributes->vertex_position, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, uvsGPULink->value);
        glEnableVertexAttribArray(material_attributes->vertex_uv);
        glVertexAttribPointer(material_attributes->vertex_uv, 2, GL_FLOAT, GL_FALSE, 0, 0);
        opengl_bind_texture(textureGPULink->value);
        opengl_set_float3(material_attributes->position, (float3) { position2D->value.x, position2D->value.y, position_z });
        opengl_set_float(material_attributes->angle, rotation2D->value);
        opengl_set_float(material_attributes->scale, scale1D->value);
        opengl_set_float(material_attributes->brightness, brightness->value);
        opengl_set_float(material_attributes->alpha, alpha->value);
#ifndef zox_disable_render_ui
        opengl_render(6);
#endif
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zoxel_log(" > failed to render element2D [%lu]: [%i] - [%ix%i:%i]\n", it->entities[i], 6, meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value);
            break;
        }
#endif
    }
    if (has_set_material) {        
        opengl_disable_buffer(material_attributes->vertex_uv);
        opengl_disable_buffer(material_attributes->vertex_position);
        opengl_disable_blend();
        opengl_unset_mesh();
        opengl_disable_texture(1);
        opengl_disable_opengl_program();
    }
} zox_declare_system(ElementRenderSystem)
