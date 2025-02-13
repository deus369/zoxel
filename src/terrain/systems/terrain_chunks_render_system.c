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
    const MaterialGPULink *materialGPULink;
    const TextureGPULink *textureGPULink;
    const MaterialTextured3D *material_attributes;
    zox_field_world()
    zox_field_in(TransformMatrix, transformMatrixs, 1)
    zox_field_in(MeshGPULink, meshGPULinks, 2)
    zox_field_in(UvsGPULink, uvsGPULinks, 3)
    zox_field_in(ColorsGPULink, colorsGPULinks, 4)
    zox_field_in(MeshIndicies, meshIndiciess, 5)
    zox_field_in(VoxLink, voxLinks, 6)
    zox_field_in(RenderDisabled, renderDisableds, 7)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        if (!meshIndicies->length) continue;
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        if (!meshGPULink->value.x) continue;
        zox_field_i(VoxLink, voxLinks, voxLink)
        if (!voxLink->value) continue;
        zox_field_i(UvsGPULink, uvsGPULinks, uvsGPULink)
        zox_field_i(ColorsGPULink, colorsGPULinks, colorsGPULink)
        zox_field_i(TransformMatrix, transformMatrixs, transformMatrix)
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
            opengl_set_material(materialGPULink->value);
            opengl_bind_texture(textureGPULink->value);
            opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
            opengl_set_float4(material_attributes->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
            opengl_set_float(material_attributes->brightness, 1);
        }
        opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_uv_buffer(material_attributes->vertex_uv, uvsGPULink->value);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        opengl_render(meshIndicies->length);
#ifdef zoxel_catch_opengl_errors
        catch_opengl_error("terrain")
#endif
    }
    if (has_set_material) {
        opengl_disable_buffer(material_attributes->vertex_color);
        opengl_disable_buffer(material_attributes->vertex_uv);
        opengl_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        opengl_disable_texture(0);
        opengl_disable_opengl_program();
    }
} zox_declare_system(TerrainChunksRenderSystem)
