/*GLuint2 shader3D;
GLuint materialInstance3D;
GLuint2 materialInstance3D_mesh;*/

void catch_basic3D_errors(char* function_name) {
#ifdef is_catch_basic3D_errors
    check_opengl_error(function_name);
#endif
}

void spawn_shaders_basics3D(ecs_world_t *world) {
    spawn_material_basic3D(world);
    spawn_material_colored3D(world);
    spawn_material_textured3D(world);
#ifndef zox_disable_rendering_instances
    spawn_material_vox_instance(world);
#endif
}

/*void dispose_shader3D_instance_material() {
    glDeleteShader(shader3D.x);
    glDeleteShader(shader3D.y);
    glDeleteBuffers(1, &materialInstance3D_mesh.x);
    glDeleteBuffers(1, &materialInstance3D_mesh.y);
    glDeleteProgram(materialInstance3D);
}*/