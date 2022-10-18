#ifndef DEMO_OPENGL_H_INCLUDED
#define DEMO_OPENGL_H_INCLUDED
#include <stdbool.h>
#include <SDL2/SDL_opengl.h>

// List of required OpenGL functions and their corresponding typedefs (defined
// somewhere under <SDL2/SDL_opengl.h>. The "OPENGL_FUNCTIONS" macro will do
// different things in different locations. Each of these functions requires
// three pieces of code: an initial declaration, an initial definition, and a
// dynamic load assignment.
//
// More info about dynamic loading can be found here:
// https://en.wikipedia.org/wiki/Dynamic_loading

#define OPENGL_FUNCTIONS                                      \
    OPENGL_FUNCTION(glCreateShader, PFNGLCREATESHADERPROC)                          \
    OPENGL_FUNCTION(glDeleteShader, PFNGLDELETESHADERPROC)                          \
    OPENGL_FUNCTION(glAttachShader, PFNGLATTACHSHADERPROC)                          \
    OPENGL_FUNCTION(glDetachShader, PFNGLDETACHSHADERPROC)                          \
    OPENGL_FUNCTION(glShaderSource, PFNGLSHADERSOURCEPROC)                          \
    OPENGL_FUNCTION(glCompileShader, PFNGLCOMPILESHADERPROC)                        \
    OPENGL_FUNCTION(glGetShaderiv, PFNGLGETSHADERIVPROC)                            \
    OPENGL_FUNCTION(glGetShaderInfoLog, PFNGLGETSHADERINFOLOGPROC)                  \
    OPENGL_FUNCTION(glCreateProgram, PFNGLCREATEPROGRAMPROC)                        \
    OPENGL_FUNCTION(glDeleteProgram, PFNGLDELETEPROGRAMPROC)                        \
    OPENGL_FUNCTION(glUseProgram, PFNGLUSEPROGRAMPROC)                              \
    OPENGL_FUNCTION(glLinkProgram, PFNGLLINKPROGRAMPROC)                            \
    OPENGL_FUNCTION(glValidateProgram, PFNGLVALIDATEPROGRAMPROC)                    \
    OPENGL_FUNCTION(glGetProgramiv, PFNGLGETPROGRAMIVPROC)                          \
    OPENGL_FUNCTION(glGetProgramInfoLog, PFNGLGETPROGRAMINFOLOGPROC)                \
    OPENGL_FUNCTION(glUniform1i, PFNGLUNIFORM1IPROC)                                \
    OPENGL_FUNCTION(glUniform1f, PFNGLUNIFORM1FPROC)                                \
    OPENGL_FUNCTION(glUniform3f, PFNGLUNIFORM3FPROC)                                \
    OPENGL_FUNCTION(glUniformMatrix4fv, PFNGLUNIFORMMATRIX4FVPROC)                  \
    OPENGL_FUNCTION(glGetUniformLocation, PFNGLGETUNIFORMLOCATIONPROC)              \
    OPENGL_FUNCTION(glGenBuffers, PFNGLGENBUFFERSPROC)                              \
    OPENGL_FUNCTION(glDeleteBuffers, PFNGLDELETEBUFFERSPROC)                        \
    OPENGL_FUNCTION(glBindBuffer, PFNGLBINDBUFFERPROC)                              \
    OPENGL_FUNCTION(glBufferData, PFNGLBUFFERDATAPROC)                              \
    OPENGL_FUNCTION(glVertexAttribPointer, PFNGLVERTEXATTRIBPOINTERPROC)            \
    OPENGL_FUNCTION(glEnableVertexAttribArray, PFNGLENABLEVERTEXATTRIBARRAYPROC)    \
    OPENGL_FUNCTION(glDisableVertexAttribArray, PFNGLDISABLEVERTEXATTRIBARRAYPROC)  \
    OPENGL_FUNCTION(glBindVertexArray, PFNGLBINDVERTEXARRAYPROC)                    \
    OPENGL_FUNCTION(glGenVertexArrays, PFNGLGENVERTEXARRAYSPROC)                    \
    OPENGL_FUNCTION(glDeleteVertexArrays, PFNGLDELETEVERTEXARRAYSPROC)

// Declare an OpenGL function. Other translation units that require
// calling OpenGL functions will link against these declarations.
//
// OPENGL_DECLARE(glCreateShader, PFNGLCREATESHADERPROC)
//
//   becomes
//
// extern PFNGLCREATESHADERPROC glCreateShader;
#define OPENGL_DECLARE(func_name, func_type)  \
    extern func_type func_name;

// Set the OPENGL_FUNCTION macro to OPENGL_DECLARE and then splat
// all of the declarations out here. Unset OPENGL_FUNCTION back
// to nothing afterwards just to be safe.
#define OPENGL_FUNCTION OPENGL_DECLARE
OPENGL_FUNCTIONS
#undef OPENGL_FUNCTION

// Call this function after obtaining an OpenGL context
// to dynamically load the modern functions.
bool opengl_load_functions(void);

#endif