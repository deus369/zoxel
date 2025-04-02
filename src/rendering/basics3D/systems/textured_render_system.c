void TexturedRenderSystem(ecs_iter_t *it) {
    zox_field_in(TransformMatrix, transformMatrixs, 1)
    zox_field_in(MeshGPULink, meshGPULinks, 2)
    zox_field_in(UvsGPULink, uvsGPULinks, 3)
    zox_field_in(ColorsGPULink, colorsGPULinks, 4)
    zox_field_in(MeshIndicies, meshIndiciess, 5)
    zox_field_in(RenderDisabled, renderDisableds, 6)
    zox_field_in(MaterialGPULink, materialGPULinks, 7)
    zox_field_in(TextureGPULink, textureGPULinks, 8)
    zox_field_in(MaterialTextured3D, materialTextured3Ds, 9)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        if (!meshIndicies->length) continue;
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        if (!meshGPULink->value.x) continue;
        zox_field_i(MaterialGPULink, materialGPULinks, materialGPULink)
        if (!materialGPULink->value) continue;
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        if (!textureGPULink->value) continue;
        zox_field_i(TransformMatrix, transformMatrixs, transformMatrix)
        zox_field_i(UvsGPULink, uvsGPULinks, uvsGPULink)
        zox_field_i(ColorsGPULink, colorsGPULinks, colorsGPULink)
        zox_field_i(MaterialTextured3D, materialTextured3Ds, material_attributes)
        opengl_set_material(materialGPULink->value);
        opengl_bind_texture(textureGPULink->value);
        opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
        opengl_set_float4(material_attributes->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
        opengl_set_float(material_attributes->brightness, 1);
        opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_uv_buffer(material_attributes->vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        opengl_render(meshIndicies->length);
        // disabling
        opengl_disable_buffer(material_attributes->vertex_color);
        opengl_disable_buffer(material_attributes->vertex_uv);
        opengl_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        opengl_disable_texture(0);
        opengl_disable_opengl_program();
        // zox_log(" + rendering cube [%s]\n", zox_get_name(it->entities[i]))
        // zox_log("texture rendering [%i]\n", i)
        catch_basic3D_errors("! TexturedRenderSystem");
    }
} zox_declare_system(TexturedRenderSystem)
