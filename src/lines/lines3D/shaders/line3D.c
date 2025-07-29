// uses custom fadeout with fog!
uint2 line3D_shader;
uint line3D_material;
uint line3D_position_location;
uint line3D_color_location;
uint line3D_camera_matrix_location;
uint line3D_fog_data_location;

void dispose_shader_line3D() {
    glDeleteShader(line3D_shader.x);
    glDeleteShader(line3D_shader.y);
    glDeleteProgram(line3D_material);
}

int initialize_shader_line3D(ecs_world_t *world) {
    char* vert = get_shader_source(world, "line3D.vert");
    char* frag = get_shader_source(world, "line3D.frag");
    line3D_shader = zox_gpu_compile_shader(vert, frag);
    if (uint2_equals(line3D_shader, uint2_zero)) {
        zox_log_error("line3D_shader has failed")
        return EXIT_FAILURE;
    }
    line3D_material = spawn_gpu_material_program((const uint2) { line3D_shader.x, line3D_shader.y });
    if (!line3D_material) {
        zox_log_error("line3D_material failed to initialize")
        return EXIT_FAILURE;
    }
    line3D_position_location = glGetAttribLocation(line3D_material, "position");
    line3D_color_location = glGetUniformLocation(line3D_material, "color");
    line3D_camera_matrix_location = glGetUniformLocation(line3D_material, "camera_matrix");
    line3D_fog_data_location = glGetUniformLocation(line3D_material, "fog_data");
    return EXIT_SUCCESS;
}