
const char* line3D_source_vert = "\
#version 300 es\n\
in lowp vec3 position;\
uniform lowp mat4 viewMatrix; \
\
void main()\
{\
    gl_Position = viewMatrix * vec4(position, 1);\
}";
const GLchar* line3D_source_frag = "\
#version 300 es\n\
uniform lowp vec4 color;\
out lowp vec4 color_output;\
\
void main()\
{\
    color_output = color;\
}";
GLuint2 line3D_shader;
GLuint line3D_shader_frag;
GLuint line3D_material;
GLuint line3D_position_location;
GLuint line3D_color_location;
GLuint line3D_view_matrix_location;

int initialize_shader_line3D()
{
    line3D_shader = spawn_gpu_shader_inline(line3D_source_vert, line3D_source_frag);
    line3D_material = spawn_gpu_material_program((const GLuint2) { line3D_shader.x, line3D_shader.y });
    line3D_position_location = glGetAttribLocation(line3D_material, "position");
    line3D_color_location = glGetUniformLocation(line3D_material, "color");
    line3D_view_matrix_location = glGetUniformLocation(line3D_material, "viewMatrix");
    return 0;
}

void Line3DRenderSystem(ecs_iter_t *it)
{
    glUseProgram(line3D_material);
    glEnableVertexAttribArray(line3D_position_location);
    const LineData3D *lineData3Ds = ecs_field(it, LineData3D, 2);
    const LineThickness *lineThicknesss = ecs_field(it, LineThickness, 3);
    const Color *colors = ecs_field(it, Color, 4);
    for (int i = 0; i < it->count; i++)
    {
        const LineData3D *lineData3D = &lineData3Ds[i];
        const LineThickness *lineThickness = &lineThicknesss[i];
        const Color *color = &colors[i];
        glLineWidth(lineThickness->value);
        float line_data[] = { lineData3D->value.x, lineData3D->value.y, lineData3D->value.z,
            lineData3D->value.w, lineData3D->value.u, lineData3D->value.v };
        glVertexAttribPointer(line3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, line_data);
        glUniformMatrix4fv(line3D_view_matrix_location, 1, GL_FALSE, (const GLfloat*) ((float*) &main_camera_matrix));
        float4 color_float4 = color_to_float4(color->value);
        glUniform4f(line3D_color_location, color_float4.x, color_float4.y, color_float4.z, color_float4.w);
        glDrawArrays(GL_LINES, 0, 3);
    }
    glUseProgram(0);
}
zoxel_declare_system(Line3DRenderSystem)