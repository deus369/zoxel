#ifndef zoxel_sounds
#define zoxel_sounds

// zoxel_settings
#include "util/import_sdl_mixer.c"
#include "settings/settings.c"
// zoxel_prefab_declares
zox_declare_tag(Sound)
zox_byte_component(InstrumentType)
zox_memory_component(SoundData, float)   //! A sound has an array of bytes
zox_component(SoundLength, double)       //! The length of a sound
zox_component(SoundFrequency, float)     //! The frequency of the generated sound
zox_component(SoundVolume, float)     //! The frequency of the generated sound
zox_byte_component(GenerateSound)        //! A state event for generating sounds
zox_byte_component(TriggerSound)         //! A state event for playing sounds
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
    #include "systems/sound_debug_system.c"
#endif

void spawn_prefabs_sounds(ecs_world_t *world) {
    load_audio_sdl();
    #ifdef zox_debug_sdl_audio
        int channel_available = Mix_GroupAvailable(-1); // -1 indicates all channels
        if (channel_available == -1) zoxel_log("  ! sdl audio error: no channels available\n");
        else zoxel_log("  > sdl channel available [%i]\n", channel_available);
    #endif
    spawn_prefab_sound(world);
    spawn_prefab_generated_sound(world);
}

zox_begin_module(Sounds)
// zoxel_define_components
zox_define_tag(Sound)
zox_define_component(InstrumentType)
zox_define_component(SoundLength)
zox_define_component(GenerateSound)
zox_define_component(SoundFrequency)
zox_define_component(SoundVolume)
zox_define_component(TriggerSound)
zox_define_component_w_dest(SDLSound)
zox_define_component(SoundDirty)
zox_define_memory_component(SoundData)
// zoxel_define_systems
zox_system(SoundGenerateSystem, EcsOnValidate, [none] Sound, [out] GenerateSound, [in] SoundLength, [in] SoundFrequency, [in] SoundVolume, [in] InstrumentType, [out] SoundData, [out] SoundDirty)
#ifdef SDL_MIXER
    //#ifdef zox_visualize_sounds
    zox_system_1(SoundDebugSystem, EcsPostUpdate, [none] Sound, [in] SoundData, [in] SoundDirty)
    //#endif
    zox_system(SoundUpdateSystem, EcsPostUpdate, [none] Sound, [in] SoundData, [out] SoundDirty, [out] SDLSound)
    zox_system(PlaySoundSystem, EcsPostUpdate, [none] Sound, [out] TriggerSound, [in] SoundLength, [in] SDLSound)
#endif
zoxel_end_module(Sounds)

#endif