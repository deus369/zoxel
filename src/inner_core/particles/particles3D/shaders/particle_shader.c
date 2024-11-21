const char* source_vert_particle3D = "\
#version 300 es\n\
in highp vec3 position;\
in lowp vec4 color;\
uniform highp mat4 camera_matrix;\
uniform highp float thickness;\
out highp float fog_level;\
out lowp vec4 frag_color;\
\
void main() {\
    gl_Position = camera_matrix * vec4(position, 1.0);\
    fog_level = gl_Position.z;\
    highp float distance_to_camera = distance(vec3(0, 0, 0), gl_Position.xyz);\
    gl_PointSize = thickness / distance_to_camera;\
    frag_color = color;\
}";

const GLchar* source_frag_particle3D = "\
#version 300 es\n\
uniform lowp vec4 fog_data;\
in highp float fog_level;\
in lowp vec4 frag_color;\
out lowp vec4 color_output;\
\
void main() {\
    lowp float fog_blend = 1.0 - exp2(-fog_data.w * fog_level * fog_level);\
    color_output = vec4(mix(frag_color.xyz, vec3(fog_data.x, fog_data.y, fog_data.z), fog_blend), frag_color.w);\
}";


// frag_color = vec4(0.6, 0.0, 0.0, 0.6);
// old - uniform lowp vec4 color;

//     color_output = vec4(1.0, 1.0, 1.0, 1.0);

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
GLuint particle3D_instanced_position_buffer;
GLuint particle3D_instanced_color_buffer;

void initialize_particle_gpu_instancing(GLuint particle3D_position_location, GLuint particle3D_color_location, int max_particles) {
#ifdef zox_disable_particles_gpu_instancing
    return;
#endif
    zox_log(" > locations are: %i x %i\n", particle3D_position_location, particle3D_color_location)
    // Setup position buffer
    glGenBuffers(1, &particle3D_instanced_position_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particle3D_instanced_position_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Position3D) * max_particles, NULL, GL_STATIC_DRAW); // NULL for data to be uploaded later
    glVertexAttribPointer(particle3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    // glEnableVertexAttribArray(particle3D_position_location);
    // glVertexAttribPointer(particle3D_position_location, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    // glVertexAttribDivisor(particle3D_position_location, 1); // Update per instance
    // glDisableVertexAttribArray(particle3D_position_location);

    // Setup color buffer
    glGenBuffers(1, &particle3D_instanced_color_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, particle3D_instanced_color_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Color) * max_particles, NULL, GL_STATIC_DRAW); // NULL for data to be uploaded later
    glVertexAttribPointer(particle3D_color_location, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*) 0);
    // glEnableVertexAttribArray(particle3D_color_location);
    // glVertexAttribPointer(particle3D_color_location, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0);
    // glVertexAttribDivisor(particle3D_color_location, 1); // Update per instance
    // glDisableVertexAttribArray(particle3D_color_location);
    // Unbind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void cleanup_particle_gpu_instancing() {
#ifdef zox_disable_particles_gpu_instancing
    return;
#endif
    glDeleteBuffers(1, & particle3D_instanced_position_buffer);
    glDeleteBuffers(1, & particle3D_instanced_color_buffer);
}

int initialize_shader_particle3D() {
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE); // ?
    particle3D_shader = spawn_gpu_shader_inline(source_vert_particle3D, source_frag_particle3D);
    particle3D_material = spawn_gpu_material_program((const GLuint2) { particle3D_shader.x, particle3D_shader.y });
    particle3D_position_location = glGetAttribLocation(particle3D_material, "position");
    particle3D_color_location = glGetAttribLocation(particle3D_material, "color");
    particle3D_camera_matrix_location = glGetUniformLocation(particle3D_material, "camera_matrix");
    particle3D_fog_data_location = glGetUniformLocation(particle3D_material, "fog_data");
    particle3D_location_thickness = glGetUniformLocation(particle3D_material, "thickness");
    initialize_particle_gpu_instancing(particle3D_position_location, particle3D_color_location, zox_max_particles3D);
    return 0;
}

void dispose_shader_particle3D() {
    glDeleteShader(particle3D_shader.x);
    glDeleteShader(particle3D_shader.y);
    glDeleteProgram(particle3D_material);
    cleanup_particle_gpu_instancing();
}
