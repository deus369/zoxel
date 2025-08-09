zox_tag(Sound);
zoxc_byte(InstrumentType);
zoxc_byte(GenerateSound);        //! A state event for generating sounds
// remember: renamed PlaySound to TriggerSound temporarily, cause of windows.h conflict
zoxc_byte(TriggerSound);         //! A state event for playing sounds
zoxc_byte(ProcessSound);
zoxc_float(SoundFrequency);     //! The frequency of the generated sound
zoxc_float(SoundVolume);     //! The frequency of the generated sound
zoxc_int(SoundFrequencyIndex);     //! The frequency of the generated sound
zoxc_double(SoundLength);       //! The length of a sound
#include "sound_data.c"
#include "sound_data_ref.c"

void define_components_sounds(ecs_world_t *world) {
    zox_define_tag(Sound);;
    zox_define_component_byte(InstrumentType);;
    zox_define_component_byte(TriggerSound);;
    zox_define_component_byte(GenerateSound);;
    zox_define_component_byte(ProcessSound);;
    zox_define_component_double(SoundLength);;
    zox_define_component_float(SoundFrequency);;
    zox_define_component_float(SoundVolume);;
    zox_define_component_int(SoundFrequencyIndex);;
    // zox_define_memory_component(SoundData);
    zox_define_component_w_dest(SoundData);;
    zox_define_component(SoundDataRef);;
}