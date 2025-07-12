#include "sound_process_system.c"
#include "sound_generate_system.c"
#include "sound_debug_system.c"
#ifdef zox_lib_sdl_mixer
    #include "sound_play_system.c"
    #include "sound_update_system.c"
#endif
zox_increment_system_with_reset(TriggerSound, zox_sound_play_end)
zox_increment_system_with_reset(ProcessSound, zox_sound_process_end)
zox_increment_system_with_reset(GenerateSound, zox_sound_generate_end)

void define_systems_sounds(ecs_world_t *world) {
    zox_define_increment_system(TriggerSound, EcsOnLoad, [none] Sound)
    zox_define_increment_system(ProcessSound, EcsOnLoad, [none] Sound)
    zox_define_increment_system(GenerateSound, EcsOnLoad, [none] Sound)
    zox_system(SoundProcessSystem, EcsOnUpdate,
        [in] ProcessSound,
        [in] SoundData,
        [in] SoundVolume,
        [in] SoundFrequency,
        [out] TriggerSound,
        [None] Sound)
    zox_system(SoundGenerateSystem, EcsOnUpdate,
        [in] InstrumentType,
        [in] SoundLength,
        [in] SoundFrequency,
        [in] SoundVolume,
        [in] GenerateSound,
        [out] TriggerSound,
        [out] SoundData,
        [none] Sound)
    zox_system(SoundPlaySystem, EcsOnUpdate,
        [in] TriggerSound,
        [in] SoundData,
        [none] Sound)
    zox_system(SoundPlayRefSystem, EcsOnUpdate,
        [in] TriggerSound,
        [in] SoundDataRef,
        [none] Sound)
    zox_system_1(SoundDebugSystem, zox_pip_mainthread,
        [none] Sound,
        [in] SoundData,
        [in] SoundDirty)
}