GLuint2 line3D_shader;
GLuint line3D_shader_frag;
GLuint line3D_material;
GLuint line3D_position_location;
GLuint line3D_color_location;
GLuint line3D_camera_matrix_location;
GLuint line3D_fog_data_location;

int initialize_shader_line3D() {
    if (is_opengl_running()) {
        line3D_shader = spawn_gpu_shader_inline(line3D_source_vert, line3D_source_frag);
        line3D_material = spawn_gpu_material_program((const GLuint2) { line3D_shader.x, line3D_shader.y });
        line3D_position_location = glGetAttribLocation(line3D_material, "position");
        line3D_color_location = glGetUniformLocation(line3D_material, "color");
        line3D_camera_matrix_location = glGetUniformLocation(line3D_material, "camera_matrix");
        line3D_fog_data_location = glGetUniformLocation(line3D_material, "fog_data");
    }
    return 0;
}

void Line3DRenderSystem(ecs_iter_t *it) {
    glUseProgram(line3D_material);
    glEnableVertexAttribArray(line3D_position_location);
    glUniform4f(line3D_fog_data_location, fog_color.x, fog_color.y, fog_color.z, fog_density);
    glUniformMatrix4fv(line3D_camera_matrix_location, 1, GL_FALSE, (float*) &main_camera_matrix);
    const LineData3D *lineData3Ds = ecs_field(it, LineData3D, 2);
    const LineThickness *lineThicknesss = ecs_field(it, LineThickness, 3);
    const ColorRGB *colorRGBs = ecs_field(it, ColorRGB, 4);
    for (int i = 0; i < it->count; i++) {
        const LineData3D *lineData3D = &lineData3Ds[i];
        const LineThickness *lineThickness = &lineThicknesss[i];
        const ColorRGB *colorRGB = &colorRGBs[i];
        float line_data[] = { lineData3D->value.x, lineData3D->value.y, lineData3D->value.z,
            lineData3D->value.w, lineData3D->value.u, lineData3D->value.v };
        glLineWidth(lineThickness->value);
        glVertexAttribPointer(line3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, line_data);
        float3 color_rgb_f3 = color_rgb_to_float3(colorRGB->value);
        glUniform3f(line3D_color_location, color_rgb_f3.x, color_rgb_f3.y, color_rgb_f3.z);
        glDrawArrays(GL_LINES, 0, 3);
    }
    glDisableVertexAttribArray(line3D_position_location);
    glUseProgram(0);
}
zoxel_declare_system(Line3DRenderSystem)