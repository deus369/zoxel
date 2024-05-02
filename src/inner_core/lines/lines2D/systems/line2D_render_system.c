const char* line2D_source_vert = "\
#version 300 es\n\
uniform lowp float depth;\
in lowp vec2 position;\
\
void main() {\
    gl_Position = vec4(position, depth, 1);\
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
GLuint line2D_depth_location;

int initialize_shader_line2D() {
    if (is_opengl_running()) {
        line2D_shader = spawn_gpu_shader_inline(line2D_source_vert, line2D_source_frag);
        line2D_material = spawn_gpu_material_program((const GLuint2) { line2D_shader.x, line2D_shader.y });
        line2D_position_location = glGetAttribLocation(line2D_material, "position");
        line2D_color_location = glGetUniformLocation(line2D_material, "color");
        line2D_depth_location = glGetUniformLocation(line2D_material, "depth");
    }
    return 0;
}

extern ecs_entity_t get_root_canvas_camera(ecs_world_t *world, const ecs_entity_t e);

void Line2DRenderSystem(ecs_iter_t *it) {
    glUseProgram(line2D_material);
    glEnableVertexAttribArray(line2D_position_location);
    zox_field_in(LineData2D, lineData2Ds, 1)
    zox_field_in(LineThickness, lineThicknesss, 2)
    zox_field_in(Color, colorRGBs, 3)
    zox_field_in(Layer2D, layer2Ds, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_in(Layer2D, layer2Ds, layer2D)
        if (layer2D->value != renderer_layer) continue; // render per layer
        zox_field_e()
        if (get_root_canvas_camera(world, e) != renderer_camera) continue;
        zox_field_i_in(LineData2D, lineData2Ds, lineData2D)
        zox_field_i_in(LineThickness, lineThicknesss, lineThickness)
        zox_field_i_in(Color, colorRGBs, colorRGB)
        const float line_data[] = { lineData2D->value.x, lineData2D->value.y, lineData2D->value.z, lineData2D->value.w };
        const float4 color_float4 = color_to_float4(colorRGB->value);
        const float position_z = ((int) layer2D->value) * shader_depth_multiplier;
        glLineWidth(lineThickness->value);
        glUniform1f(line2D_depth_location, position_z);
        glVertexAttribPointer(line2D_position_location, 2, GL_FLOAT, GL_FALSE, 0, line_data);
        glUniform4f(line2D_color_location, color_float4.x, color_float4.y, color_float4.z, color_float4.w);
        glDrawArrays(GL_LINES, 0, 2); // 2
    }
    glUseProgram(0);
} zox_declare_system(Line2DRenderSystem)
