// #define zox_debug_render3D_colored
#define max_character_mesh_indicies 1000000

void RenderCharacters3DSystem(ecs_iter_t *it) {
    if (attributes_colored3D.vertex_position < 0 || attributes_colored3D.vertex_color < 0) return;
    const Position3D *positions = ecs_field(it, Position3D, 2);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 3);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 6);
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
        // testing
        /*if (meshIndicies2->length < 0) {
            zoxel_log(" > character mesh is negative [%lu]: [%i]\n", it->entities[i], meshIndicies2->length);
            continue;
        }
        if (meshIndicies2->length > max_character_mesh_indicies) {
            zoxel_log(" > character mesh too large [%lu]: [%i]\n", it->entities[i], meshIndicies2->length);
            continue;
        }*/
        // if (ecs_get(it->world, it->entities[i], MeshDirty)->value) continue;
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        if (colorsGPULink->value == 0) continue;
        const Position3D *position = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        if (!has_set_material) {
            has_set_material = 1;
            opengl_set_material(colored3D_material);
            glUniformMatrix4fv(attributes_colored3D.camera_matrix, 1, GL_FALSE, (float*) &render_camera_matrix);
            glUniform1f(attributes_colored3D.scale, 1.0f);
            glUniform4f(attributes_colored3D.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
            glUniform1f(attributes_colored3D.brightness, 1.0f);
        }
        render_character3D(meshIndicies2->length, meshGPULink->value, colorsGPULink->value, position->value, rotation->value);
        /*if (check_opengl_error("[RenderCharacters3DSystem 1]") != 0) {
            zoxel_log(" > rendered character [%lu]: [%i] - [%ix%i:%i]\n", it->entities[i], meshIndicies2->length, meshGPULink->value.x, meshGPULink->value.y, colorsGPULink->value);
            // break;
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
} zox_declare_system(RenderCharacters3DSystem)