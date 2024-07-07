const float cube_lines_length = 1.0f;

void set_line3D_color(color_rgb color_rgb2) {
    float3 color_rgb_f3 = color_rgb_to_float3(color_rgb2);
    glUniform3f(line3D_color_location, color_rgb_f3.x, color_rgb_f3.y, color_rgb_f3.z);
}

void set_line3D_thickness(float thickness) {
        glLineWidth(thickness);
}

void render_cube_line3D(float3 position_a, float3 position_b) {
    // glLineWidth(cubeLinesThickness->value);
    glVertexAttribPointer(line3D_position_location, 3, GL_FLOAT, GL_FALSE, 0,
        (float[]) { position_a.x, position_a.y, position_a.z, position_b.x, position_b.y, position_b.z });
    glDrawArrays(GL_LINES, 0, 3);
}

void CubeLineRenderSystem(ecs_iter_t *it) {
    glUseProgram(line3D_material);
    glEnableVertexAttribArray(line3D_position_location);
    opengl_set_float4(line3D_fog_data_location, (float4) { fog_color.x, fog_color.y, fog_color.z, get_fog_density() });
    glUniformMatrix4fv(line3D_camera_matrix_location, 1, GL_FALSE, (float*) &render_camera_matrix);
    zox_field_in(DebugCubeLines, debugCubeLiness, 2)
    zox_field_in(CubeLinesThickness, cubeLinesThicknesss, 3)
    zox_field_in(ColorRGB, colorRGBs, 4)
    zox_field_in(Position3D, position3Ds, 5)
    zox_field_in(Rotation3D, rotation3Ds, 6)
    zox_field_in(Bounds3D, bounds3Ds, 7)
    zox_field_in(RenderLod, renderLods, 8)
    zox_field_in(MeshIndicies, meshIndiciess, 9)
    zox_field_in(RenderDisabled, renderDisableds, 10)
    for (int i = 0; i < it->count; i++) {
        zox_field_i(DebugCubeLines, debugCubeLiness, debugCubeLines)
        if (debugCubeLines->value == 0) continue;
        zox_field_i(RenderLod, renderLods, renderLod)
        if (renderLod->value == 255) continue;
        zox_field_i(CubeLinesThickness, cubeLinesThicknesss, cubeLinesThickness)
        zox_field_i(ColorRGB, colorRGBs, colorRGB)
        zox_field_i(Position3D, position3Ds, position3D)
        zox_field_i(Rotation3D, rotation3Ds, rotation3D)
        zox_field_i(Bounds3D, bounds3Ds, bounds3D)
        zox_field_i(MeshIndicies, meshIndiciess, meshIndicies)
        zox_field_i(RenderDisabled, renderDisableds, renderDisabled)
        set_line3D_thickness(cubeLinesThickness->value);
        color_rgb lines_color = colorRGB->value;
        if (meshIndicies->length == 0) lines_color = (color_rgb) { 255, 0, 0 };
        else if (renderDisabled->value) lines_color = (color_rgb) { 0, 255, 0 };
        else lines_color = (color_rgb) { 0, 0, 255 };
        // lines_color = (color_rgb) { renderLod->value * 32, 0, 0 }; // debug render lod
#ifdef zoxel_debug_transforms
        // up axis
        // render_cube_line3D(position3D->value, (float3) { position3D->value.x, position3D->value.y + cube_lines_length, position3D->value.z });
        set_line3D_color(lines_color);
        float3 up_vector = (float3) { 0, cube_lines_length, 0 };
        float4_rotate_float3_p(rotation3D->value, &up_vector);
        float3_add_float3_p(&up_vector, position3D->value);
        render_cube_line3D(position3D->value, up_vector);
        // forward axis
        set_line3D_color(lines_color);
        float3 forward_vector = (float3) { 0, 0, cube_lines_length };
        float4_rotate_float3_p(rotation3D->value, &forward_vector);
        float3_add_float3_p(&forward_vector, position3D->value);
        render_cube_line3D(position3D->value, forward_vector);
        // right axis
        set_line3D_color(lines_color);
        float3 right_vector = (float3) { cube_lines_length, 0, 0 };
        float4_rotate_float3_p(rotation3D->value, &right_vector);
        float3_add_float3_p(&right_vector, position3D->value);
        render_cube_line3D(position3D->value, right_vector);
#else
        // this is normal case
        color_rgb cube_color = lines_color;
        /*cube_color.r += 30 * renderLod->value;
        cube_color.g -= 20 * renderLod->value;
        cube_color.b -= 20 * renderLod->value;*/
        set_line3D_color(cube_color);
        // get corners of cube
        float3 top_right = (float3) { bounds3D->value.x, bounds3D->value.y, bounds3D->value.z };
        float3 top_left = (float3) { - bounds3D->value.x, bounds3D->value.y, bounds3D->value.z };
        float3 top_right2 = (float3) { bounds3D->value.x, bounds3D->value.y, - bounds3D->value.z };
        float3 top_left2 = (float3) { - bounds3D->value.x, bounds3D->value.y, - bounds3D->value.z };
        float3 bottom_right = (float3) { bounds3D->value.x, - bounds3D->value.y, bounds3D->value.z };
        float3 bottom_left = (float3) { - bounds3D->value.x, - bounds3D->value.y, bounds3D->value.z };
        float3 bottom_right2 = (float3) { bounds3D->value.x, - bounds3D->value.y, - bounds3D->value.z };
        float3 bottom_left2 = (float3) { - bounds3D->value.x, - bounds3D->value.y, - bounds3D->value.z };
        float4_rotate_float3_p(rotation3D->value, &top_right);
        float4_rotate_float3_p(rotation3D->value, &top_left);
        float4_rotate_float3_p(rotation3D->value, &top_right2);
        float4_rotate_float3_p(rotation3D->value, &top_left2);
        float4_rotate_float3_p(rotation3D->value, &bottom_right);
        float4_rotate_float3_p(rotation3D->value, &bottom_left);
        float4_rotate_float3_p(rotation3D->value, &bottom_right2);
        float4_rotate_float3_p(rotation3D->value, &bottom_left2);
        float3_add_float3_p(&top_right, position3D->value);
        float3_add_float3_p(&top_left, position3D->value);
        float3_add_float3_p(&top_right2, position3D->value);
        float3_add_float3_p(&top_left2, position3D->value);
        float3_add_float3_p(&bottom_right, position3D->value);
        float3_add_float3_p(&bottom_left, position3D->value);
        float3_add_float3_p(&bottom_right2, position3D->value);
        float3_add_float3_p(&bottom_left2, position3D->value);
        // top
        render_cube_line3D(top_left, top_right);
        render_cube_line3D(top_left2, top_right2);
        render_cube_line3D(top_left, top_left2);
        render_cube_line3D(top_right, top_right2);
        // bottom
        render_cube_line3D(bottom_left, bottom_right);
        render_cube_line3D(bottom_left2, bottom_right2);
        render_cube_line3D(bottom_left, bottom_left2);
        render_cube_line3D(bottom_right, bottom_right2);
        // vertical
        render_cube_line3D(bottom_right, top_right);
        render_cube_line3D(bottom_left, top_left);
        render_cube_line3D(bottom_right2, top_right2);
        render_cube_line3D(bottom_left2, top_left2);
#endif

        // up | down for collision
        /*set_line3D_color(colorRGB->value);
        render_cube_line3D(position3D->value, (float3) { position3D->value.x, position3D->value.y - bounds3D->value.y, position3D->value.z });
        set_line3D_color((color_rgb) { colorRGB->value.g, colorRGB->value.r, colorRGB->value.b });
        render_cube_line3D(position3D->value, (float3) { position3D->value.x, position3D->value.y + bounds3D->value.y, position3D->value.z });*/
        // zoxel_log(" + cls [%i] - [%lu] position3D [%fx%fx%f]\n", i, it->entities[i], position3D->value.x, position3D->value.y, position3D->value.z);
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" ! CubeLineRenderSystem [%lu]\n", it->entities[i])
            break;
        }
#endif
    }
    glDisableVertexAttribArray(line3D_position_location);
    glUseProgram(0);
} zox_declare_system(CubeLineRenderSystem)
