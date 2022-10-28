#ifndef Zoxel_OpenGL
#define Zoxel_OpenGL

// #include <GL/gl.h>
// https://www.khronos.org/opengl/wiki/Load_OpenGL_Functions
// https://stackoverflow.com/questions/12682950/is-there-a-webgl-equivalent-of-glgenvertexarrays-and-glbindvertexarrays

// #include <GLFW/glfw3.h>
#include "Dynamic/opengl.h"
#include "Dynamic/opengl.c"

// Material Data
#include "Data/MaterialTextured2D.c"

// Util Functions
#include "Util/MeshUtil.c"
#include "Util/ShaderUtil.c"    // uses InitializeMesh
#include "Util/InstancingUtil.c"
#include "Util/TexturedMeshUtil.c"
#include "Util/OpenGLUtil.c"

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