// debug mode
#define zox_cubeline_debug_none 0
#define zox_cubeline_debug_mesh 1
#define zox_cubeline_debug_render_lod 2
const byte cubeline_debug_mode = zox_cubeline_debug_mesh;
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
    zox_gpu_render_lines(3);
}

void CubeLineRenderSystem(ecs_iter_t *it) {
    zox_enable_material(line3D_material);
    glEnableVertexAttribArray(line3D_position_location);
    zox_gpu_float4(line3D_fog_data_location, get_fog_value());
    glUniformMatrix4fv(line3D_camera_matrix_location, 1, GL_FALSE, (float*) &render_camera_matrix);
    zox_sys_begin()
    zox_sys_in(DebugCubeLines)
    zox_sys_in(CubeLinesThickness)
    zox_sys_in(Color)
    zox_sys_in(Position3D)
    zox_sys_in(Rotation3D)
    zox_sys_in(Bounds3D)
    zox_sys_in(RenderLod)
    zox_sys_in(RenderDisabled)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(DebugCubeLines, debugCubeLines)
        zox_sys_i(RenderLod, renderLod)
        zox_sys_i(CubeLinesThickness, cubeLinesThickness)
        zox_sys_i(Color, colorr)
        zox_sys_i(Position3D, position3D)
        zox_sys_i(Rotation3D, rotation3D)
        zox_sys_i(Bounds3D, bounds3D)
        zox_sys_i(RenderDisabled, renderDisabled)
        if (debugCubeLines->value == 0 || renderLod->value == 255) {
            continue;
        }
        set_line3D_thickness(cubeLinesThickness->value);
        color_rgb lines_color = color_to_color_rgb(colorr->value);
        if (cubeline_debug_mode == zox_cubeline_debug_mesh) {
            // if (meshIndicies->length == 0) lines_color = (color_rgb) { 255, 0, 0 };
            // else lines_color = (color_rgb) { 0, 255, 0 };
            if (renderDisabled->value) lines_color = (color_rgb) { 0, 0, 255 };
        } else if (cubeline_debug_mode == zox_cubeline_debug_render_lod) {
            if (renderLod->value == 255) lines_color = (color_rgb) { 255, 0, 0 };
            else if (renderLod->value == 0) lines_color = (color_rgb) { 0, 255, 255 };
            else if (renderLod->value <= 2) lines_color = (color_rgb) { 0, 255 - renderLod->value * 80, 0 };
            else lines_color = (color_rgb) { 0, 0, 255 };
        }
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
        set_line3D_color(lines_color);
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
#ifdef zoxel_catch_opengl_errors
        if (check_opengl_error_unlogged() != 0) {
            zox_log(" ! CubeLineRenderSystem [%lu]\n", it->entities[i])
            break;
        }
#endif
    }
    glDisableVertexAttribArray(line3D_position_location);
    zox_disable_material();
} zox_declare_system(CubeLineRenderSystem)
