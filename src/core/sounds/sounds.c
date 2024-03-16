#ifndef zoxel_sounds
#define zoxel_sounds

// renamed PlaySound to TriggerSound temporarily, cause of windows.h conflict

// zoxel_settings
int global_master_volume = 64;
const int global_master_volume_max = 128;
const int global_master_volume_increment = 16;
#include "util/import_sdl_mixer.c"
#include "settings/settings.c"
// zoxel_prefab_declares
zox_declare_tag(Sound)
zox_component_byte(InstrumentType)
zox_component_byte(GenerateSound)        //! A state event for generating sounds
zox_component_byte(TriggerSound)         //! A state event for playing sounds
zox_component_byte(SoundDirty)
zox_component_float(SoundFrequency)     //! The frequency of the generated sound
zox_component_float(SoundVolume)     //! The frequency of the generated sound
zox_component_double(SoundLength)       //! The length of a sound
zox_memory_component(SoundData, float)   //! A sound has an array of bytes
#include "components/SDLSound.c"
// zoxel_prefab_includes
#include "prefabs/sound.c"
#include "prefabs/generated_sound.c"
// zoxel_util_includes
#include "util/static_sound_util.c"
#include "util/sdl_mix_util.c"
#include "util/sdl_sound_util.c"
#include "util/sound_files.c"
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
#include "systems/sound_debug_system.c"
#ifdef SDL_MIXER
#include "systems/play_sound_system.c"
#include "systems/sound_update_system.c"
#endif

void initialize_sounds(ecs_world_t *world) {
    load_files_sounds();
}

void dispose_sounds(ecs_world_t *world) {
    dispose_sound_files();
}

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
zox_define_component_byte(InstrumentType)
zox_define_component_byte(SoundDirty)
zox_define_component_byte(TriggerSound)
zox_define_component_byte(GenerateSound)
zox_define_component_double(SoundLength)
zox_define_component_float(SoundFrequency)
zox_define_component_float(SoundVolume)
zox_define_memory_component(SoundData)
#ifdef SDL_MIXER
    zox_define_component_w_dest(SDLSound)
#endif
// zoxel_define_systems
zox_system(SoundGenerateSystem, EcsOnUpdate, [none] Sound, [out] GenerateSound, [out] SoundData, [out] SoundDirty, [in] SoundLength, [in] SoundFrequency, [in] SoundVolume, [in] InstrumentType)
#ifdef SDL_MIXER
    zox_system(SoundUpdateSystem, EcsPostUpdate, [none] Sound, [in] SoundData, [out] SoundDirty, [out] SDLSound)
    zox_system(PlaySoundSystem, EcsPreStore, [none] Sound, [out] TriggerSound, [in] SoundLength, [in] SDLSound)
#endif
zox_system_1(SoundDebugSystem, main_thread_pipeline, [none] Sound, [in] SoundData, [in] SoundDirty)
zoxel_end_module(Sounds)

#endif
