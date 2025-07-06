extern ecs_entity_t get_root_canvas_camera(ecs_world_t *world, const ecs_entity_t e);

// this is more like a non blend pass!
void RenderTextureRenderSystem(ecs_iter_t *it) {
    zox_field_world()
    if (!material_render_texture) {
        return;
    }
    const GLuint material_link = zox_get_value(material_render_texture, MaterialGPULink)
    const MaterialAttributesRenderTexture *material_attributes = zox_get(material_render_texture, MaterialAttributesRenderTexture)
    byte has_set_material = 0;
    zox_field_in(TransformMatrix, transformMatrixs, 1)
    zox_field_in(Layer2D, layer2Ds, 2)
    zox_field_in(RenderDisabled, renderDisableds, 3)
    zox_field_in(MeshGPULink, meshGPULinks, 4)
    zox_field_in(UvsGPULink, uvsGPULinks, 5)
    zox_field_in(TextureGPULink, textureGPULinks, 6)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(Layer2D, layer2Ds, layer2D)
        if (layer2D->value != renderer_layer) continue;
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_e()
        if (get_root_canvas_camera(world, e) != renderer_camera) continue;
        zox_field_i(TransformMatrix, transformMatrixs, transformMatrix)
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i(UvsGPULink, uvsGPULinks, uvsGPULink)
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        if (!meshGPULink->value.x || !meshGPULink->value.y) {
            continue;
        }
        if (!uvsGPULink->value) {
            continue;
        }
        if (!textureGPULink->value) {
            zox_log("! render texture - gpu texture link broken\n")
            continue;
        }
        // zox_log("+ rendering - render texture\n")
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(material_link);
            opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
            opengl_disable_blend();
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        glBindBuffer(GL_ARRAY_BUFFER, meshGPULink->value.y);
        glEnableVertexAttribArray(material_attributes->vertex_position);
        glVertexAttribPointer(material_attributes->vertex_position, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glBindBuffer(GL_ARRAY_BUFFER, uvsGPULink->value);
        glEnableVertexAttribArray(material_attributes->vertex_uv);
        glVertexAttribPointer(material_attributes->vertex_uv, 2, GL_FLOAT, GL_FALSE, 0, 0);
        opengl_bind_texture(textureGPULink->value);
        opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);
#ifndef zox_disable_render_ui
        opengl_render(6);
#endif
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" > failed to render render_texture [%lu]: [%i] - [%ix%i:%i]\n", it->entities[i], 6, meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value)
            break;
        }
#endif
    }
    if (has_set_material) {
        opengl_disable_buffer(material_attributes->vertex_uv);
        opengl_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        opengl_disable_texture(1);
        opengl_disable_opengl_program();
    }
} zox_declare_system(RenderTextureRenderSystem)