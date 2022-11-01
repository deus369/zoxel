#ifndef Zoxel_OpenGL
#define Zoxel_OpenGL

// #include <GL/gl.h>
// https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions
// https://stackoverflow.com/questions/12682950/is-there-a-webgl-equivalent-of-glgenvertexarrays-and-glbindvertexarrays

// #include <GLFW/glfw3.h>
#include "Dynamic/opengl.h"
#include "Dynamic/opengl.c"
// Material Data
#include "Data/Material2D.c"
#include "Data/MaterialTextured2D.c"
#include "Data/Material3D.c"
// Util Functions
#include "Util/MeshUtil.c"
#include "Util/ShaderUtil.c"    // uses InitializeMesh
#include "Util/OpenGLUtil.c"
// Rendering
#include "Rendering/Instanced2DMaterial.c"
#include "Rendering/Textured2DMaterial.c"
#include "Rendering/Instanced3DMaterial.c"

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