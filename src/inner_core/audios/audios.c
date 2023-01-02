#ifndef zoxel_audios
#define zoxel_audios

#ifdef SDL_MIXER
    #ifdef ANDROID_BUILD
		  #include <SDL_mixer.h>
    #else
		  #include <SDL2/SDL_mixer.h>
    #endif
#endif
#include "sounds/sounds.c"
#include "musics/musics.c"

#ifdef SDL_MIXER
unsigned char load_audio()
{
	unsigned char success = 1;
    const int sample_rate = 44100;
    const int channels_count = 1;   // 2
    // MIX_DEFAULT_FORMAT
    // https://wiki.libsdl.org/SDL2/SDL_AudioFormat
	if( Mix_OpenAudio( sample_rate, AUDIO_F32SYS, channels_count, 2048 ) < 0 )
	{
		zoxel_log( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		success = 0;
	}
    if (!load_static_sounds())
    {
		success = 0;
    }
	return success;
}

void close_audio()
{
    dispose_static_sounds();
	Mix_Quit(); // Close SDL subsystems
}
#else
void close_audio() { }
#endif

//! textures Module.
void AudiosImport(ecs_world_t *world)
{
    zoxel_module(Audios)
    zoxel_import_module(Sounds)
    zoxel_import_module(Musics)
#ifdef SDL_MIXER
    load_audio();
#endif
}
#endif