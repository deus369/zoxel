
const char* line2D_source_vert = "\
#version 300 es\n\
in lowp vec2 position;\
\
void main()\
{\
    gl_Position = vec4(position, 0, 1);\
}";
const GLchar* line2D_source_frag = "\
#version 300 es\n\
out lowp vec4 color;\
\
void main()\
{\
    color = vec4(0, 1, 1, 1);\
}";
GLuint2 line2D_shader;
GLuint line2D_shader_frag;
GLuint line2D_material;

int initialize_shader_line2D()
{
    line2D_shader = spawn_gpu_shader_inline(line2D_source_vert, line2D_source_frag);
    line2D_material = spawn_gpu_material_program((const GLuint2) { line2D_shader.x, line2D_shader.y });
    // printf("line2D_shader: %ix%i\n", line2D_shader.x, line2D_shader.y);
    // printf("line2D_material: %i\n", line2D_material);
    return 0;
}

//! Render 3D entities.
void Line2DRenderSystem(ecs_iter_t *it)
{
    // glViewport(0, 0, 1920, 1080);
    glUseProgram(line2D_material);
    GLuint position_attribute = glGetAttribLocation(line2D_material, "position");
    glEnableVertexAttribArray(position_attribute);
    const LineData2D *lineData2Ds = ecs_field(it, LineData2D, 2);
    const LineThickness *lineThicknesss = ecs_field(it, LineThickness, 3);
    for (int i = 0; i < it->count; i++)
    {
        const LineData2D *lineData2D = &lineData2Ds[i];
        const LineThickness *lineThickness = &lineThicknesss[i];
        glLineWidth(lineThickness->value);
        float line_data[] = { lineData2D->value.x, lineData2D->value.y, lineData2D->value.z, lineData2D->value.w };
        glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, line_data);
        glDrawArrays(GL_LINES, 0, 2);
    }
    glUseProgram(0);
}
ECS_SYSTEM_DECLARE(Line2DRenderSystem);

        // glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, NULL);
        /*glBegin(GL_LINES);
        glVertex2f(lineData2D->value.x, lineData2D->value.y);
        glVertex2f(lineData2D->value.z, lineData2D->value.w);
        glEnd();*/

    /*line2D_shader_vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(line2D_shader_vert, 1, &line2D_source_vert, NULL);
    glCompileShader(line2D_shader_vert);
    GLint success;
    glGetShaderiv(line2D_shader_vert, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE)
    {
        GLint info_log_length;
        glGetShaderiv(line2D_shader_vert, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar* info_log = malloc(info_log_length);
        glGetShaderInfoLog(line2D_shader_vert, info_log_length, NULL, info_log);
        // zoxel_log_arg(stderr, "Failed to compile shader:\n%s\n", info_log);
        zoxel_log_arg("initialize_shader_line2D - Failed to compile shader:\n%s\n", info_log);
        free(info_log);
        return -1;
    }
    printf("line2D_shader_vert: %i\n", line2D_shader_vert);
    // Link the vertex and fragment shaders into a program
    line2D_material = glCreateProgram();
    //glAttachShader(line2D_material, line2D_shader_vert);
    //glLinkProgram(line2D_material);

    glAttachShader(line2D_material, line2D_shader_vert);
    glLinkProgram(line2D_material);
    glGetProgramiv(line2D_material, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        GLint info_log_length;
        glGetProgramiv(line2D_material, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar* info_log = malloc(info_log_length);
        glGetProgramInfoLog(line2D_material, info_log_length, NULL, info_log);
        zoxel_log_arg("Failed to link [%i], line2D_shader_vert:\n%s\n", (int) line2D_material, info_log);
        free(info_log);
        glDetachShader(line2D_material, line2D_shader_vert);
        return false;
    }
    glDetachShader(line2D_material, line2D_shader_vert);*/

    // Bind the vertex data to the shader
    /*float vertexData[] = {
        // 0.0f, 0.0f, 10.0f, 10.0f
        0.0f, 0.0f
    };*/
    //float2 start_position = { -540, -1920 / 2 };
    /*float2 start_position = { 0, 0 };
    //float2 end_position = { 100, 100 };
    float2 end_position = { 540, 1920 / 2 };
    GLuint position_attribute = glGetAttribLocation(line2D_material, "position");
    if (position_attribute != -1)
    {
        float data[] = {
            start_position.x, start_position.y, end_position.x, end_position.y
        };
        glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, data);   // 0, data
        glEnableVertexAttribArray(position_attribute);
    }
    else
    {
        printf("position_attribute error - initialize_shader_line2D: %i\n", position_attribute);
    }*/