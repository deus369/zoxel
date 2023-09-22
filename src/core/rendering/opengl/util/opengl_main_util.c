// todo: create a event data structure that higher level modules can just add functions too
extern void rendering_dispose_basic_shaders3D();
extern void rendering_restore_basic_shaders3D(ecs_world_t *world);
extern void load_shaders_dynamic(ecs_world_t *world);

void opengl_dispose_shaders() {
    dispose_shader2D_instance_material();
    dispose_shader2D_textured();
    rendering_dispose_basic_shaders3D();
}

int opengl_load_shaders(ecs_world_t *world) {
    load_shaders_dynamic(world);
    if (load_instance2D_material() != 0) zoxel_log("    ! error loading [instance2D_material]\n");
    if (load_shader2D_textured() != 0) zoxel_log("    ! error loading [shader2D_textured]\n");
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_load_shaders");
    #endif
    return 0;
}

// for now until i move the rest to use ecs
int rendering_restore_basic_shaders2D(ecs_world_t *world) {
    if (load_instance2D_material() != 0) zoxel_log("    ! error loading [instance2D_material]\n");
    if (load_shader2D_textured() != 0) zoxel_log("    ! error loading [shader2D_textured]\n");
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("opengl_load_shaders");
    #endif
    return 0;
}