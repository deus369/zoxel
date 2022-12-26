#ifndef zoxel_opengl
#define zoxel_opengl

// #include <GL/gl.h>
// https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions
// https://stackoverflow.com/questions/12682950/is-there-a-webgl-equivalent-of-glgenvertexarrays-and-glbindvertexarrays

// #include <GLFW/glfw3.h>
#include "dynamic/opengl.h"
#include "dynamic/opengl.c"
// util Functions
#include "util/primitive_square.c"
#include "util/primitive_mesh_util.c"
#include "util/shaders_util.c"    // uses initialize_mesh
#include "util/opengl_util.c"
// render2D
#include "render2D/material2D.c"
#include "render2D/instanced2D_material.c"
// render2D textured
#include "render2D_textured/material2D_textured.c"
#include "render2D_textured/shader2D_textured.c"
// render3D
#include "data/material3D.c"
#include "rendering/instanced3D_material.c"
// render3D textured
#include "data/material3D_textured.c"
#include "rendering/unique3D_material.c"
#include "rendering/shader3D_textured.c"
// material3D_colored
#include "data/material3D_colored.c"
#include "rendering/shader3D_colored.c"

int load_all_shaders()
{
    if (load_instance2D_material() != 0)
    {
        printf("Error loading Instance Shader.\n");
    }
    if (load_shader2D_textured() != 0)
    {
        printf("Error loading Texture Shader.\n");
    }
    if (load_shader3D_basic() != 0)
    {
        printf("Error [load_shader3D_basic]\n");
    }
    if (load_shader3D_colored() != 0)
    {
        printf("Error [load_shader3D_colored]\n");
    }
    if (load_shader3D_textured())
    {
        printf("Error [load_shader3D_textured]\n");
    }
    #ifdef zoxel_catch_opengl_errors
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            zoxel_log_arg("GL ERROR with load_all_shaders [%i]\n", err);
            return false;
        }
    #endif
    return 0;
}

//! Cleanup Meshes VBOs
void dispose_opengl()
{
    DisposeInstance2DMaterial();
    dispose_shader2D_textured();
    DisposeInstanced3DMaterial();
    dispose_shader3D_textured();
    dispose_shader3D_colored();
// #ifdef zoxel_catch_opengl_errors
//     GLenum err7 = glGetError();
//     if (err7 != GL_NO_ERROR)
//     {
//         printf("GL ERROR with end of dispose_opengl: %i\n", err7);
//     }
// #endif
}

//! The OpenGL Module.
void OpenGLImport(ecs_world_t *world)
{
    ECS_MODULE(world, OpenGL);
    // check open gl for failures?
    opengl_load_functions();
    int didFail = load_all_shaders();
    if (didFail == EXIT_FAILURE)
    {
        printf("Failed to InitializeOpenGL.");
    }
}

#endif