extern byte can_render_ui(ecs *world, entity e);
// #define zox_time_render3D_textured_system

void Element3DRenderSystem(iter *it) {
    if (!material_textured3D) {
        return;
    }
    zox_sys_world()
    byte has_set_material = 0;
    const uint material_link = zox_get_value(material_textured3D, MaterialGPULink)
    const MaterialTextured3D *material_attributes = zox_get(material_textured3D, MaterialTextured3D)
    zox_sys_begin()
    zox_sys_in(TransformMatrix)
    zox_sys_in(MeshGPULink)
    zox_sys_in(UvsGPULink)
    zox_sys_in(ColorsGPULink)
    zox_sys_in(MeshIndicies)
    zox_sys_in(TextureGPULink)
    zox_sys_in(RenderDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(TransformMatrix, transformMatrix)
        zox_sys_i(UvsGPULink, uvsGPULink)
        zox_sys_i(ColorsGPULink, colorsGPULink)
        zox_sys_i(TextureGPULink, textureGPULink)
        if (renderDisabled->value) {
            continue;
        }
        if (!can_render_ui(world, e)) {
            continue;
        }
        if (!meshIndicies->length) {
            continue;
        }
        if (!meshGPULink->value.x || !meshGPULink->value.y) {
            continue;
        }
        if (!has_set_material) {
            has_set_material = 1;
            zox_gpu_blend_enable();
            zox_gpu_material(material_link);
            zox_gpu_float4x4(material_attributes->camera_matrix, render_camera_matrix);
            zox_gpu_float4(material_attributes->fog_data, get_fog_value());
            zox_gpu_float(material_attributes->brightness, 1);
        }
        zox_gpu_float4x4(material_attributes->transform_matrix, transformMatrix->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_uv_buffer(material_attributes->vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        opengl_bind_texture(textureGPULink->value);
        zox_gpu_render(meshIndicies->length);
        zox_log_elements3D("+ rendered element3D [%lu]", it->entities[i])
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged()) {
            zox_log(" > failed to render element3D [%i]: [%i] - [%ix%i:%i]\n", i, meshIndicies->length, meshGPULink->value.x, meshGPULink->value.y, uvsGPULink->value)
            break;
        }
#endif
    }
    if (has_set_material) {
        zox_gpu_blend_disable();
        zox_gpu_disable_buffer(material_attributes->vertex_color);
        zox_gpu_disable_buffer(material_attributes->vertex_uv);
        zox_gpu_disable_buffer(material_attributes->vertex_position);
        opengl_disable_texture(0);
        opengl_unset_mesh();
        zox_disable_material();
    }
} zoxd_system(Element3DRenderSystem)