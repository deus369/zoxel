extern byte can_render_ui(ecs_world_t *world, ecs_entity_t e);
// #define zox_time_render3D_textured_system

void Element3DRenderSystem(ecs_iter_t *it) {
    if (!material_textured3D) {
        return;
    }
    zox_field_world()
    byte has_set_material = 0;
    const uint material_link = zox_get_value(material_textured3D, MaterialGPULink)
    const MaterialTextured3D *material_attributes = zox_get(material_textured3D, MaterialTextured3D)
    zox_field_in(TransformMatrix, transformMatrixs, 1)
    zox_field_in(MeshGPULink, meshGPULinks, 2)
    zox_field_in(UvsGPULink, uvsGPULinks, 3)
    zox_field_in(ColorsGPULink, colorsGPULinks, 4)
    zox_field_in(MeshIndicies, meshIndiciess, 5)
    zox_field_in(TextureGPULink, textureGPULinks, 6)
    zox_field_in(RenderDisabled, renderDisableds, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) {
            continue;
        }
        zox_field_e()
        if (!can_render_ui(world, e)) {
            continue;
        }
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        if (!meshIndicies->length) {
            continue;
        }
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        if (!meshGPULink->value.x || !meshGPULink->value.y) {
            continue;
        }
        zox_field_i(TransformMatrix, transformMatrixs, transformMatrix)
        zox_field_i(UvsGPULink, uvsGPULinks, uvsGPULink)
        zox_field_i(ColorsGPULink, colorsGPULinks, colorsGPULink)
        zox_field_i(TextureGPULink, textureGPULinks, textureGPULink)
        if (!has_set_material) {
            has_set_material = 1;
            zox_gpu_blend_enable();
            zox_enable_material(material_link);
            opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
            zox_gpu_float4(material_attributes->fog_data, get_fog_value());
            zox_gpu_float(material_attributes->brightness, 1);
        }
        opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);
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
} zox_declare_system(Element3DRenderSystem)