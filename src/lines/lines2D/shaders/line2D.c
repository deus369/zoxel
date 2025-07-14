GLuint2 line2D_shader;
GLuint line2D_shader_frag;
GLuint line2D_material;
GLuint line2D_position_location;
GLuint line2D_color_location;
GLuint line2D_depth_location;
GLuint line2D_camera_matrix_location;

int initialize_shader_line2D(ecs_world_t *world) {
    char* vert = get_shader_source(world, "line2D.vert");
    char* frag = get_shader_source(world, "line2D.frag");
    line2D_shader = spawn_gpu_shader_inline(vert, frag);
    line2D_material = spawn_gpu_material_program((const GLuint2) { line2D_shader.x, line2D_shader.y });
    if (!line2D_material) {
        zox_log_error("line2D_material failed to initialize")
        return EXIT_FAILURE;
    }
    line2D_position_location = glGetAttribLocation(line2D_material, "position");
    line2D_color_location = glGetUniformLocation(line2D_material, "color");
    line2D_depth_location = glGetUniformLocation(line2D_material, "depth");
    line2D_camera_matrix_location = glGetUniformLocation(line2D_material, "camera_matrix");
    return EXIT_SUCCESS;
}