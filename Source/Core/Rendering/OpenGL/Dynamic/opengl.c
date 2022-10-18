#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "opengl.h"

// Define an OpenGL function. Until dynamically loaded, it will
// be set to NULL and should NOT be called. Doing so will cause
// a segfault.
//
// OPENGL_DEFINE(glCreateShader, PFNGLCREATESHADERPROC)
//
//   becomes
//
// PFNGLCREATESHADERPROC glCreateShader = NULL;
#define OPENGL_DEFINE(func_name, func_type)  \
    func_type func_name = NULL;

// Define all of the initally-NULL OpenGL functions.
#define OPENGL_FUNCTION OPENGL_DEFINE
OPENGL_FUNCTIONS
#undef OPENGL_FUNCTION

// Define a union that bridges the gap between object pointers
// and function pointers. This is needed because the C standard
// forbids assignment between function pointers and object pointers
// (void*, in our case). They are NOT guaranteed to be the same size.
// By pulling the void* from SDL_GL_GetProcAddress though this union,
// we ensure that the potential difference in pointer sizes is mitigated.
union bridge
{
    void* object_ptr;
    void (*function_ptr)(void);
};

//
//   becomes
//
// glCreateShader = (PFNGLCREATESHADERPROC)(union bridge){
//     .object_ptr = SDL_GL_GetProcAddress("glCreateShader")
// }.function_ptr;
#define OPENGL_LOAD(func_name, func_type)                \
    func_name = (func_type)(union bridge)               \
    {               \
        .object_ptr = SDL_GL_GetProcAddress(#func_name)  \
    }.function_ptr;

// Extra safety step to ensure that all the OpenGL functions were successfully
// dynamically loaded. If a function failed to load, print and error and
// return false back to the caller.
//
// OPENGL_VALIDATE(glCreateShader, PFNGLCREATESHADERPROC)
//
//   becomes
//
// if (glCreateShader == NULL) {
//     fprintf(stderr, "failed to load func: %s\n", "glCreateShader);
//     return false;
// }
#define OPENGL_VALIDATE(func_name, func_type)                      \
    if (func_name == NULL) {                                       \
        fprintf(stderr, "failed to load func: %s\n", #func_name);  \
        return false;                                              \
    }

bool opengl_load_functions(void)
{
    // use SDL2's platform-agnostic loader to pull the "real" addresses
    //  out by name and assign to the definitions above
    //
    // WARN: ISO C forbids conversion of object pointer to function pointer type
    //
    // the C standard defines func ptrs and object ptrs as different types
    //  that are potentially different sizes (though in practice they tend
    //  to be the same)
    // glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");

    #define OPENGL_FUNCTION OPENGL_LOAD
OPENGL_FUNCTIONS
    #undef OPENGL_FUNCTION

    #define OPENGL_FUNCTION OPENGL_VALIDATE
OPENGL_FUNCTIONS
    #undef OPENGL_FUNCTION

    return true;
}