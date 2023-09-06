#ifndef zoxel_opengl
#define zoxel_opengl

#define GL_GLEXT_PROTOTYPES
#ifdef USE_SDL_3
    #include <SDL3/SDL_opengl.h>
#else
    #ifdef zoxel_on_android
        #include <SDL_opengl.h>
    #else
        #include <SDL2/SDL_opengl.h>
    #endif
#endif
// zoxel_settings
float3 opengl_clear_color = { 125 / 255.0f, 125 / 255.0f, 125 / 255.0f };
// zoxel_data
#include "data/GLuint2.c"
// zoxel_util
#include "util/error_util.c"
#include "util/primitive_square.c"
#include "util/primitive_mesh_util.c"
#include "util/shaders_util.c"
#include "util/opengl_util.c"
#include "util/compute_util.c"
// basics 2D
#include "shaders/instanced2D.c"
#include "shaders/textured2D.c"
#include "render2D/material2D.c"
#include "render2D/instanced2D_material.c"
#include "render2D_textured/textured2D_material.c"
#include "render2D_textured/shader_textured2D.c"
// loads / disposes all shaders, move to higher level
#include "util/opengl_main_util.c"

unsigned char initialize_opengl(ecs_world_t *world) {
    #ifdef zoxel_debug_opengl
        zoxel_log(" > initializing opengl\n");
    #endif
    /*glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "   ! error initializing GLEW: %s\n", glewGetErrorString(err));
        exit(1);
    }*/
    print_opengl();
    if (check_compute_shader_support() == EXIT_FAILURE) zoxel_log(" ! compute is not supported\n");
    if (opengl_load_shaders(world) == EXIT_FAILURE) {
        zoxel_log(" - failed to load all shaders\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

zox_begin_module(OpenGL)
zoxel_end_module(OpenGL)

#endif

// #include <GL/glew.h>    // used to import opengl functions
// float3 opengl_clear_color = { 2.0f / 255.0f, 16.0f / 255.0f, 24.0f / 255.0f };
// #include "dynamic/opengl_functions.c"
/*if (opengl_load_functions() == EXIT_FAILURE) {
    zoxel_log(" - opengl failed to load [opengl_load_functions]\n");
    return EXIT_FAILURE;
}*/
/*#ifdef USE_SDL_3
    #include <SDL3/SDL_opengl.h>
#else
    #ifdef zoxel_on_android
        #include <SDL_opengl.h>
    #else
        #include <SDL2/SDL_opengl.h>
    #endif
#endif*/
// if(SDL_GL_LoadLibrary(NULL) < 0) zoxel_log("    ! failed to load opengl library (%s)\n", SDL_GetError());
//glUseProgram = (gl_one_int) SDL_GL_GetProcAddress("glUseProgram");
//glDispatchCompute = (gl_three_int) SDL_GL_GetProcAddress("glDispatchCompute");
/*glLinkProgram = (gl_one_int) SDL_GL_GetProcAddress("glLinkProgram");
glAttachShader = (gl_two_int) SDL_GL_GetProcAddress("glAttachShader");
glCreateProgram = (gl_ret_one_int_void) SDL_GL_GetProcAddress("glCreateProgram");
glCompileShader = (gl_one_int) SDL_GL_GetProcAddress("glCompileShader");
glCreateShader = (gl_ret_one_int_glenum) SDL_GL_GetProcAddress("glCreateShader");
glGenBuffers = (gl_int_and_int_pointer) SDL_GL_GetProcAddress("glGenBuffers");
glShaderSource = (glShaderSource_fun) SDL_GL_GetProcAddress("glShaderSource");
glGetProgramiv = (glGetProgramiv_fun) SDL_GL_GetProcAddress("glGetProgramiv");*/

// #define GL3_PROTOTYPES 1
// #include <GL/glxext.h>
// #include <GL/gl.h>
//#define GL_GLEXT_PROTOTYPES
// #include <GL/gl.h>
// #include <GL/glx.h>
// #include <GL/glu.h>
// #include <GL/glew.h>
// typedef void (*glUseProgram_fun)(unsigned int);
/*typedef int (*gl_ret_one_int_void)(void);
typedef void (*gl_one_int)(unsigned int);
typedef void (*gl_two_int)(unsigned int, unsigned int);
typedef void (*gl_three_int)(unsigned int, unsigned int, unsigned int);
gl_one_int glUseProgram = 0;
gl_three_int glDispatchCompute = 0;*/
/*gl_one_int glLinkProgram = 0;
gl_one_int glCompileShader = 0;
gl_two_int glAttachShader = 0;
gl_ret_one_int_void glCreateProgram = 0;
typedef void (*gl_int_and_int_pointer)(unsigned int, unsigned int *);
gl_int_and_int_pointer glGenBuffers = 0;
typedef int (*gl_ret_one_int_glenum)(GLenum);
gl_ret_one_int_glenum glCreateShader = 0;
typedef void (*glShaderSource_fun)(GLuint, GLsizei, const GLchar**, const GLint*);
glShaderSource_fun glShaderSource = 0;
typedef void (*glGetProgramiv_fun)(GLuint, GLenum, GLint*);
glGetProgramiv_fun glGetProgramiv = 0;*/