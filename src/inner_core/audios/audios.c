#ifndef zoxel_audios
#define zoxel_audios

#include <SDL2/SDL_mixer.h>
#include "sounds/sounds.c"
#include "musics/musics.c"

bool load_audio()
{
	bool success = true;
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
    if (!load_static_sounds())
    {
		success = false;
    }
	return success;
}

void close_audio()
{
    dispose_static_sounds();
	Mix_Quit(); // Close SDL subsystems
}

//! textures Module.
void AudiosImport(ecs_world_t *world)
{
    ECS_MODULE(world, Audios);
    ECS_IMPORT(world, Sounds);
    ECS_IMPORT(world, Musics);
    load_audio();
}
#endif