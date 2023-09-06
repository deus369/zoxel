// todo: create a event data structure that higher level modules can just add functions too
extern int load_shader_skybox();
extern void dispose_shader_skybox();
extern int load_shader_skybox();
extern void dispose_shader_skybox();
extern void rendering_dispose_basic_shaders3D();
extern void rendering_load_basic_shaders3D(ecs_world_t *world);
extern void rendering_restore_basic_shaders3D(ecs_world_t *world);

void opengl_dispose_shaders() {
    dispose_shader2D_instance_material();
    dispose_shader2D_textured();
    dispose_shader_skybox();
    rendering_dispose_basic_shaders3D();
}

int opengl_load_shaders(ecs_world_t *world) {
    rendering_load_basic_shaders3D(world);
    // if (load_shader3D_textured(world)) zoxel_log("    ! error loading [load_shader3D_textured]\n");
    if (load_instance2D_material() != 0) zoxel_log("    ! error loading [instance2D_material]\n");
    if (load_shader2D_textured() != 0) zoxel_log("    ! error loading [shader2D_textured]\n");
    if (load_shader_skybox()) zoxel_log("    ! error loading [load_shader_skybox]\n");
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_load_shaders");
    #endif
    return 0;
}

// for now until i move the rest to use ecs
int opengl_restore_shaders() {
    rendering_restore_basic_shaders3D(world);
    if (load_instance2D_material() != 0) zoxel_log("    ! error loading [instance2D_material]\n");
    if (load_shader2D_textured() != 0) zoxel_log("    ! error loading [shader2D_textured]\n");
    if (load_shader_skybox()) zoxel_log("    ! error loading [load_shader_skybox]\n");
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_load_shaders");
    #endif
    return 0;
}