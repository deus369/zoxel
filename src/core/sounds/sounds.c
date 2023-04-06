#ifndef zoxel_sounds
#define zoxel_sounds

#ifdef SDL_MIXER
    #ifdef ANDROID_BUILD
		  #include <SDL_mixer.h>
    #else
		  #include <SDL2/SDL_mixer.h>
    #endif
#endif
#define sound_sample_rate 44100 // / 2
#define sample_rate_f 44100.0f // / 2.0f
#define static_sounds_length 5
#ifdef zoxel_debug_sounds
    #define sound_display_skip_rate 35
    #define sound_display_start 0.0f
    #define sound_display_end 1.0f
#endif
zoxel_declare_tag(Sound)
zoxel_byte_component(InstrumentType)
zoxel_memory_component(SoundData, float)   //! A sound has an array of bytes.
zoxel_component(SoundLength, double)       //! The length of a sound.
zoxel_component(SoundFrequency, float)     //! The frequency of the generated sound.
zoxel_byte_component(GenerateSound)        //! A state event for generating sounds.
zoxel_byte_component(TriggerSound)         //! A state event for playing sounds.
// renamed PlaySound to TriggerSound temporarily, cause of windows.h conflict
zoxel_byte_component(SoundDirty)
#include "components/SDLSound.c"
#include "prefabs/sound_prefab.c"
#include "util/static_sound_util.c"
#include "util/sdl_mix_util.c"
#include "instruments/note_frequencies.c"
#include "instruments/sin_waves.c"
#include "instruments/square_waves.c"
#include "instruments/triangle_waves.c"
#include "instruments/sawtooth_waves.c"
#include "instruments/fm_synthesis_waves.c"
#include "instruments/noise_waves.c"
#include "instruments/instruments.c"
#include "instruments/envelop.c"
#include "systems/sound_generate_system.c"
#ifdef SDL_MIXER
	#include "systems/play_sound_system.c"
    #include "systems/sound_update_system.c"
#endif
zoxel_reset_system(PlaySoundResetSystem, TriggerSound)
zoxel_reset_system(GenerateSoundResetSystem, GenerateSound)
zoxel_reset_system(SoundDirtyResetSystem, SoundDirty)

zoxel_begin_module(Sounds)
zoxel_define_tag(Sound)
zoxel_define_component(InstrumentType)
zoxel_define_component(SoundLength)
zoxel_define_component(GenerateSound)
zoxel_define_component(SoundFrequency)
zoxel_define_component(TriggerSound)
zoxel_define_component(SDLSound)
zoxel_define_component(SoundDirty)
zoxel_define_memory_component(SoundData)
ecs_set_hooks(world, SDLSound, { .dtor = ecs_dtor(SDLSound) });
zoxel_system(SoundGenerateSystem, EcsOnValidate, [none] Sound, [in] GenerateSound, [in] SoundLength, [in] SoundFrequency, [in] InstrumentType, [out] SoundData, [out] SoundDirty)
#ifdef SDL_MIXER
    zoxel_system_main_thread(world, SoundUpdateSystem, EcsPreStore, [none] Sound, [in] SoundDirty, [in] SoundData, [out] SDLSound)
    zoxel_system_main_thread(world, PlaySoundSystem, EcsPreStore, [none] Sound, [in] TriggerSound, [in] SoundLength, [in] SDLSound)
#endif
zoxel_define_reset_system(PlaySoundResetSystem, TriggerSound)
zoxel_define_reset_system(GenerateSoundResetSystem, GenerateSound)
zoxel_define_reset_system(SoundDirtyResetSystem, SoundDirty)
spawn_prefab_sound(world);
load_audio_sdl();
zoxel_end_module(Sounds)

#endif