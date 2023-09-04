#ifdef SDL_MIXER
    #ifdef zoxel_on_android
		  #include <SDL_mixer.h>
    #else
		  #include <SDL2/SDL_mixer.h>
    #endif
#endif