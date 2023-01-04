#ifndef zoxel_sounds
#define zoxel_sounds

#define sound_sample_rate 44100
#define sample_rate_f 44100.0f
#define static_sounds_length 5
#ifdef zoxel_debug_sounds
    // 50
    #define sound_display_skip_rate 35
    #define sound_display_start 0.0f
    #define sound_display_end 1.0f
#endif
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
zoxel_component(SoundFrequency, float)      //! The frequency of the generated sound.
zoxel_state_component(GenerateSound)        //! A state event for generating sounds.
zoxel_state_component(PlaySound)            //! A state event for playing sounds.
zoxel_state_component(SoundDirty)
#include "components/SDLSound.c"
#include "prefabs/sound_prefab.c"
#ifdef SDL_MIXER
	#include "util/static_sound_util.c"
#endif
#include "util/note_frequencies.c"
#include "util/sin_waves.c"
#include "util/square_waves.c"
#include "util/instruments.c"
#include "util/envelop.c"
// systems
#include "systems/sound_generate_system.c"
#ifdef SDL_MIXER
	#include "systems/play_sound_system.c"
    #include "systems/sound_update_system.c"
#endif
zoxel_reset_system(PlaySoundResetSystem, PlaySound)
zoxel_reset_system(GenerateSoundResetSystem, GenerateSound)
zoxel_reset_system(SoundDirtyResetSystem, SoundDirty)

//! Sounds Module.
void SoundsImport(ecs_world_t *world)
{
    zoxel_module(Sounds)
    zoxel_define_tag(Sound)
    zoxel_define_component(SoundLength)
    zoxel_define_component(GenerateSound)
    zoxel_define_component(SoundFrequency)
    zoxel_define_component(PlaySound)
    zoxel_define_component(SDLSound)
    zoxel_define_component(SoundDirty)
    zoxel_memory_component_define(world, SoundData)
    ecs_set_hooks(world, SDLSound, { .dtor = ecs_dtor(SDLSound) });
    zoxel_system(world, SoundGenerateSystem, EcsOnValidate, [none] Sound,
        [in] GenerateSound, [in] SoundLength, [in] SoundFrequency,
        [out] SoundData, [out] SoundDirty)
#ifdef SDL_MIXER
    zoxel_system_main_thread(world, SoundUpdateSystem, EcsPreStore,
        [none] Sound, [in] SoundDirty, [in] SoundData, [out] SDLSound)
    zoxel_system_main_thread(world, PlaySoundSystem, EcsPreStore,
        [none] Sound, [in] PlaySound, [in] SDLSound)
#endif
	zoxel_reset_system_define(PlaySoundResetSystem, PlaySound)
    zoxel_reset_system_define(GenerateSoundResetSystem, GenerateSound)
    zoxel_reset_system_define(SoundDirtyResetSystem, SoundDirty)
    spawn_prefab_sound(world);
    // test
    // spawn_generated_sound(world);
}
#endif