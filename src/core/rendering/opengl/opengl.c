#ifndef zoxel_opengl
#define zoxel_opengl

// #include <GL/gl.h>
// https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions
// https://stackoverflow.com/questions/12682950/is-there-a-webgl-equivalent-of-glgenvertexarrays-and-glbindvertexarrays

// #include <GLFW/glfw3.h>
#include "dynamic/opengl.h"
#include "dynamic/opengl.c"
// MaterialGPULink data
#include "data/Material2D.c"
#include "data/MaterialTextured2D.c"
#include "data/Material3D.c"
// util Functions
#include "util/primitive_mesh_util.c"
#include "util/shaders_util.c"    // uses InitializeMesh
#include "util/opengl_util.c"
// rendering
#include "rendering/Instanced2DMaterial.c"
#include "rendering/Textured2DMaterial.c"
#include "rendering/Instanced3DMaterial.c"

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
    return 0;
}

//! Cleanup Meshes VBOs
void EndAppOpenGL()
{
    DisposeInstance2DMaterial();
    DisposeTexturedMaterial2D();
    DisposeInstanced3DMaterial();
#ifdef DEVBUILD
    GLenum err7 = glGetError();
    if (err7 != GL_NO_ERROR)
    {
        printf("GL HAD ERROR with end of EndAppOpenGL: %i\n", err7);
    }
#endif
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