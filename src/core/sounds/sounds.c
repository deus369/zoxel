#ifndef zox_mod_sounds
#define zox_mod_sounds

int global_master_volume = 64;
const int global_master_volume_max = 128;
const int global_master_volume_increment = 16;
#include "util/import_sdl_mixer.c"
#include "data/instrument_types.c"
#include "settings/settings.c"
zox_declare_tag(Sound)
zox_component_byte(InstrumentType)
zox_component_byte(GenerateSound)        //! A state event for generating sounds
// remember: renamed PlaySound to TriggerSound temporarily, cause of windows.h conflict
zox_component_byte(TriggerSound)         //! A state event for playing sounds
zox_component_byte(SoundDirty)
zox_component_float(SoundFrequency)     //! The frequency of the generated sound
zox_component_float(SoundVolume)     //! The frequency of the generated sound
zox_component_int(SoundFrequencyIndex)     //! The frequency of the generated sound
zox_component_double(SoundLength)       //! The length of a sound
zox_memory_component(SoundData, float)   //! A sound has an array of bytes
#include "components/SDLSound.c"
#include "prefabs/prefabs.c"
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
#include "systems/sound_generate_system.c"
#include "systems/sound_debug_system.c"
#ifdef zox_lib_sdl_mixer
#include "systems/play_sound_system.c"
#include "systems/sound_update_system.c"
#endif

void initialize_sounds(ecs_world_t *world) {
#ifndef zox_lib_sdl_mixer
    zox_log(" ! sdl sounds are disabled\n")
    return;
#endif
    initialize_sdl_mixer();
    load_files_sounds();
}

void dispose_sounds(ecs_world_t *world, void *ctx) {
    dispose_sound_files();
    close_audio_sdl();
}

zox_begin_module(Sounds)
zox_module_dispose(dispose_sounds)
zox_define_tag(Sound)
zox_define_component_byte(InstrumentType)
zox_define_component_byte(SoundDirty)
zox_define_component_byte(TriggerSound)
zox_define_component_byte(GenerateSound)
zox_define_component_double(SoundLength)
zox_define_component_float(SoundFrequency)
zox_define_component_float(SoundVolume)
zox_define_component_int(SoundFrequencyIndex)
zox_define_memory_component(SoundData)
#ifdef zox_lib_sdl_mixer
zox_define_component(SDLSound)
#endif
zox_system(SoundGenerateSystem, EcsOnUpdate, [none] Sound, [out] GenerateSound, [out] SoundData, [out] SoundDirty, [in] SoundLength, [in] SoundFrequency, [in] SoundVolume, [in] InstrumentType)
#ifdef zox_lib_sdl_mixer
zox_system(SoundUpdateSystem, EcsPostUpdate, [none] Sound, [in] SoundData, [out] SoundDirty, [out] SDLSound)
zox_system(PlaySoundSystem, zox_pipelines_pre_render, [in] SoundLength, [out] TriggerSound, [out] SDLSound, [out] DestroyInTime, [none] Sound)
#endif
zox_system_1(SoundDebugSystem, zox_pip_mainthread, [none] Sound, [in] SoundData, [in] SoundDirty)
initialize_sounds(world);
spawn_prefabs_sounds(world);
zoxel_end_module(Sounds)

#endif
