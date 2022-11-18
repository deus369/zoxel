#ifndef zoxel_opengl
#define zoxel_opengl

// #include <GL/gl.h>
// https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions
// https://stackoverflow.com/questions/12682950/is-there-a-webgl-equivalent-of-glgenvertexarrays-and-glbindvertexarrays

// #include <GLFW/glfw3.h>
#include "dynamic/opengl.h"
#include "dynamic/opengl.c"
// MaterialGPULink data
#include "data/material2D.c"
#include "data/material3D.c"
#include "data/material2D_textured.c"
#include "data/material3D_textured.c"
// util Functions
#include "util/primitive_square.c"
#include "util/primitive_mesh_util.c"
#include "util/shaders_util.c"    // uses InitializeMesh
#include "util/opengl_util.c"
// rendering
#include "rendering/instanced2D_material.c"
#include "rendering/textured2D_material.c"
#include "rendering/instanced3D_material.c"
#include "rendering/unique3D_material.c"
#include "rendering/shader3D_textured.c"

// #include "shaders/terrain.vert"
// #include "shaders/terrain.frag"

int LoadShaders()
{
    if (LoadInstance2DMaterial() != 0)
    {
        printf("Error loading Instance Shader.\n");
    }
    if (LoadTextureRender2DShader() != 0)
    {
        printf("Error loading Texture Shader.\n");
    }
    if (LoadInstance3DMaterial() != 0)
    {
        printf("Error [LoadInstance3DMaterial]\n");
    }
    if (load_shader3D_textured())
    {
        printf("Error [load_shader3D_textured]\n");
    }
    return 0;
}

//! Cleanup Meshes VBOs
void dispose_opengl()
{
    DisposeInstance2DMaterial();
    DisposeTexturedMaterial2D();
    DisposeInstanced3DMaterial();
    dispose_shader3D_textured();
// #ifdef zoxel_catch_opengl_errors
//     GLenum err7 = glGetError();
//     if (err7 != GL_NO_ERROR)
//     {
//         printf("GL HAD ERROR with end of dispose_opengl: %i\n", err7);
//     }
// #endif
}

//! The OpenGL Module.
void OpenGLImport(ecs_world_t *world)
{
    ECS_MODULE(world, OpenGL);
    // check open gl for failures?
    opengl_load_functions();
    int didFail = LoadShaders();
    if (didFail == EXIT_FAILURE)
    {
        printf("Failed to InitializeOpenGL.");
    }
}

#endif