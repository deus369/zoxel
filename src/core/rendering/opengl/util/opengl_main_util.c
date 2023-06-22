// #include <GL/gl.h>
// https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions
// https://stackoverflow.com/questions/12682950/is-there-a-webgl-equivalent-of-glgenvertexarrays-and-glbindvertexarrays
// #include <GLFW/glfw3.h>

int load_all_shaders() {
    if (load_instance2D_material() != 0) {
        zoxel_log("    ! error loading [instance2D_material]\n");
    }
    if (load_shader2D_textured() != 0) {
        zoxel_log("    ! error loading [shader2D_textured]\n");
    }
    if (load_shader3D_basic() != 0) {
        zoxel_log("    ! error loading [shader3D_basic]\n");
    }
    if (load_shader3D_colored() != 0) {
        zoxel_log("    ! error loading [load_shader3D_colored]\n");
    }
    if (load_shader3D_textured()) {
        zoxel_log("    ! error loading [load_shader3D_textured]\n");
    }
    #ifdef zoxel_catch_opengl_errors
        check_opengl_error("load_all_shaders");
    #endif
    return 0;
}

void dispose_shaders() {
    dispose_shader2D_instance_material();
    dispose_shader2D_textured();
    dispose_shader3D_instance_material();
    dispose_shader3D_textured();
    dispose_shader3D_colored();
}