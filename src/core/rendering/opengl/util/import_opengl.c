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