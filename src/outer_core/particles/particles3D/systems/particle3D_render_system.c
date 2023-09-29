#define zox_debug_particle3Ds
#ifdef zox_debug_particle3Ds
    extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

void Particle3DRenderSystem(ecs_iter_t *it) {
    // glUseProgram(line3D_material);
    // opengl_set_float4(line3D_fog_data_location, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
    // glUniformMatrix4fv(line3D_camera_matrix_location, 1, GL_FALSE, (float*) &render_camera_matrix);
    // glEnableVertexAttribArray(line3D_position_location);
    const Position3D *position3Ds = ecs_field(it, Position3D, 2);
    const Rotation3D *rotation3Ds = ecs_field(it, Rotation3D, 3);
    const Scale1D *scale1Ds = ecs_field(it, Scale1D, 4);
    for (int i = 0; i < it->count; i++) {
        const Position3D *position3D = &position3Ds[i];
        const Rotation3D *rotation3D = &rotation3Ds[i];
        const Scale1D *scale1D = &scale1Ds[i];
        
        /*float line_data[] = { lineData3D->value.x, lineData3D->value.y, lineData3D->value.z, lineData3D->value.w, lineData3D->value.u, lineData3D->value.v };
        glLineWidth(lineThickness->value);
        glVertexAttribPointer(line3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, line_data);
        float3 color_rgb_f3 = color_rgb_to_float3(colorRGB->value);
        glUniform3f(line3D_color_location, color_rgb_f3.x, color_rgb_f3.y, color_rgb_f3.z);
        glDrawArrays(GL_LINES, 0, 3);*/
        #ifdef zox_debug_particle3Ds
            spawn_line3D(world, position3D->value, float3_add(position3D->value, (float3) { 0, 0.4f, 0 }), 0.5f, 0.1);
        #endif
    }
    // glDisableVertexAttribArray(line3D_position_location);
    // glUseProgram(0);
} zox_declare_system(Particle3DRenderSystem)