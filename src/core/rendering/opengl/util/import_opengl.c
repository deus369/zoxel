#define GL_GLEXT_PROTOTYPES

#ifdef zox_lib_sdl_direct
    #include <SDL_opengl.h>
#else
    #ifdef USE_SDL_3
        #include <SDL3/SDL_opengl.h>
    #else
        #if defined(zox_sdl_import_file_only)
            #include <SDL_opengl.h>
        #else
            #include <SDL2/SDL_opengl.h>
        #endif
    #endif
#endif
