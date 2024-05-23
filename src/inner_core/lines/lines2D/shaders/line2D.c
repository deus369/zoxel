const char* line2D_source_vert = "\
#version 300 es\n\
in highp vec2 position;\
uniform lowp float depth;\
uniform highp mat4 camera_matrix;\
\
void main() {\
    gl_Position = camera_matrix * vec4(position, 0, 1);\
    gl_Position.z = depth;\
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
GLuint line2D_camera_matrix_location;

int initialize_shader_line2D() {
    line2D_shader = spawn_gpu_shader_inline(line2D_source_vert, line2D_source_frag);
    line2D_material = spawn_gpu_material_program((const GLuint2) { line2D_shader.x, line2D_shader.y });
    line2D_position_location = glGetAttribLocation(line2D_material, "position");
    line2D_color_location = glGetUniformLocation(line2D_material, "color");
    line2D_depth_location = glGetUniformLocation(line2D_material, "depth");
    line2D_camera_matrix_location = glGetUniformLocation(line2D_material, "camera_matrix");
    return 0;
}
