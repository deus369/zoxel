#ifndef zox_mod_sounds
#define zox_mod_sounds

#include "_includes.c"
byte audio_enabled = 0;
#include "data/instrument_types.c"
#include "data/settings.c"
zox_declare_tag(Sound)
zox_component_byte(InstrumentType)
zox_component_byte(GenerateSound)        //! A state event for generating sounds
// remember: renamed PlaySound to TriggerSound temporarily, cause of windows.h conflict
zox_component_byte(TriggerSound)         //! A state event for playing sounds
zox_component_byte(SoundDirty)
zox_component_byte(ProcessSound)
zox_component_float(SoundFrequency)     //! The frequency of the generated sound
zox_component_float(SoundVolume)     //! The frequency of the generated sound
zox_component_int(SoundFrequencyIndex)     //! The frequency of the generated sound
zox_component_double(SoundLength)       //! The length of a sound
zox_memory_component(SoundData, float)   //! A sound has an array of bytes
#include "components/SDLSound.c"
#include "prefabs/prefabs.c"
#include "util/util.c"
#include "instruments/instruments.c"
#include "systems/systems.c"

void initialize_sounds(ecs_world_t *world) {
#ifndef zox_lib_sdl_mixer
    zox_log(" ! sdl sounds are disabled\n")
    return;
#endif
    if (initialize_sdl_mixer() == EXIT_SUCCESS) {
        load_files_sounds();
        audio_enabled = 1;
    } else {
        zox_log(" ! audio files not loaded")
    }
}

void dispose_sounds(ecs_world_t *world, void *ctx) {
    dispose_files_sounds();
    close_audio_sdl();
}

zox_begin_module(Sounds)
    zox_module_dispose(dispose_sounds)
    zox_define_tag(Sound)
    zox_define_component_byte(InstrumentType)
    zox_define_component_byte(SoundDirty)
    zox_define_component_byte(TriggerSound)
    zox_define_component_byte(GenerateSound)
    zox_define_component_byte(ProcessSound)
    zox_define_component_double(SoundLength)
    zox_define_component_float(SoundFrequency)
    zox_define_component_float(SoundVolume)
    zox_define_component_int(SoundFrequencyIndex)
    zox_define_memory_component(SoundData)
    #ifdef zox_lib_sdl_mixer
    zox_define_component(SDLSound)
    #endif
    define_systems_sounds(world);
    initialize_sounds(world);
    spawn_prefabs_sounds(world);
zoxel_end_module(Sounds)

#endif
