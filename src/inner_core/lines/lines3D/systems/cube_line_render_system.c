const float cube_lines_length = 1.0f;

void set_line3D_color(color_rgb color_rgb2) {
    float3 color_rgb_f3 = color_rgb_to_float3(color_rgb2);
    glUniform3f(line3D_color_location, color_rgb_f3.x, color_rgb_f3.y, color_rgb_f3.z);
}

void set_line3D_thickness(float thickness) {
        glLineWidth(thickness);
}

void render_line3D(float3 position_a, float3 position_b) {
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
    const DebugCubeLines *debugCubeLiness = ecs_field(it, DebugCubeLines, 2);
    const CubeLinesThickness *cubeLinesThicknesss = ecs_field(it, CubeLinesThickness, 3);
    const ColorRGB *colorRGBs = ecs_field(it, ColorRGB, 4);
    const Position3D *position3Ds = ecs_field(it, Position3D, 5);
    const Rotation3D *rotation3Ds = ecs_field(it, Rotation3D, 6);
    const Bounds3D *bounds3Ds = ecs_field(it, Bounds3D, 7);
    const RenderLod *renderLods = ecs_field(it, RenderLod, 8);
    for (int i = 0; i < it->count; i++) {
        const DebugCubeLines *debugCubeLines = &debugCubeLiness[i];
        if (debugCubeLines->value == 0) continue;
        const RenderLod *renderLod = &renderLods[i];
        if (renderLod->value == 255) continue;
        const CubeLinesThickness *cubeLinesThickness = &cubeLinesThicknesss[i];
        const ColorRGB *colorRGB = &colorRGBs[i];
        const Position3D *position3D = &position3Ds[i];
        const Rotation3D *rotation3D = &rotation3Ds[i];
        const Bounds3D *bounds3D = &bounds3Ds[i];
        set_line3D_thickness(cubeLinesThickness->value);
        #ifdef zoxel_debug_transforms
            // up axis
            set_line3D_color(colorRGB->value);
            // render_line3D(position3D->value, (float3) { position3D->value.x, position3D->value.y + cube_lines_length, position3D->value.z });
            float3 up_vector = (float3) { 0, cube_lines_length, 0 };
            float4_rotate_float3_p(rotation3D->value, &up_vector);
            float3_add_float3_p(&up_vector, position3D->value);
            render_line3D(position3D->value, up_vector);
            // forward axis
            set_line3D_color((color_rgb) { colorRGB->value.b, colorRGB->value.g, colorRGB->value.r });
            float3 forward_vector = (float3) { 0, 0, cube_lines_length };
            float4_rotate_float3_p(rotation3D->value, &forward_vector);
            float3_add_float3_p(&forward_vector, position3D->value);
            render_line3D(position3D->value, forward_vector);
            // right axis
            set_line3D_color((color_rgb) { colorRGB->value.g, colorRGB->value.r, colorRGB->value.b });
            float3 right_vector = (float3) { cube_lines_length, 0, 0 };
            float4_rotate_float3_p(rotation3D->value, &right_vector);
            float3_add_float3_p(&right_vector, position3D->value);
            render_line3D(position3D->value, right_vector);
        #else
            color_rgb cube_color = colorRGB->value;
            cube_color.r += 30 * renderLod->value;
            cube_color.g -= 20 * renderLod->value;
            cube_color.b -= 20 * renderLod->value;
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
            render_line3D(top_left, top_right);
            render_line3D(top_left2, top_right2);
            render_line3D(top_left, top_left2);
            render_line3D(top_right, top_right2);
            // bottom
            render_line3D(bottom_left, bottom_right);
            render_line3D(bottom_left2, bottom_right2);
            render_line3D(bottom_left, bottom_left2);
            render_line3D(bottom_right, bottom_right2);
            // vertical
            render_line3D(bottom_right, top_right);
            render_line3D(bottom_left, top_left);
            render_line3D(bottom_right2, top_right2);
            render_line3D(bottom_left2, top_left2);
        #endif

        // up | down for collision
        /*set_line3D_color(colorRGB->value);
        render_line3D(position3D->value, (float3) { position3D->value.x, position3D->value.y - bounds3D->value.y, position3D->value.z });
        set_line3D_color((color_rgb) { colorRGB->value.g, colorRGB->value.r, colorRGB->value.b });
        render_line3D(position3D->value, (float3) { position3D->value.x, position3D->value.y + bounds3D->value.y, position3D->value.z });*/
        // zoxel_log(" + cls [%i] - [%lu] position3D [%fx%fx%f]\n", i, it->entities[i], position3D->value.x, position3D->value.y, position3D->value.z);
    }
    glDisableVertexAttribArray(line3D_position_location);
    glUseProgram(0);
} zox_declare_system(CubeLineRenderSystem)

// up and forward line for now
// float line_data[] = { position3D->value.x, position3D->value.y, position3D->value.z,
//    position3D->value.x, position3D->value.y + 6.0f, position3D->value.z };
// glVertexAttribPointer(line3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, line_data);
//float3 color_rgb_f3 = color_rgb_to_float3(colorRGB->value);
//glUniform3f(line3D_color_location, color_rgb_f3.x, color_rgb_f3.y, color_rgb_f3.z);
// glDrawArrays(GL_LINES, 0, 3);
