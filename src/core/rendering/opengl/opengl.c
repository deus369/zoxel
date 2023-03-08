#ifndef zoxel_opengl
#define zoxel_opengl

#include "dynamic/opengl_functions.c"
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
#include "util/opengl_main_util.c"

void print_opengl()
{
    #ifdef zoxel_debug_opengl
        zoxel_log("OpenGL Context\n");
        zoxel_log("    Vendor:   %s\n", glGetString(GL_VENDOR));
        zoxel_log("    Renderer: %s\n", glGetString(GL_RENDERER));
        zoxel_log("    Version:  %s\n", glGetString(GL_VERSION));
        zoxel_log("    GLSL Version:    %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    #endif
}

int check_compute_shader_support()
{
    // Check whether compute shaders are supported
    if (!glUseProgram)
    {
        printf("glUseProgram is not supported\n");
        return 0;
    }

    if (!glDispatchCompute)
    {
        printf("glDispatchCompute is not supported\n");
        return 0;
    }

    // Get the maximum number of compute work groups
    GLint max_compute_group_count[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &max_compute_group_count[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &max_compute_group_count[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &max_compute_group_count[2]);
    printf("Maximum compute work group count: %d, %d, %d\n",
        max_compute_group_count[0], max_compute_group_count[1], max_compute_group_count[2]);

    // Get the maximum compute work group size
    GLint max_compute_group_size[3];
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &max_compute_group_size[0]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &max_compute_group_size[1]);
    glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &max_compute_group_size[2]);
    printf("Maximum compute work group size: %d, %d, %d\n",
        max_compute_group_size[0], max_compute_group_size[1], max_compute_group_size[2]);
    
    // Get the maximum compute work group invocations
    GLint max_compute_work_group_invocations;
    glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &max_compute_work_group_invocations);
    printf("Maximum compute work group invocations: %d\n", max_compute_work_group_invocations);
    
    return 1;
}

//! The OpenGL Module.
void OpenGLImport(ecs_world_t *world)
{
    zoxel_module(OpenGL)
    // check open gl for failures?
    opengl_load_functions();
    int didFail = load_all_shaders();
    if (didFail == EXIT_FAILURE)
    {
        printf("Failed to InitializeOpenGL.\n");
    }
    print_opengl();
    int supports_compute = check_compute_shader_support();
    if (supports_compute == 0)
    {
        printf("Failed to support Compute Shaders.\n");
    }
}
#endif