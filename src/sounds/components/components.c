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
#include "sdl_sound.c"

void define_components_sounds(ecs_world_t *world) {
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
}