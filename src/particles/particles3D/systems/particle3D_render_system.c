// #define zox_debug_particle3Ds
#ifdef zox_debug_particle3Ds
const float3 debug_particle_line_addition = (float3) { 0, 0.2f, 0 };
extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

// todo: use one draw call with array of positions, instead of multiple calls here
// todo: also push in colors
// todo: test function that spawns 100k particles at once and lerps their positions or something out from origin

void Particle3DRenderSystem(ecs_iter_t *it) {
    // zox_log("particles [%i]\n", it->count)
    zox_statistics_particles3D += it->count;
    zox_gpu_blend_enable();
    zox_gpu_material(particle3D_material);
    zox_gpu_float4(particle3D_fog_data_location, get_fog_value());
    zox_gpu_float4x4(particle3D_camera_matrix_location, render_camera_matrix);
    float fov_fixer = 90.0f / ((float) render_camera_fov);
    zox_gpu_float(particle3D_location_thickness, fov_fixer * default_point_thickness * viewport_scale);
    zox_sys_begin()
    zox_sys_in(Position3D)
    zox_sys_in(Color)
#ifndef zox_disable_particles_gpu_instancing

    // position
    glBindBuffer(GL_ARRAY_BUFFER, particle3D_instanced_position_buffer);
    // glBufferData(GL_ARRAY_BUFFER, it->count * sizeof(float3), position3Ds, GL_STATIC_DRAW);
    glVertexAttribPointer(particle3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBufferSubData(GL_ARRAY_BUFFER, 0, it->count * sizeof(float3), Position3D_); //, GL_STATIC_DRAW);
    glEnableVertexAttribArray(particle3D_position_location);// Set divisor for position attribute
    glVertexAttribDivisor(particle3D_position_location, 1); // Update per instance

    // colors
    glBindBuffer(GL_ARRAY_BUFFER, particle3D_instanced_color_buffer);
    // glBufferData(GL_ARRAY_BUFFER, it->count * sizeof(color), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(particle3D_color_location, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*) 0);
    glBufferSubData(GL_ARRAY_BUFFER, 0, it->count * sizeof(color), Color_); // , GL_STATIC_DRAW);
    glEnableVertexAttribArray(particle3D_color_location);// Set divisor for position attribute
    glVertexAttribDivisor(particle3D_color_location, 1); // Update per instance

    // draw
    glDrawArraysInstanced(GL_POINTS, 0, 1, it->count);

    // resets
    glVertexAttribDivisor(particle3D_color_location, 0); // Update per instance
    glVertexAttribDivisor(particle3D_position_location, 0); // Update per instance
    glDisableVertexAttribArray(particle3D_color_location);
    glDisableVertexAttribArray(particle3D_position_location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#else
    glEnableVertexAttribArray(particle3D_position_location);
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Position3D, position3D)
        zox_sys_i(Color, color)
        const float data[] = { position3D->value.x, position3D->value.y, position3D->value.z };
        glVertexAttribPointer(particle3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, data);
        float4 color_f = color_to_float4(color->value);
        glUniform4f(particle3D_color_location, color_f.x, color_f.y, color_f.z, color_f.w);
        zox_gpu_render_points(1);
#ifdef zox_debug_particle3Ds
        spawn_line3D(world, position3D->value, float3_add(position3D->value, debug_particle_line_addition), 0.5f, 0.03);
#endif
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" ! Particle3DRenderSystem [%lu]: [%i]\n", it->entities[i], 1)
            break;
        }
#endif
    }
    glDisableVertexAttribArray(particle3D_position_location);
#endif
    zox_disable_material();
    zox_gpu_blend_disable();
} zox_declare_system(Particle3DRenderSystem)

// const Rotation3D *rotation3D = &rotation3Ds[i];
// const Scale1D *scale1D = &scale1Ds[i];
// glVertexAttribPointer(particle3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, position3D->value);
// zox_gpu_float3(particle3D_position_location, position3D->value);
// this keeps a consistent thickness
// float distance_to_camera = float3_distance(camera_position, position3D->value);
// float point_thickness = default_point_thickness - distance_to_camera / default_point_thickness;
// float point_thickness = distance_to_camera / default_point_thickness;
// glPointSize(point_thickness);
// zox_log("   > distance [%f] - t[%f]\n", distance_to_camera, point_thickness);
