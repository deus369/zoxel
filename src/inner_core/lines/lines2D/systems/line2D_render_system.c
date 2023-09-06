const char* line2D_source_vert = "\
#version 300 es\n\
in lowp vec2 position;\
\
void main() {\
    gl_Position = vec4(position, 0, 1);\
}";
const GLchar* line2D_source_frag = "\
#version 300 es\n\
uniform lowp vec4 color;\
out lowp vec4 color_output;\
\
void main() {\
    color_output = color;\
}";
GLuint2 line2D_shader;
GLuint line2D_shader_frag;
GLuint line2D_material;
GLuint line2D_position_location;
GLuint line2D_color_location;

int initialize_shader_line2D() {
    if (is_opengl_running()) {
        line2D_shader = spawn_gpu_shader_inline(line2D_source_vert, line2D_source_frag);
        line2D_material = spawn_gpu_material_program((const GLuint2) { line2D_shader.x, line2D_shader.y });
        line2D_position_location = glGetAttribLocation(line2D_material, "position");
        line2D_color_location = glGetUniformLocation(line2D_material, "color");
    }
    return 0;
}

void Line2DRenderSystem(ecs_iter_t *it) {
    if (renderer_layer != 0) return;
    glUseProgram(line2D_material);
    glEnableVertexAttribArray(line2D_position_location);
    const LineData2D *lineData2Ds = ecs_field(it, LineData2D, 2);
    const LineThickness *lineThicknesss = ecs_field(it, LineThickness, 3);
    const Color *colorRGBs = ecs_field(it, Color, 4);
    for (int i = 0; i < it->count; i++) {
        const LineData2D *lineData2D = &lineData2Ds[i];
        const LineThickness *lineThickness = &lineThicknesss[i];
        const Color *color = &colorRGBs[i];
        float line_data[] = { lineData2D->value.x, lineData2D->value.y, lineData2D->value.z, lineData2D->value.w };
        float4 color_float4 = color_to_float4(color->value);
        glLineWidth(lineThickness->value);
        glVertexAttribPointer(line2D_position_location, 2, GL_FLOAT, GL_FALSE, 0, line_data);
        glUniform4f(line2D_color_location, color_float4.x, color_float4.y, color_float4.z, color_float4.w);
        glDrawArrays(GL_LINES, 0, 2);
    }
    // glUseProgram(0);
}
zox_declare_system(Line2DRenderSystem)