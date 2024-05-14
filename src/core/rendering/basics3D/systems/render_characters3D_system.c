// #define zox_debug_render3D_colored
// #define max_character_mesh_indicies 1000000
//#define zox_disable_render_characters

void RenderCharacters3DSystem(ecs_iter_t *it) {
    if (!material_colored3D) return;
    zox_iter_world()
    const GLuint material_link = zox_get_value(material_colored3D, MaterialGPULink)
    const MaterialColored3D *material_attributes = zox_get(material_colored3D, MaterialColored3D)
    /*zox_field_in(Position3D, position3Ds, 1)
    zox_field_in(Rotation3D, rotation3Ds, 2)
    zox_field_in(Scale1D, scale1Ds, 3)*/
    zox_field_in(MeshIndicies, meshIndiciess, 4)
    zox_field_in(MeshGPULink, meshGPULinks, 5)
    zox_field_in(ColorsGPULink, colorsGPULinks, 6)
    zox_field_in(TransformMatrix, transformMatrixs, 7)
    unsigned char has_set_material = 0;
    int rendered_count = 0;
#ifdef zox_debug_render3D_colored
    int zero_meshes = 0;
    int meshes = 0;
    int tris_rendered = 0;
#endif
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(MeshIndicies, meshIndiciess, meshIndicies)
#ifdef zox_debug_render3D_colored
        if (meshIndicies->length == 0) zero_meshes++;
#endif
#ifndef zox_characters_as_cubes
        if (meshIndicies->length == 0) continue;
#endif
        zox_field_i_in(MeshGPULink, meshGPULinks, meshGPULink)
        //if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        zox_field_i_in(ColorsGPULink, colorsGPULinks, colorsGPULink)
        //if (colorsGPULink->value == 0) continue;
        /*zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i_in(Scale1D, scale1Ds, scale1D)*/
        zox_field_i_in(TransformMatrix, transformMatrixs, transformMatrix)
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(material_link);
            opengl_set_matrix(material_attributes->camera_matrix, render_camera_matrix);
#ifndef zox_debug_color_shader
            opengl_set_float(material_attributes->scale, 1);
            opengl_set_float4(material_attributes->fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
            opengl_set_float(material_attributes->brightness, 1);
#endif
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(material_attributes->vertex_position, meshGPULink->value.y);
#ifndef zox_debug_color_shader
        opengl_enable_color_buffer(material_attributes->vertex_color, colorsGPULink->value);
#endif
        opengl_set_matrix(material_attributes->transform_matrix, transformMatrix->value);
        /*opengl_set_float3(material_attributes->position, position3D->value);
        opengl_set_float4(material_attributes->rotation, rotation3D->value);
        opengl_set_float(material_attributes->scale, scale1D->value);*/
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
