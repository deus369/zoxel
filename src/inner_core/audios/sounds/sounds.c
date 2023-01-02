#ifndef zoxel_sounds
#define zoxel_sounds

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
zoxel_declare_tag(Sound)
zoxel_memory_component(SoundData, float)    //! A sound has an array of bytes.
zoxel_component(SoundLength, double)        //! The length of a sound.
zoxel_state_component(GenerateSound)        //! A state event for generating sounds.
zoxel_state_component(PlaySound)            //! A state event for playing sounds.
zoxel_state_component(SoundDirty)
#include "components/SDLSound.c"
#include "prefabs/sound_prefab.c"
#ifdef SDL_MIXER
	#include "util/static_sound_util.c"
#endif
// systems
#include "systems/generate_sound_system.c"
#ifdef SDL_MIXER
	#include "systems/play_sound_system.c"
#endif
#include "systems/update_sound_system.c"
zoxel_reset_system(PlaySoundResetSystem, PlaySound)
zoxel_reset_system(GenerateSoundResetSystem, GenerateSound)
zoxel_reset_system(SoundDirtyResetSystem, SoundDirty)

//! Sounds Module.
void SoundsImport(ecs_world_t *world)
{
    zoxel_module(Sounds)
    zoxel_define_tag(Sound)
    zoxel_memory_component_define(world, SoundData);
    zoxel_define_component(SoundLength)
    zoxel_define_component(GenerateSound)
    zoxel_define_component(PlaySound)
    zoxel_define_component(SDLSound)
    zoxel_define_component(SoundDirty)
    ecs_set_hooks(world, SDLSound, { .dtor = ecs_dtor(SDLSound) });
    // systems
#ifdef SDL_MIXER
    zoxel_system_main_thread(world, PlaySoundSystem, EcsPreStore, [none] Sound, [in] PlaySound, [in] SDLSound);
#endif
    zoxel_system(world, GenerateSoundSystem, EcsOnValidate, [none] Sound, [in] GenerateSound, [out] SoundData, [in] SoundLength, [out] SoundDirty);
    zoxel_system_main_thread(world, UpdateSoundSystem, EcsPostUpdate, [none] Sound, [in] SoundDirty, [in] SoundData, [out] SDLSound);
	zoxel_reset_system_define(PlaySoundResetSystem, PlaySound);
    zoxel_reset_system_define(GenerateSoundResetSystem, GenerateSound);
    zoxel_reset_system_define(SoundDirtyResetSystem, SoundDirty);
    // prefabs
    spawn_prefab_sound(world);
    // test
    // spawn_generated_sound(world);
}
#endif