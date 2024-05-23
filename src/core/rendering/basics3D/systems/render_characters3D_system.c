// #define zox_debug_render3D_colored
// #define max_character_mesh_indicies 1000000
//#define zox_disable_render_characters
extern int zox_statistics_characters_rendered;

void RenderCharacters3DSystem(ecs_iter_t *it) {
    if (!material_colored3D) zox_log(" ! RenderCharacters3DSystem - has no material\n")
    if (!material_colored3D) return;
    zox_iter_world()
    const GLuint material_link = zox_get_value(material_colored3D, MaterialGPULink)
    const MaterialColored3D *material_attributes = zox_get(material_colored3D, MaterialColored3D)
    zox_field_in(MeshIndicies, meshIndiciess, 1)
    zox_field_in(MeshGPULink, meshGPULinks, 2)
    zox_field_in(ColorsGPULink, colorsGPULinks, 3)
    zox_field_in(TransformMatrix, transformMatrixs, 4)
    zox_field_in(RenderDisabled, renderDisableds, 5)
    unsigned char has_set_material = 0;
    int rendered_count = 0;
#ifdef zox_debug_render3D_colored
    int zero_meshes = 0;
    int meshes = 0;
    int tris_rendered = 0;
#endif
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(RenderDisabled, renderDisableds, renderDisabled)
        if (renderDisabled->value) continue;
        zox_field_i_in(MeshIndicies, meshIndiciess, meshIndicies)
#ifdef zox_debug_render3D_colored
        if (meshIndicies->length == 0) zero_meshes++;
#endif
        // if (meshIndicies->length == 0) zox_log(" ! RenderCharacters3DSystem - meshIndicies 0\n")
        if (meshIndicies->length == 0) continue;
        zox_field_i_in(MeshGPULink, meshGPULinks, meshGPULink)
        zox_field_i_in(ColorsGPULink, colorsGPULinks, colorsGPULink)
        zox_field_i_in(TransformMatrix, transformMatrixs, transformMatrix)
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(material_link);
            opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
            opengl_set_float4(material_attributes->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
            opengl_set_float(material_attributes->brightness, 1);
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
        opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);
#ifndef zox_disable_render_characters
#ifdef zox_characters_as_cubes
        opengl_render(36);
#else
        opengl_render(meshIndicies->length);
#endif
#endif
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zoxel_log(" > could not render character [%i]: indicies [%i] - [%ix%i:%i]\n", rendered_count, meshIndicies->length, meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value);
            break;
        }
#endif
#ifdef zox_debug_render3D_colored
        meshes++;
        tris_rendered += meshIndicies->length / 3;
#endif
        rendered_count++;
        zox_statistics_characters_rendered++;
    }
#ifdef zox_debug_render3D_colored
    zoxel_log("  > rendered meshes [%i] unused meshes [%i] itcount [%i] tris [%i]\n", meshes, zero_meshes, it->count, tris_rendered);
#endif
    if (has_set_material) {
        opengl_disable_buffer(material_attributes->vertex_color);
        opengl_disable_buffer(material_attributes->vertex_position);
        opengl_unset_mesh();
        opengl_disable_opengl_program();
    }
} zox_declare_system(RenderCharacters3DSystem)
