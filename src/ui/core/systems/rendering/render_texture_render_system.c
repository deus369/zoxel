extern ecs_entity_t get_root_canvas_camera(ecs_world_t *world, const ecs_entity_t e);

// this is more like a non blend pass!
void RenderTextureRenderSystem(ecs_iter_t *it) {
    zox_sys_world()
    if (!material_render_texture) {
        return;
    }
    const uint material_link = zox_get_value(material_render_texture, MaterialGPULink)
    const MaterialAttributesRenderTexture *material_attributes = zox_get(material_render_texture, MaterialAttributesRenderTexture)
    byte has_set_material = 0;
    zox_sys_begin()
    zox_sys_in(TransformMatrix)
    zox_sys_in(Layer2D)
    zox_sys_in(RenderDisabled)
    zox_sys_in(MeshGPULink)
    zox_sys_in(UvsGPULink)
    zox_sys_in(TextureGPULink)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(TransformMatrix, transformMatrix)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(UvsGPULink, uvsGPULink)
        zox_sys_i(TextureGPULink, textureGPULink)
        zox_sys_i(Layer2D, layer2D)
        zox_sys_i(RenderDisabled, renderDisabled)
        if (renderDisabled->value || layer2D->value != renderer_layer || !meshGPULink->value.x || !meshGPULink->value.y || !uvsGPULink->value || !textureGPULink->value) {
            continue;
        }
        if (get_root_canvas_camera(world, e) != renderer_camera) {
            continue;
        }
        // zox_log("+ rendering - render texture\n")
        if (!has_set_material) {
            has_set_material = 1;
            zox_gpu_material(material_link);
            zox_gpu_float4x4(material_attributes->camera_matrix, render_camera_matrix);
            zox_gpu_blend_disable();
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        glBindBuffer(GL_ARRAY_BUFFER, meshGPULink->value.y);
        glEnableVertexAttribArray(material_attributes->vertex_position);
        glVertexAttribPointer(material_attributes->vertex_position, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, uvsGPULink->value);
        glEnableVertexAttribArray(material_attributes->vertex_uv);
        glVertexAttribPointer(material_attributes->vertex_uv, 2, GL_FLOAT, GL_FALSE, 0, 0);
        opengl_bind_texture(textureGPULink->value);
        zox_gpu_float4x4(material_attributes->transform_matrix, transformMatrix->value);
#ifndef zox_disable_render_ui
        zox_gpu_render(6);
#endif
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" > failed to render render_texture [%lu]: [%i] - [%ix%i:%i]\n", it->entities[i], 6, meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value)
            break;
        }
#endif
    }
    if (has_set_material) {
        zox_gpu_disable_buffer(material_attributes->vertex_uv);
        zox_gpu_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        opengl_disable_texture(1);
        zox_disable_material();
    }
} zox_declare_system(RenderTextureRenderSystem)