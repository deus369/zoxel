// #define zox_debug_particle3Ds

#ifdef zox_debug_particle3Ds
    const float3 debug_particle_line_addition = (float3) { 0, 0.2f, 0 };
    extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void Particle3DRenderSystem(ecs_iter_t *it) {
    float point_thickness = 5.0f;
    glUseProgram(particle3D_material);
    opengl_set_float4(particle3D_fog_data_location, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
    glUniformMatrix4fv(particle3D_camera_matrix_location, 1, GL_FALSE, (float*) &render_camera_matrix);
    glEnableVertexAttribArray(particle3D_position_location);
    const Position3D *position3Ds = ecs_field(it, Position3D, 2);
    // const Rotation3D *rotation3Ds = ecs_field(it, Rotation3D, 3);
    // const Scale1D *scale1Ds = ecs_field(it, Scale1D, 4);
    for (int i = 0; i < it->count; i++) {
        const Position3D *position3D = &position3Ds[i];
        // const Rotation3D *rotation3D = &rotation3Ds[i];
        // const Scale1D *scale1D = &scale1Ds[i];
        // glVertexAttribPointer(particle3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, position3D->value);
        // opengl_set_float3(particle3D_position_location, position3D->value);
        glPointSize(point_thickness);
        float data[] = { position3D->value.x, position3D->value.y, position3D->value.z };
        glVertexAttribPointer(particle3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, data);
        float3 color_rgb_f3 = float3_zero; // color_rgb_to_float3(colorRGB->value);
        glUniform3f(particle3D_color_location, color_rgb_f3.x, color_rgb_f3.y, color_rgb_f3.z);
        glDrawArrays(GL_POINTS, 0, 1);

        #ifdef zox_debug_particle3Ds
            spawn_line3D(world, position3D->value, float3_add(position3D->value, debug_particle_line_addition), 0.5f, 0.03);
        #endif
    }
    glDisableVertexAttribArray(particle3D_position_location);
    glUseProgram(0);
} zox_declare_system(Particle3DRenderSystem)