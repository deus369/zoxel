// #define zox_debug_particle3Ds
const float default_point_thickness = 32.0f;
#ifdef zox_debug_particle3Ds
const float3 debug_particle_line_addition = (float3) { 0, 0.2f, 0 };
extern ecs_entity_t spawn_line3D(ecs_world_t *world, float3 pointA, float3 pointB, float thickness, double life_time);
#endif

/*float float4x4_mul_float_z(float4x4 matrix, float value) {
    return value * matrix.z.z;
}*/

void Particle3DRenderSystem(ecs_iter_t *it) {
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    // float3 camera_position = float4x4_get_position(render_camera_matrix);
    // zox_log("   > camera_position: %fx%fx%f\n", camera_position.x, camera_position.y, camera_position.z);
    // zox_log("   > render_camera_matrix.z: %f\n", camera_position.z);
    glUseProgram(particle3D_material);
    opengl_set_float4(particle3D_fog_data_location, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
    glUniformMatrix4fv(particle3D_camera_matrix_location, 1, GL_FALSE, (float*) &render_camera_matrix);
    glEnableVertexAttribArray(particle3D_position_location);
    float fov_fixer = 90.0f / ((float) render_camera_fov);
    // if (fov_fixer != 1) fov_fixer *= 1.3f;
    opengl_set_float(particle3D_location_thickness, fov_fixer * default_point_thickness);
    // glPointSize(default_point_thickness);
    const Position3D *position3Ds = ecs_field(it, Position3D, 2);
    // const Rotation3D *rotation3Ds = ecs_field(it, Rotation3D, 3);
    // const Scale1D *scale1Ds = ecs_field(it, Scale1D, 4);
    const ColorRGB *colorRGBs = ecs_field(it, ColorRGB, 5);
    for (int i = 0; i < it->count; i++) {
        const Position3D *position3D = &position3Ds[i];
        const ColorRGB *colorRGB = &colorRGBs[i];
        // const Rotation3D *rotation3D = &rotation3Ds[i];
        // const Scale1D *scale1D = &scale1Ds[i];
        // glVertexAttribPointer(particle3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, position3D->value);
        // opengl_set_float3(particle3D_position_location, position3D->value);
        // this keeps a consistent thickness
        // float distance_to_camera = float3_distance(camera_position, position3D->value);
        // float point_thickness = default_point_thickness - distance_to_camera / default_point_thickness;
        // float point_thickness = distance_to_camera / default_point_thickness;
        // glPointSize(point_thickness);
        // zox_log("   > distance [%f] - t[%f]\n", distance_to_camera, point_thickness);
        float data[] = { position3D->value.x, position3D->value.y, position3D->value.z };
        glVertexAttribPointer(particle3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, data);
        float3 color_rgb_f3 = color_rgb_to_float3(colorRGB->value); // float3_zero; // color_rgb_to_float3(colorRGB->value);
        glUniform3f(particle3D_color_location, color_rgb_f3.x, color_rgb_f3.y, color_rgb_f3.z);
        glDrawArrays(GL_POINTS, 0, 1);
#ifdef zox_debug_particle3Ds
        spawn_line3D(world, position3D->value, float3_add(position3D->value, debug_particle_line_addition), 0.5f, 0.03);
#endif
    }
    glDisableVertexAttribArray(particle3D_position_location);
    glUseProgram(0);
} zox_declare_system(Particle3DRenderSystem)
