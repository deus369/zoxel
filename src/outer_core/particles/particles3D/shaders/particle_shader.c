const char* source_vert_particle3D = "\
#version 300 es\n\
uniform highp mat4 camera_matrix;\
in highp vec3 position;\
out highp float fog_level;\
\
void main() {\
    gl_Position = camera_matrix * vec4(position, 1);\
    fog_level = gl_Position.z;\
}";

const GLchar* source_frag_particle3D = "\
#version 300 es\n\
uniform lowp vec3 color;\
uniform lowp vec4 fog_data;\
in highp float fog_level;\
out lowp vec3 color2;\
\
void main() {\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_data.w * fog_level * fog_level);\
    color2 = color;\
    color2 = mix(color2, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend);\
}";

GLuint2 particle3D_shader;
GLuint particle3D_material;
GLuint particle3D_position_location;
GLuint particle3D_color_location;
GLuint particle3D_camera_matrix_location;
GLuint particle3D_fog_data_location;

int initialize_shader_particle3D() {
    if (is_opengl_running()) {
        particle3D_shader = spawn_gpu_shader_inline(source_vert_particle3D, source_frag_particle3D);
        particle3D_material = spawn_gpu_material_program((const GLuint2) { particle3D_shader.x, particle3D_shader.y });
        particle3D_position_location = glGetAttribLocation(particle3D_material, "position");
        particle3D_color_location = glGetUniformLocation(particle3D_material, "color");
        particle3D_camera_matrix_location = glGetUniformLocation(particle3D_material, "camera_matrix");
        particle3D_fog_data_location = glGetUniformLocation(particle3D_material, "fog_data");
    }
    return 0;
}

void dispose_shader_particle3D() {
    glDeleteShader(particle3D_shader.x);
    glDeleteShader(particle3D_shader.y);
    glDeleteProgram(particle3D_material);
}