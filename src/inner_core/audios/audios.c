#ifndef zoxel_audios
#define zoxel_audios

// MIX_DEFAULT_FORMAT https://wiki.libsdl.org/SDL2/SDL_AudioFormat
#ifdef SDL_MIXER
    #ifdef ANDROID_BUILD
		  #include <SDL_mixer.h>
    #else
		  #include <SDL2/SDL_mixer.h>
    #endif
#endif
zoxel_byte_component(InstrumentType)
#include "sounds/sounds.c"
#include "musics/musics.c"

unsigned char load_audio() {
    #ifdef SDL_MIXER
        // const int sample_rate = 44100;
        const int channels_count = 1;   // 2
        if(Mix_OpenAudio(sound_sample_rate, AUDIO_F32SYS, channels_count, 2048) < 0) {
            zoxel_log(" - sdl audio could not initialize [%s]\n", Mix_GetError());
            return EXIT_FAILURE;
        }
        /*if (!load_static_sounds())
        {
            success = 0;
        }*/
        zoxel_log(" + sdl audio has initialized\n");
        return EXIT_SUCCESS;
    #endif
}

void close_audio() {
    #ifdef SDL_MIXER
    dispose_static_sounds();
    // Close SDL subsystems
	Mix_Quit();
    #endif
}

void AudiosImport(ecs_world_t *world) {
    zoxel_module(Audios)
    zoxel_define_component(InstrumentType)
    zoxel_import_module(Sounds)
    zoxel_import_module(Musics)
    load_audio();
}
#endif