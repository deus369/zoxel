#ifndef zoxel_sounds
#define zoxel_sounds

// zoxel_settings
#ifdef SDL_MIXER
    #ifdef zoxel_on_android
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
const float sound_attack_multiplier = 0.02f; // 0.04f
const float sound_dampen_multiplier = 0.7f; // 0.92f
const float sound_noise = 0.02f; // 0.04
// zoxel_prefab_declares
zox_declare_tag(Sound)
zox_byte_component(InstrumentType)
zox_memory_component(SoundData, float)   //! A sound has an array of bytes.
zox_component(SoundLength, double)       //! The length of a sound.
zox_component(SoundFrequency, float)     //! The frequency of the generated sound.
zox_byte_component(GenerateSound)        //! A state event for generating sounds.
zox_byte_component(TriggerSound)         //! A state event for playing sounds.
// renamed PlaySound to TriggerSound temporarily, cause of windows.h conflict
zox_byte_component(SoundDirty)
#include "components/SDLSound.c"
// zoxel_prefab_includes
#include "prefabs/sound.c"
#include "prefabs/generated_sound.c"
// zoxel_util_includes
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
// zoxel_system_declares
#include "systems/sound_generate_system.c"
#ifdef SDL_MIXER
	#include "systems/play_sound_system.c"
    #include "systems/sound_update_system.c"
#endif

void spawn_prefabs_sounds(ecs_world_t *world) {
    spawn_prefab_sound(world);
    spawn_prefab_generated_sound(world);
    load_audio_sdl();
}

zox_begin_module(Sounds)
zox_define_tag(Sound)
zox_define_component(InstrumentType)
zox_define_component(SoundLength)
zox_define_component(GenerateSound)
zox_define_component(SoundFrequency)
zox_define_component(TriggerSound)
zox_define_component_w_dest(SDLSound)
zox_define_component(SoundDirty)
zox_define_memory_component(SoundData)
zox_system(SoundGenerateSystem, EcsOnValidate, [none] Sound, [out] GenerateSound, [in] SoundLength, [in] SoundFrequency, [in] InstrumentType, [out] SoundData, [out] SoundDirty)
#ifdef SDL_MIXER
    zox_system(SoundUpdateSystem, EcsPreStore, [none] Sound, [in] SoundData, [out] SoundDirty, [out] SDLSound)
    zox_system(PlaySoundSystem, EcsOnStore, [none] Sound, [out] TriggerSound, [in] SoundLength, [in] SDLSound)
#endif
zoxel_end_module(Sounds)

#endif