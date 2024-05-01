// #define zox_debug_render3D_colored
// #define max_character_mesh_indicies 1000000
void RenderCharacters3DSystem(ecs_iter_t *it) {
    zox_field_in(Position3D, position3Ds, 2)
    zox_field_in(Rotation3D, rotation3Ds, 3)
    zox_field_in(Scale1D, scale1Ds, 4)
    zox_field_in(MeshIndicies, meshIndiciess, 5)
    zox_field_in(MeshGPULink, meshGPULinks, 6)
    zox_field_in(ColorsGPULink, colorsGPULinks, 7)
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
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        zox_field_i_in(ColorsGPULink, colorsGPULinks, colorsGPULink)
        if (colorsGPULink->value == 0) continue;
        zox_field_i_in(Position3D, position3Ds, position3D)
        zox_field_i_in(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i_in(Scale1D, scale1Ds, scale1D)
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(colored3D_material);
            opengl_set_matrix(attributes_colored3D.camera_matrix, render_camera_matrix);
#ifndef zox_debug_color_shader
            opengl_set_float(attributes_colored3D.scale, 1);
            opengl_set_float4(attributes_colored3D.fog_data, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
            opengl_set_float(attributes_colored3D.brightness, 1);
#endif
        }
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_enable_vertex_buffer(attributes_colored3D.vertex_position, meshGPULink->value.y);
#ifndef zox_debug_color_shader
        opengl_enable_color_buffer(attributes_colored3D.vertex_color, colorsGPULink->value);
#endif
        opengl_set_float3(attributes_colored3D.position, position3D->value);
        opengl_set_float4(attributes_colored3D.rotation, rotation3D->value);
        opengl_set_float(attributes_colored3D.scale, scale1D->value);
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
    zoxel_log("  > rendered meshes [%i] unused meshes [%i] tris [%i]\n", meshes, zero_meshes, tris_rendered);
#endif
    if (has_set_material) {
        opengl_disable_buffer(attributes_colored3D.vertex_color);
        opengl_disable_buffer(attributes_colored3D.vertex_position);
        opengl_unset_mesh();
        opengl_disable_opengl_program();
    }
} zox_declare_system(RenderCharacters3DSystem)
