void ElementRenderSystem(ecs_iter_t *it) {
    zox_sys_world()
    if (!zox_valid(material_textured2D)) {
        return;
    }
    byte is_rendering = 0;
    const float position_z = ((int) renderer_layer) * shader_depth_multiplier;
    zox_geter_value(material_textured2D, MaterialGPULink, uint, material_link)
    zox_geter(material_textured2D, MaterialTextured2D, material_attributes)
    zox_sys_begin()
    zox_sys_in(Position2D)
    zox_sys_in(Rotation2D)
    zox_sys_in(Scale1D)
    zox_sys_in(Layer2D)
    zox_sys_in(RenderDisabled)
    zox_sys_in(Brightness)
    zox_sys_in(Alpha)
    zox_sys_in(MeshGPULink)
    zox_sys_in(UvsGPULink)
    zox_sys_in(TextureGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(Position2D, position2D)
        zox_sys_i(Rotation2D, rotation2D)
        zox_sys_i(Scale1D, scale1D)
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(Layer2D, layer2D)
        zox_sys_i(Brightness, brightness)
        zox_sys_i(Alpha, alpha)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(UvsGPULink, uvsGPULink)
        zox_sys_i(TextureGPULink, textureGPULink)
        if (layer2D->value != renderer_layer || renderDisabled->value || get_root_canvas_camera(world, e) != renderer_camera || !meshGPULink->value.x || !meshGPULink->value.y || !uvsGPULink->value || !textureGPULink->value) {
            continue;
        }
        if (!is_rendering) {
            is_rendering = 1;
            // per material data
            zox_gpu_blend_enable();
            zox_gpu_material(material_link);
            zox_gpu_float4x4(material_attributes->camera_matrix, render_camera_matrix);
        }
        // per mesh data
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_bind_texture(textureGPULink->value);
        glBindBuffer(GL_ARRAY_BUFFER, meshGPULink->value.y);
        glEnableVertexAttribArray(material_attributes->vertex_position);
        glVertexAttribPointer(material_attributes->vertex_position, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, uvsGPULink->value);
        glEnableVertexAttribArray(material_attributes->vertex_uv);
        glVertexAttribPointer(material_attributes->vertex_uv, 2, GL_FLOAT, GL_FALSE, 0, 0);
        zox_gpu_float3(material_attributes->position, (float3) { position2D->value.x, position2D->value.y, position_z });
        zox_gpu_float(material_attributes->angle, rotation2D->value);
        zox_gpu_float(material_attributes->scale, scale1D->value);
        zox_gpu_float(material_attributes->brightness, brightness->value);
        zox_gpu_float(material_attributes->alpha, alpha->value);
        zox_gpu_render(6);
    }
    if (is_rendering) {
        // cleanup material data
        zox_gpu_disable_buffer(material_attributes->vertex_uv);
        zox_gpu_disable_buffer(material_attributes->vertex_position);
        zox_gpu_blend_disable();
        opengl_unset_mesh();
        opengl_disable_texture(1);
        zox_disable_material();
    }
} zox_declare_system(ElementRenderSystem)