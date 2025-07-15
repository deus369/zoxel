// #define zox_debug_render3D_colored
// #define max_character_mesh_indicies 1000000
//#define zox_disable_render_characters
int zox_statistics_characters_rendered;
// extern int zox_statistics_characters_rendered;
void RenderCharacters3DSystem(ecs_iter_t *it) {
    zox_sys_world()
    if (!zox_valid(material_colored3D)) {
        return;
    }
    zox_geter_value(material_colored3D, MaterialGPULink, uint, material_link)
    if (!material_link) {
        return;
    }
    zox_geter(material_colored3D, MaterialColored3D, material_attributes)
    byte has_set_material = 0;
    zox_sys_begin()
    zox_sys_in(MeshIndicies)
    zox_sys_in(MeshGPULink)
    zox_sys_in(ColorsGPULink)
    zox_sys_in(TransformMatrix)
    zox_sys_in(RenderDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(RenderDisabled, renderDisabled)
        zox_sys_i(MeshIndicies, meshIndicies)
        zox_sys_i(MeshGPULink, meshGPULink)
        zox_sys_i(ColorsGPULink, colorsGPULink)
        zox_sys_i(TransformMatrix, transformMatrix)
        if (renderDisabled->value || !meshIndicies->length || !meshGPULink->value.x || !meshGPULink->value.y || !colorsGPULink->value) {
            continue;
        }
        if (!has_set_material) {
            has_set_material = 1;
#ifdef zox_transparent_voxes
            opengl_enable_blend();
            glDisable(GL_CULL_FACE);
#endif
            zox_enable_material(material_link);
            opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
            zox_gpu_float4(material_attributes->fog_data, get_fog_value());
            zox_gpu_float(material_attributes->brightness, 1);
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);
        zox_gpu_render(meshIndicies->length);
        catch_basic3D_errors("! RenderCharacters3DSystem");
        zox_statistics_characters_rendered++;
    }
    if (has_set_material) {
        opengl_disable_buffer(material_attributes->vertex_color);
        opengl_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        zox_disable_material();
#ifdef zox_transparent_voxes
        opengl_disable_blend();
        glEnable(GL_CULL_FACE);
#endif
    }
} zox_declare_system(RenderCharacters3DSystem)
