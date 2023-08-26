const char* line3D_source_vert = "\
#version 300 es\n\
in highp vec3 position;\
uniform highp mat4 camera_matrix;\
out highp float fog_level;\
\
void main() {\
    gl_Position = camera_matrix * vec4(position, 1);\
    fog_level = gl_Position.z;\
}";

const GLchar* line3D_source_frag = "\
#version 300 es\n\
in highp float fog_level;\
uniform lowp vec3 color;\
uniform lowp vec4 fog_data;\
out lowp vec3 color2;\
\
void main() {\
    color2 = color;\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);\
    color2 = mix(color2, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";

GLuint2 line3D_shader;
GLuint line3D_material;
GLuint line3D_position_location;
GLuint line3D_color_location;
GLuint line3D_camera_matrix_location;
GLuint line3D_fog_data_location;

// todo: call dispose_line3D_shader / move it to a shader entity
void dispose_shader_line3D() {
    glDeleteShader(line3D_shader.x);
    glDeleteShader(line3D_shader.y);
    glDeleteProgram(line3D_material);
}

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