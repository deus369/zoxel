// #define zox_debug_render3D_colored
// #define max_character_mesh_indicies 1000000
//#define zox_disable_render_characters
int zox_statistics_characters_rendered;
// extern int zox_statistics_characters_rendered;
void RenderCharacters3DSystem(ecs_iter_t *it) {
    if (!material_colored3D) {
        return;
    }
    zox_field_world()
    const GLuint material_link = zox_get_value(material_colored3D, MaterialGPULink)
    const MaterialColored3D *material_attributes = zox_get(material_colored3D, MaterialColored3D)
    zox_field_in(MeshIndicies, meshIndiciess, 1)
    zox_field_in(MeshGPULink, meshGPULinks, 2)
    zox_field_in(ColorsGPULink, colorsGPULinks, 3)
    zox_field_in(TransformMatrix, transformMatrixs, 4)
    zox_field_in(RenderDisabled, renderDisableds, 5)
    byte has_set_material = 0;
    for (int i = 0; i < it->count; i++) {
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        if (meshIndicies->length == 0) continue;
        zox_field_i(MeshGPULink, meshGPULinks, meshGPULink)
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        zox_field_i(ColorsGPULink, colorsGPULinks, colorsGPULink)
        if (colorsGPULink->value == 0) continue;
        zox_field_i(TransformMatrix, transformMatrixs, transformMatrix)
        if (!has_set_material) {
            has_set_material = 1;
#ifdef zox_transparent_voxes
            opengl_enable_blend();
            glDisable(GL_CULL_FACE);
#endif
            opengl_set_material(material_link);
            opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
            opengl_set_float4(material_attributes->fog_data, get_fog_value());
            opengl_set_float(material_attributes->brightness, 1);
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);
        opengl_render(meshIndicies->length);
        catch_basic3D_errors("! RenderCharacters3DSystem");
        zox_statistics_characters_rendered++;
    }
    if (has_set_material) {
        opengl_disable_buffer(material_attributes->vertex_color);
        opengl_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        opengl_disable_opengl_program();
#ifdef zox_transparent_voxes
        opengl_disable_blend();
        glEnable(GL_CULL_FACE);
#endif
    }
} zox_declare_system(RenderCharacters3DSystem)
