// #define zoxel_render3D_uvs_system_overdebug
// later store commands per material to optimize this process

#define catch_opengl_error(type)\
if (check_opengl_error_unlogged()) {\
        zox_log(" > could not render "type" [%i]: indicies [%i] - [%ix%i]\n", i, meshIndicies->length, meshGPULink->value.x, meshGPULink->value.y);\
        break;\
}

void TerrainChunksRenderSystem(ecs_iter_t *it) {
#ifdef zox_disable_chunks_rendering
    return;
#endif
    // todo: optimize transform so it doesn't update every frame? StaticTransform tag
    byte has_set_material = 0;
    ecs_entity_t vox_entity = 0;
    const MaterialGPULink *materialGPULink = NULL;
    const TextureGPULink *textureGPULink = NULL;
    const MaterialTextured3D *material_attributes = NULL;
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(TransformMatrix)
    zox_sys_in(MeshGPULink)
    zox_sys_in(UvsGPULink)
    zox_sys_in(ColorsGPULink)
    zox_sys_in(MeshIndicies)
    zox_sys_in(VoxLink)
    zox_sys_in(RenderDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(VoxLink, voxLink)
        zox_sys_i(UvsGPULink, uvsGPULink)
        zox_sys_i(ColorsGPULink, colorsGPULink)
        zox_sys_i(TransformMatrix, transformMatrix)
        if (renderDisabled->value) continue;
        if (!meshIndicies->length) continue;
        if (!meshGPULink->value.x) continue;
        if (!voxLink->value) continue;
        if (vox_entity != voxLink->value) {
            vox_entity = voxLink->value;
            const TilemapLink *tilemapLink = zox_get(voxLink->value, TilemapLink)
            materialGPULink = zox_get(tilemapLink->value, MaterialGPULink)
            if (!materialGPULink->value) continue;
            textureGPULink = zox_get(tilemapLink->value, TextureGPULink)
            if (!textureGPULink->value) continue;
            material_attributes = zox_get(tilemapLink->value, MaterialTextured3D)
            if (!material_attributes) break;
        }
        if (!has_set_material) {
            has_set_material = 1;
            zox_gpu_material(materialGPULink->value);
            opengl_bind_texture(textureGPULink->value);
            zox_gpu_float4x4(material_attributes->camera_matrix, render_camera_matrix);
            zox_gpu_float4(material_attributes->fog_data, get_fog_value());
            zox_gpu_float(material_attributes->brightness, 1);
        }
        zox_gpu_float4x4(material_attributes->transform_matrix, transformMatrix->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_uv_buffer(material_attributes->vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        zox_gpu_render(meshIndicies->length);
#ifdef zoxel_catch_opengl_errors
        catch_opengl_error("terrain")
#endif
    }
    if (has_set_material) {
        zox_gpu_disable_buffer(material_attributes->vertex_color);
        zox_gpu_disable_buffer(material_attributes->vertex_uv);
        zox_gpu_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        opengl_disable_texture(0);
        zox_disable_material();
    }
} zox_declare_system(TerrainChunksRenderSystem)
