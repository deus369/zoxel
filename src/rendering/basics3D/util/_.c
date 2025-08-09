void catch_basic3D_errors(char* function_name) {
#ifdef is_catch_basic3D_errors
    check_opengl_error(function_name);
#else
    (void) function_name;
#endif
}

void spawn_shaders_basics3D(ecs *world) {
    spawn_material_basic3D(world);
    spawn_material_colored3D(world);
    spawn_material_textured3D(world);
#ifndef zox_disable_rendering_instances
    spawn_material_vox_instance(world);
#endif
}