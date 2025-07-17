void Line3DRenderSystem(ecs_iter_t *it) {
    zox_gpu_blend_enable();
    zox_gpu_material(line3D_material);
    zox_gpu_float4(line3D_fog_data_location, get_fog_value());
    zox_gpu_float4x4(line3D_camera_matrix_location, render_camera_matrix);
    glEnableVertexAttribArray(line3D_position_location);
    zox_sys_begin()
    zox_sys_in(LineData3D)
    zox_sys_in(LineThickness)
    zox_sys_in(Color)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(LineData3D, lineData3D)
        zox_sys_i(LineThickness, lineThickness)
        zox_sys_i(Color, colorr)
        glLineWidth(lineThickness->value);
        const float4 colorf = color_to_float4(colorr->value);
        glVertexAttribPointer(line3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, (GLfloat*) &lineData3D->value);
        zox_gpu_float4(line3D_color_location, colorf);
        zox_gpu_render_lines(3);
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" ! Line3DRenderSystem [%lu]: [%i]\n", it->entities[i], 2)
            break;
        }
#endif
    }
    glDisableVertexAttribArray(line3D_position_location);
    zox_disable_material();
    zox_gpu_blend_disable();
} zox_declare_system(Line3DRenderSystem)