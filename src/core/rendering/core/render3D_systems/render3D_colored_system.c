// #define zox_debug_render3D_colored

void Render3DColoredSystem(ecs_iter_t *it) {
    // if (check_opengl_error("[Render3DColoredSystem Error]")) return;
    // OpenGL error GL_OUT_OF_MEMORY?
    if (colored3D_material == 0 || it->count == 0) return;
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 6);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 7);
    unsigned char is_set_material = 0;
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
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (meshGPULink->value.x == 0 || meshGPULink->value.y == 0) continue;
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        if (colorsGPULink->value == 0) continue;
        const Position3D *position = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        if (!is_set_material) {
            is_set_material = 1;
            opengl_set_material(colored3D_material);
            glUniformMatrix4fv(attributes_colored3D.view_matrix, 1, GL_FALSE, (float*) &render_camera_matrix);
            uint fog_data_location = glGetUniformLocation(colored3D_material, "fog_data");
            glUniform4f(fog_data_location, fog_color.x, fog_color.y, fog_color.z, fog_density);
            glUniform1f(attributes_colored3D.scale, 1.0f);
            glUniform1f(attributes_colored3D.brightness, 1.0f);
        }
        render_colored3D(meshGPULink->value, colorsGPULink->value, meshIndicies2->length, position->value, rotation->value);
        /*if (check_opengl_error("[Render3DColoredSystem Error]")) {
            zoxel_log("     + meshIndicies2->length [%i]\n", meshIndicies2->length);
            return;
        }*/
        #ifdef zox_debug_render3D_colored
            meshes++;
            tris_rendered += meshIndicies2->length / 3;
        #endif
    }
    #ifdef zox_debug_render3D_colored
        zoxel_log("  > rendered meshes [%i] unused meshes [%i] tris [%i]\n", meshes, zero_meshes, tris_rendered);
    #endif
    if (is_set_material) {
        opengl_unset_mesh();
        opengl_disable_opengl_program();
    }
    // if (check_opengl_error("[Render3DColoredSystem Error]")) return;
} zox_declare_system(Render3DColoredSystem)

    // opengl_unset_mesh();
    // opengl_disable_texture(false);
    // glUniform4f(attributes_colored3D.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
    // zoxel_log(" - Rendering 3D Colored Mesh [%lu]\n", (long int) it->entities[i]);
// unsigned char has_set_single_material = 0;
/*if (!has_set_single_material) {
    has_set_single_material = 1;
    opengl_set_material(colored3D_material);
    glUniformMatrix4fv(attributes_colored3D.view_matrix, 1, GL_FALSE, (float*) &render_camera_matrix);
    glUniform1f(attributes_colored3D.scale, scale1D->value);
    glUniform1f(attributes_colored3D.brightness, brightness->value);
    uint fog_data_location = glGetUniformLocation(colored3D_material, "fog_data");
    glUniform4f(fog_data_location, fog_color.x, fog_color.y, fog_color.z, fog_density);
    // glUniform4f(attributes_colored3D.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
    // zoxel_log(" - Rendering 3D Colored Mesh [%lu]\n", (long int) it->entities[i]);
}*/

// const Scale1D *scale1D = &scale1Ds[i];
// const Brightness *brightness = &brightnesses[i];
// glUniform1f(attributes_colored3D.scale, scale1D->value);
// glUniform1f(attributes_colored3D.brightness, brightness->value);
        /*if (check_opengl_error("[render_colored3D Error]")) {
            zoxel_log(" ! meshIndicies2->length [%i]\n", meshIndicies2->length);
            break;
        }*/
        /* else {
            zoxel_log(" > meshIndicies2->length [%i]\n", meshIndicies2->length);
        }*/