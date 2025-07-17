// cache camera?? todo: refactor!
extern ecs_entity_t get_root_canvas_camera(ecs_world_t *world, const ecs_entity_t e);

void line2D_render_iteration(ecs_iter_t *it, const byte is_element_line) {
    zox_gpu_material(line2D_material);
    glEnableVertexAttribArray(line2D_position_location);
    float4x4 render_matrix;
    if (is_element_line) {
        glUniform1f(line2D_depth_location, ((int) renderer_layer) * shader_depth_multiplier);
        const float4x4 identity = float4x4_identity();
        render_matrix = identity;
    } else {
        render_matrix = render_camera_matrix;
        glUniform1f(line2D_depth_location, 0);
    }
    zox_gpu_float4x4(line2D_camera_matrix_location, render_matrix);
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(LineData2D)
    zox_sys_in(LineThickness)
    zox_sys_in(Color)
    zox_sys_in(Layer2D)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(Layer2D, layer2D)
        zox_sys_i(LineData2D, lineData2D)
        zox_sys_i(LineThickness, lineThickness)
        zox_sys_i(Color, line_color)
        if (is_element_line) {
            if (layer2D->value != renderer_layer) {
                continue; // render per layer
            }
            zox_field_e()
            if (get_root_canvas_camera(world, e) != renderer_camera) {
                continue;
            }
        }
        const float4 color_float4 = color_to_float4(line_color->value);
        glLineWidth(lineThickness->value);
        glVertexAttribPointer(line2D_position_location, 2, GL_FLOAT, GL_FALSE, 0, (GLfloat*) &lineData2D->value);
        // glUniform4f(line2D_color_location, color_float4.x, color_float4.y, color_float4.z, color_float4.w);
        zox_gpu_float4(line2D_color_location, color_float4);
        // zox_log("   - [%fx%f] -> [%fx%f]", lineData2D->value.x, lineData2D->value.y, lineData2D->value.z, lineData2D->value.w)
        zox_gpu_render_lines(2);
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" > failed to render line2D_render_iteration [%lu]: [%i]\n", it->entities[i], 2)
            break;
        }
#endif
    }
    glDisableVertexAttribArray(line2D_position_location);
    zox_disable_material();
}

void Line2DRenderSystem(ecs_iter_t *it) {
    line2D_render_iteration(it, 0);
} zox_declare_system(Line2DRenderSystem)

void ElementLine2DRenderSystem(ecs_iter_t *it) {
    line2D_render_iteration(it, 1);
} zox_declare_system(ElementLine2DRenderSystem)
