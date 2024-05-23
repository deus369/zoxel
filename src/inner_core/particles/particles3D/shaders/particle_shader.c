const char* source_vert_particle3D = "\
#version 300 es\n\
uniform highp mat4 camera_matrix;\
uniform highp float thickness;\
in highp vec3 position;\
out highp float fog_level;\
\
void main() {\
    gl_Position = camera_matrix * vec4(position, 1);\
    fog_level = gl_Position.z;\
    highp float distance_to_camera = distance(vec3(0, 0, 0), gl_Position.xyz);\
    gl_PointSize = thickness / distance_to_camera;\
}";

const GLchar* source_frag_particle3D = "\
#version 300 es\n\
uniform lowp vec4 color;\
uniform lowp vec4 fog_data;\
in highp float fog_level;\
out lowp vec4 color_output;\
\
void main() {\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_level * fog_level);\
    color_output = vec4(mix(color.xyz, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend), color.w);\
}";

// maybe color.w -= fog_blend, but limit to 0, so it fades out
/*
    highp float point_size = 100.0;\
    highp vec3 camera_position = vec3(camera_matrix[3][0], camera_matrix[3][1], camera_matrix[3][2]);\
    highp float distance_to_camera = distance(camera_position, position);\
    gl_PointSize = point_size - distance_to_camera / point_size;\
    gl_PointSize = point_size * (1.0 / distance_to_camera);\
*/

GLuint2 particle3D_shader;
GLuint particle3D_material;
GLuint particle3D_position_location;
GLuint particle3D_color_location;
GLuint particle3D_camera_matrix_location;
GLuint particle3D_fog_data_location;
GLuint particle3D_location_thickness;

int initialize_shader_particle3D() {
    particle3D_shader = spawn_gpu_shader_inline(source_vert_particle3D, source_frag_particle3D);
    particle3D_material = spawn_gpu_material_program((const GLuint2) { particle3D_shader.x, particle3D_shader.y });
    particle3D_position_location = glGetAttribLocation(particle3D_material, "position");
    particle3D_color_location = glGetUniformLocation(particle3D_material, "color");
    particle3D_camera_matrix_location = glGetUniformLocation(particle3D_material, "camera_matrix");
    particle3D_fog_data_location = glGetUniformLocation(particle3D_material, "fog_data");
    particle3D_location_thickness = glGetUniformLocation(particle3D_material, "thickness");
    return 0;
}

void dispose_shader_particle3D() {
    glDeleteShader(particle3D_shader.x);
    glDeleteShader(particle3D_shader.y);
    glDeleteProgram(particle3D_material);
}
