// #define zox_debug_render3D_colored
extern float4x4 render_camera_matrix;

void Render3DColoredSystem(ecs_iter_t *it) {
    if (colored3D_material == 0 || it->count == 0) return;
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 6);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 7);
    // set fog and camera for material
    opengl_set_material(colored3D_material);
    glUniformMatrix4fv(materialColored3D.view_matrix, 1, GL_FALSE, (float*) &render_camera_matrix);
    uint fog_data_location = glGetUniformLocation(colored3D_material, "fog_data");
    glUniform4f(fog_data_location, fog_color.x, fog_color.y, fog_color.z, fog_density);
    // for now
    glUniform1f(materialColored3D.scale, 1.0f);
    glUniform1f(materialColored3D.brightness, 1.0f);
    // glUniform4f(materialColored3D.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
    // zoxel_log(" - Rendering 3D Colored Mesh [%lu]\n", (long int) it->entities[i]);
    #ifdef zox_debug_render3D_colored
        int zero_meshes = 0;
        int meshes = 0;
        int tris_rendered = 0;
    #endif
    for (int i = 0; i < it->count; i++) {
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (meshGPULink->value.x == 0) continue;
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        #ifdef zox_debug_render3D_colored
            if (meshIndicies2->length == 0) zero_meshes++;
        #endif
        if (meshIndicies2->length == 0) continue;
        const Position3D *position = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        // glUniform1f(materialColored3D.scale, scale1D->value);
        // glUniform1f(materialColored3D.brightness, brightness->value);
        opengl_set_buffer_attributes_colors(meshGPULink->value.y, colorsGPULink->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_set_material3D_colors_properties(position->value, rotation->value);
        opengl_draw_triangles(meshIndicies2->length);
        // check_opengl_error("Render3DColoredSystem");
        #ifdef zox_debug_render3D_colored
            meshes++;
            tris_rendered += meshIndicies2->length / 3;
        #endif
    }
    #ifdef zox_debug_render3D_colored
        zoxel_log("  > rendered meshes [%i] unused meshes [%i] tris [%i]\n", meshes, zero_meshes, tris_rendered);
    #endif
    // check_opengl_error("Render3DColoredSystem");
    opengl_unset_mesh();
    opengl_disable_opengl_program();
}
zox_declare_system(Render3DColoredSystem)

// unsigned char has_set_single_material = 0;
/*if (!has_set_single_material) {
    has_set_single_material = 1;
    opengl_set_material(colored3D_material);
    glUniformMatrix4fv(materialColored3D.view_matrix, 1, GL_FALSE, (float*) &render_camera_matrix);
    glUniform1f(materialColored3D.scale, scale1D->value);
    glUniform1f(materialColored3D.brightness, brightness->value);
    uint fog_data_location = glGetUniformLocation(colored3D_material, "fog_data");
    glUniform4f(fog_data_location, fog_color.x, fog_color.y, fog_color.z, fog_density);
    // glUniform4f(materialColored3D.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
    // zoxel_log(" - Rendering 3D Colored Mesh [%lu]\n", (long int) it->entities[i]);
}*/