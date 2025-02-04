extern ecs_entity_t get_root_canvas_camera(ecs_world_t *world, const ecs_entity_t e);

void line2D_render_iteration(ecs_iter_t *it, const unsigned char is_element_line) {
    glUseProgram(line2D_material);
    glEnableVertexAttribArray(line2D_position_location);
    if (is_element_line) {
        const float4x4 identity = float4x4_identity();
        glUniformMatrix4fv(line2D_camera_matrix_location, 1, GL_FALSE, (GLfloat*) &identity);
        glUniform1f(line2D_depth_location, ((int) renderer_layer) * shader_depth_multiplier);
    } else {
        glUniformMatrix4fv(line2D_camera_matrix_location, 1, GL_FALSE, (GLfloat*) &render_camera_matrix);
        glUniform1f(line2D_depth_location, ((int) 0) * shader_depth_multiplier);
    }
    zox_field_in(LineData2D, lineData2Ds, 1)
    zox_field_in(LineThickness, lineThicknesss, 2)
    zox_field_in(Color, colors, 3)
    zox_field_in(Layer2D, layer2Ds, 4)
    for (int i = 0; i < it->count; i++) {
        if (is_element_line) {
            zox_field_i(Layer2D, layer2Ds, layer2D)
            if (layer2D->value != renderer_layer) continue; // render per layer
            zox_field_e()
            if (get_root_canvas_camera(world, e) != renderer_camera) continue;
        }
        zox_field_i(LineData2D, lineData2Ds, lineData2D)
        zox_field_i(LineThickness, lineThicknesss, lineThickness)
        zox_field_i(Color, colors, line_color)
        const float4 color_float4 = color_to_float4(line_color->value);
        glLineWidth(lineThickness->value);
        glVertexAttribPointer(line2D_position_location, 2, GL_FLOAT, GL_FALSE, 0, (GLfloat*) &lineData2D->value);
        glUniform4f(line2D_color_location, color_float4.x, color_float4.y, color_float4.z, color_float4.w);
        glDrawArrays(GL_LINES, 0, 2);
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" > failed to render line2D_render_iteration [%lu]: [%i]\n", it->entities[i], 2)
            break;
        }
#endif
    }
    glDisableVertexAttribArray(line2D_position_location);
    glUseProgram(0);
}

void Line2DRenderSystem(ecs_iter_t *it) {
    line2D_render_iteration(it, 0);
} zox_declare_system(Line2DRenderSystem)

void ElementLine2DRenderSystem(ecs_iter_t *it) {
    line2D_render_iteration(it, 1);
} zox_declare_system(ElementLine2DRenderSystem)
