// #define zox_debug_render3D_colored
// #define max_character_mesh_indicies 1000000

void RenderCharacters3DSystem(ecs_iter_t *it) {
    const Position3D *positions = ecs_field(it, Position3D, 2);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 3);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 6);
    unsigned char has_set_material = 0;
    int rendered_count = 0;
    #ifdef zox_debug_render3D_colored
        int zero_meshes = 0;
        int meshes = 0;
        int tris_rendered = 0;
    #endif
    for (int i = 0; i < it->count; i++) {
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        #ifdef zox_debug_render3D_colored
            if (meshIndicies2->length == 0) zero_meshes++;
        #endif
        #ifndef zox_characters_as_cubes
            if (meshIndicies2->length == 0) continue;
        #endif
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        if (colorsGPULink->value == 0) continue;
        const Position3D *position3D = &positions[i];
        const Rotation3D *rotation3D = &rotations[i];
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
        #ifndef zox_disable_render_characters
            #ifdef zox_characters_as_cubes
                opengl_render(36);
            #else
                opengl_render(meshIndicies2->length);
            #endif
        #endif
        #ifdef zoxel_catch_opengl_errors
            if (check_opengl_error_unlogged() != 0) {
                zoxel_log(" > could not render character [%i]: indicies [%i] - [%ix%i:%i]\n", rendered_count, meshIndicies2->length, meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value);
                break;
            }
        #endif
        #ifdef zox_debug_render3D_colored
            meshes++;
            tris_rendered += meshIndicies2->length / 3;
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