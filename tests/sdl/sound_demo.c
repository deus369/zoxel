// cc -std=c99 tests/sdl/sound_demo.c -o sound_demo -lSDL2 -lSDL2_mixer
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include<unistd.h>

bool running = true;
const int sounds_length = 4;
const char *sound_file_names[] = {
	"resources/sounds/scratch.wav",
	"resources/sounds/high.wav",
	"resources/sounds/medium.wav",
	"resources/sounds/low.wav"
};
Mix_Chunk *sounds[4];
const char *music_file_name = "resources/musics/beat.wav";
Mix_Music *gMusic = NULL;

void print_help()
{
	printf( "	h for Help\n" );
	printf( "	1 for High\n" );
	printf( "	2 for Medium\n" );
	printf( "	3 for Low\n" );
	printf( "	4 for Scratch\n" );
	printf( "	9 for Music\n" );
	printf( "	0 for Music Stop\n" );
	printf( "	q for Exit\n" );
}

bool load_audio()
{
	bool success = true;
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	//Load music
	gMusic = Mix_LoadMUS(music_file_name); //  "resources/beat.wav" );	// Mix_LoadMUS
	if( gMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	for (int i = 0; i < sounds_length; i++)
	{
		sounds[i] = Mix_LoadWAV(sound_file_names[i]);
		if(sounds[i] == NULL)
		{
			printf( "Failed to load sound effect[%i]! SDL_mixer Error: %s\n", i, Mix_GetError() );
			success = false;
		}
	}
	return success;
}

void cleanup_audio()
{
	//Free the sound effects
	for (int i = 0; i < sounds_length; i++)
	{
		Mix_FreeChunk(sounds[i]);
	}
	Mix_FreeMusic( gMusic );
	gMusic = NULL;
	//Quit SDL subsystems
	Mix_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !load_audio() )
	{
		printf( "Failed to initialize!\n" );
		return 0;
	}
	else
	{
		printf("---------------\n");
		print_help();
		printf("---------------\n");
		printf("Input Command: ");
		while(running)
		{
			char input = getchar( );
			if (input == '\n')
			{
				continue;
			}
			else if (input == 'q')
			{
				running = false;
			}
			else if (input == 'h')
			{
				print_help();
			}
			else if (input == '4')
			{
				printf("Played Sound [Scratch]\n");
				Mix_PlayChannel( -1, sounds[0], 0 );
			}
			else if (input == '1')
			{
				printf("Played Sound [High]\n");
				Mix_PlayChannel( -1, sounds[1], 0 );
			}
			else if (input == '2')
			{
				printf("Played Sound [Medium]\n");
				Mix_PlayChannel( -1, sounds[2], 0 );
			}
			else if (input == '3')
			{
				printf("Played Sound [Low]\n");
				Mix_PlayChannel( -1, sounds[3], 0 );
			}
			else if (input == '9')
			{
				printf("Played Music\n");
				//If there is no music playing
				if( Mix_PlayingMusic() == 0 )
				{
					//Play the music
					Mix_PlayMusic( gMusic, -1 );
				}
				//If music is being played
				else
				{
					//If the music is paused
					if( Mix_PausedMusic() == 1 )
					{
						//Resume the music
						Mix_ResumeMusic();
					}
					//If the music is playing
					else
					{
						//Pause the music
						Mix_PauseMusic();
					}
				}
			}
			else if (input == '0')
			{
				printf("Stopped Music\n");
				Mix_HaltMusic();
			}
			printf("---------------\n");
			sleep(0.1f);
			printf("Input Command: ");
		}
	}
	//Free resources and close SDL
	cleanup_audio();
	return 0;
}