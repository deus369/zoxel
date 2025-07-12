void Line3DRenderSystem(ecs_iter_t *it) {
    opengl_enable_blend();
    glUseProgram(line3D_material);
    glEnableVertexAttribArray(line3D_position_location);
    opengl_set_float4(line3D_fog_data_location, get_fog_value());
    glUniformMatrix4fv(line3D_camera_matrix_location, 1, GL_FALSE, (GLfloat*) &render_camera_matrix);
    zox_sys_begin()
    zox_sys_in(LineData3D)
    zox_sys_in(LineThickness)
    zox_sys_in(Color)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(LineData3D, lineData3D)
        zox_sys_i(LineThickness, lineThickness)
        zox_sys_i(Color, colorr)
        // const float3 color_rgb_f3 = color_rgb_to_float3(colorr->value);
        glLineWidth(lineThickness->value);
        const float4 colorf = color_to_float4(colorr->value);
        glVertexAttribPointer(line3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, (GLfloat*) &lineData3D->value);
        // glUniform3f(line3D_color_location, color_rgb_f3.x, color_rgb_f3.y, color_rgb_f3.z);
        glUniform4f(line3D_color_location, colorf.x, colorf.y, colorf.z, colorf.w);
        glDrawArrays(GL_LINES, 0, 2);
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" ! Line3DRenderSystem [%lu]: [%i]\n", it->entities[i], 2)
            break;
        }
#endif
    }
    glDisableVertexAttribArray(line3D_position_location);
    glUseProgram(0);
    opengl_disable_blend();
} zox_declare_system(Line3DRenderSystem)
