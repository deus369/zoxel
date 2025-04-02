GLuint2 shader3D;

#include "basic3D.c"
#include "instanced3D_material.c"
#include "unique3D_material.c"
#include "textured3D_shader.c"
#include "shader3D_colored.c"
#include "mesh.c"

void catch_basic3D_errors(char* function_name) {
    #ifdef is_catch_basic3D_errors
    check_opengl_error(function_name);
    #endif
}

void spawn_shaders_basics3D(ecs_world_t *world) {
    if (load_shader3D_basic()) zox_log("    ! error loading [shader3D_basic]\n");
    spawn_material_basic3D(world);
    spawn_material_colored3D(world);
    spawn_material_textured3D(world);
    #ifndef zox_disable_rendering_instances
        spawn_material_vox_instance(world);
    #endif
}