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

uint2 particle3D_shader;
uint particle3D_material;
uint particle3D_position_location;
uint particle3D_color_location;
uint particle3D_camera_matrix_location;
uint particle3D_fog_data_location;
uint particle3D_location_thickness;
uint particle3D_instanced_position_buffer;
uint particle3D_instanced_color_buffer;

void initialize_particle_gpu_instancing(uint particle3D_position_location, uint particle3D_color_location, int max_particles) {
#ifdef zox_disable_particles_gpu_instancing
    return;
#endif
    // zox_log(" > locations are: %i x %i\n", particle3D_position_location, particle3D_color_location)
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

int initialize_shader_particle3D(ecs_world_t *world) {
    char* vert = get_shader_source(world, "particle3D.vert");
    char* frag = get_shader_source(world, "particle3D.frag");
    particle3D_shader = spawn_gpu_shader_inline(vert, frag);
    particle3D_material = spawn_gpu_material_program((const uint2) { particle3D_shader.x, particle3D_shader.y });
    if (!particle3D_material) {
        zox_log_error("shader particle3D failed to initialize")
        return EXIT_FAILURE;
    }
    particle3D_position_location = glGetAttribLocation(particle3D_material, "position");
    particle3D_color_location = glGetAttribLocation(particle3D_material, "color");
    particle3D_camera_matrix_location = glGetUniformLocation(particle3D_material, "camera_matrix");
    particle3D_fog_data_location = glGetUniformLocation(particle3D_material, "fog_data");
    particle3D_location_thickness = glGetUniformLocation(particle3D_material, "thickness");
    initialize_particle_gpu_instancing(particle3D_position_location, particle3D_color_location, zox_max_particles3D);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    return EXIT_SUCCESS;
}

void dispose_shader_particle3D() {
    glDeleteShader(particle3D_shader.x);
    glDeleteShader(particle3D_shader.y);
    glDeleteProgram(particle3D_material);
    cleanup_particle_gpu_instancing();
}
