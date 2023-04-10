extern float4x4 main_camera_matrix;

void Render3DColoredSystem(ecs_iter_t *it) {
    const Position3D *positions = ecs_field(it, Position3D, 1);
    const Rotation3D *rotations = ecs_field(it, Rotation3D, 2);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 3);
    const Brightness *brightnesses = ecs_field(it, Brightness, 4);
    const MeshGPULink *meshGPULinks = ecs_field(it, MeshGPULink, 5);
    const ColorsGPULink *colorsGPULinks = ecs_field(it, ColorsGPULink, 6);
    const MeshIndicies *meshIndicies = ecs_field(it, MeshIndicies, 7);
    unsigned char has_set_single_material = 0;
    for (int i = 0; i < it->count; i++) {
        const MeshGPULink *meshGPULink = &meshGPULinks[i];
        if (meshGPULink->value.x == 0) {
            continue;
        }
        const Position3D *position = &positions[i];
        const Rotation3D *rotation = &rotations[i];
        const Scale1D *scale1D = &scale1Ds[i];
        const Brightness *brightness = &brightnesses[i];
        const ColorsGPULink *colorsGPULink = &colorsGPULinks[i];
        const MeshIndicies *meshIndicies2 = &meshIndicies[i];
        if (!has_set_single_material) {
            has_set_single_material = 1;
            opengl_set_material(colored3D_material);
            glUniformMatrix4fv(materialColored3D.view_matrix, 1, GL_FALSE, (float*) &main_camera_matrix);
            glUniform1f(materialColored3D.scale, scale1D->value);
            glUniform1f(materialColored3D.brightness, brightness->value);
            GLuint fog_data_location = glGetUniformLocation(colored3D_material, "fog_data");
            glUniform4f(fog_data_location, fog_color.x, fog_color.y, fog_color.z, fog_density);
            // glUniform4f(materialColored3D.fog_data, fog_color.x, fog_color.y, fog_color.z, fog_density);
            // zoxel_log(" - Rendering 3D Colored Mesh [%lu]\n", (long int) it->entities[i]);
        }
        opengl_set_buffer_attributes_colors(meshGPULink->value.y, colorsGPULink->value);
        opengl_set_mesh_indicies(meshGPULink->value.x);
        opengl_set_material3D_colors_properties(position->value, rotation->value);
        opengl_draw_triangles(meshIndicies2->length);
        // check_opengl_error("Render3DColoredSystem");
    }
    // check_opengl_error("Render3DColoredSystem");
    opengl_unset_mesh();
    opengl_disable_opengl_program();
}
zoxel_declare_system(Render3DColoredSystem)