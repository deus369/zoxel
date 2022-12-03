#ifndef zoxel_sounds
#define zoxel_sounds

// resources
#define static_sounds_length 5
const char *sound_file_names[] = {
    resources_folder_name"sounds/bloop.wav",
	resources_folder_name"sounds/scratch.wav",
	resources_folder_name"sounds/high.wav",
	resources_folder_name"sounds/medium.wav",
	resources_folder_name"sounds/low.wav"
};
#ifdef SDL_MIXER
Mix_Chunk *sounds[static_sounds_length];
#endif
// Tags
ECS_DECLARE(Sound);
// components
//! A sound has an array of bytes.
zoxel_memory_component(SoundData, unsigned char);
//! The length of a sound.
zoxel_component(SoundLength, double);
//! A state event for generating sounds.
zoxel_component(GenerateSound, bool);
//! A state event for playing sounds.
zoxel_state_component(PlaySound);
// prefabs
#include "prefabs/sound_prefab.c"
// util
// systems
zoxel_reset_system(PlaySoundResetSystem, PlaySound)

#ifdef SDL_MIXER
	#include "systems/play_sound_system.c"

	bool load_static_sounds()
	{
		bool success = true;
		for (int i = 0; i < static_sounds_length; i++)
		{
			sounds[i] = Mix_LoadWAV(sound_file_names[i]);
			if(sounds[i] == NULL)
			{
				zoxel_log_arg( "Failed to load sound effect[%i]! SDL_mixer Error: %s\n", i, Mix_GetError() );
				success = false;
			}
		}
		return success;
	}

	void dispose_static_sounds()
	{
		for (int i = 0; i < static_sounds_length; i++)
		{
			Mix_FreeChunk(sounds[i]);
		}
	}
#endif

//! Sounds Module.
void SoundsImport(ecs_world_t *world)
{
    ECS_MODULE(world, Sounds);
    ECS_TAG_DEFINE(world, Sound);
    zoxel_memory_component_define(world, SoundData);
    ECS_COMPONENT_DEFINE(world, SoundLength);
    ECS_COMPONENT_DEFINE(world, GenerateSound);
    ECS_COMPONENT_DEFINE(world, PlaySound);
    // systems
    zoxel_reset_system_define(PlaySoundResetSystem, PlaySound);
#ifdef SDL_MIXER
    zoxel_event_respond_system_main_thread(PlaySoundSystem, Sound, PlaySound);
#endif
    // prefabs
    spawn_prefab_sound(world);
    // SpawnSoundPrefab(world);
}
#endif