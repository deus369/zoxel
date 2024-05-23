const char* line3D_source_vert = "\
#version 300 es\n\
in highp vec3 position;\
uniform highp mat4 camera_matrix;\
out highp float fog_level;\
\
void main() {\
    gl_Position = camera_matrix * vec4(position, 1);\
    fog_level = gl_Position.z * gl_Position.z;\
}";

const GLchar* line3D_source_frag = "\
#version 300 es\n\
in highp float fog_level;\
uniform lowp vec3 color;\
uniform lowp vec4 fog_data;\
out lowp vec4 frag_color;\
\
void main() {\
    frag_color = vec4(color, 0.2);\
    lowp float fog_blend = min(1.0, 1.1 - exp2(-fog_data.w * fog_level));\
    frag_color = mix(frag_color, vec4(fog_data.x, fog_data.y, fog_data.z, 0), fog_blend);\
}";

// uses custom fadeout with fog!
GLuint2 line3D_shader;
GLuint line3D_material;
GLuint line3D_position_location;
GLuint line3D_color_location;
GLuint line3D_camera_matrix_location;
GLuint line3D_fog_data_location;

void dispose_shader_line3D() {
    glDeleteShader(line3D_shader.x);
    glDeleteShader(line3D_shader.y);
    glDeleteProgram(line3D_material);
}

int initialize_shader_line3D() {
    line3D_shader = spawn_gpu_shader_inline(line3D_source_vert, line3D_source_frag);
    line3D_material = spawn_gpu_material_program((const GLuint2) { line3D_shader.x, line3D_shader.y });
    line3D_position_location = glGetAttribLocation(line3D_material, "position");
    line3D_color_location = glGetUniformLocation(line3D_material, "color");
    line3D_camera_matrix_location = glGetUniformLocation(line3D_material, "camera_matrix");
    line3D_fog_data_location = glGetUniformLocation(line3D_material, "fog_data");
    return 0;
}
