void TexturedRenderSystem(iter *it) {
    zox_sys_begin()
    zox_sys_in(TransformMatrix)
    zox_sys_in(MeshGPULink)
    zox_sys_in(UvsGPULink)
    zox_sys_in(ColorsGPULink)
    zox_sys_in(MeshIndicies)
    zox_sys_in(RenderDisabled)
    zox_sys_in(MaterialGPULink)
    zox_sys_in(TextureGPULink)
    zox_sys_in(MaterialTextured3D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(MaterialGPULink, materialGPULink)
        zox_sys_i(TextureGPULink, textureGPULink)
        zox_sys_i(TransformMatrix, transformMatrix)
        zox_sys_i(UvsGPULink, uvsGPULink)
        zox_sys_i(ColorsGPULink, colorsGPULink)
        zox_sys_i(MaterialTextured3D, material_attributes)
        if (renderDisabled->value) continue;
        if (!meshIndicies->length) continue;
        if (!meshGPULink->value.x) continue;
        if (!materialGPULink->value) continue;
        if (!textureGPULink->value) continue;
        zox_gpu_material(materialGPULink->value);
        opengl_bind_texture(textureGPULink->value);
        zox_gpu_float4x4(material_attributes->camera_matrix, render_camera_matrix);
        zox_gpu_float4(material_attributes->fog_data, get_fog_value());
        zox_gpu_float(material_attributes->brightness, 1);
        zox_gpu_float4x4(material_attributes->transform_matrix, transformMatrix->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_uv_buffer(material_attributes->vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        zox_gpu_render(meshIndicies->length);
        // disabling
        zox_gpu_disable_buffer(material_attributes->vertex_color);
        zox_gpu_disable_buffer(material_attributes->vertex_uv);
        zox_gpu_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        opengl_disable_texture(0);
        zox_disable_material();
        // zox_log(" + rendering cube [%s]\n", zox_get_name(it->entities[i]))
        // zox_log("texture rendering [%i]\n", i)
        catch_basic3D_errors("! TexturedRenderSystem");
    }
} zoxd_system(TexturedRenderSystem)
