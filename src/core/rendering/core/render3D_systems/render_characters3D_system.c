// #define zox_debug_render3D_colored
#define max_character_mesh_indicies 1000000

void RenderCharacters3DSystem(ecs_iter_t *it) {
    if (it->count == 0) return;
    const Position3D *positions = ecs_field(it, Position3D, 3);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 4);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 5);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 6);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 7);
    unsigned char has_set_material = 0;
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
        if (meshIndicies2->length == 0) continue;
        if (meshIndicies2->length < 0) {
            zoxel_log(" > character mesh is negative [%lu]: [%i]\n", it->entities[i], meshIndicies2->length);
            continue;
        }
        if (meshIndicies2->length > max_character_mesh_indicies) {
            zoxel_log(" > character mesh too large [%lu]: [%i]\n", it->entities[i], meshIndicies2->length);
            continue;
        }
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        if (colorsGPULink->value == 0) continue;
        const Position3D *position = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(colored3D_material);
            glUniformMatrix4fv(attributes_colored3D.view_matrix, 1, GL_FALSE, (float*) &render_camera_matrix);
            glUniform4f(attributes_colored3D.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
            glUniform1f(attributes_colored3D.scale, 1.0f);
            glUniform1f(attributes_colored3D.brightness, 1.0f);
        }
        render_character3D(meshIndicies2->length, meshGPULink->value, colorsGPULink->value, position->value, rotation->value);
        /*if (check_opengl_error("[render_characters - render_character3D]") != 0) {
            zoxel_log(" > rendered character [%lu]: [%i]\n", it->entities[i], meshIndicies2->length);
        }*/
        #ifdef zox_debug_render3D_colored
            meshes++;
            tris_rendered += meshIndicies2->length / 3;
        #endif
    }
    #ifdef zox_debug_render3D_colored
        zoxel_log("  > rendered meshes [%i] unused meshes [%i] tris [%i]\n", meshes, zero_meshes, tris_rendered);
    #endif
    if (has_set_material) {
        opengl_unset_mesh();
        opengl_disable_opengl_program();
    }
    // check_opengl_error("[render_characters]");
} zox_declare_system(RenderCharacters3DSystem)