#include "sound_process_system.c"
#include "sound_generate_system.c"
#include "sound_debug_system.c"
#ifdef zox_lib_sdl_mixer
    #include "sound_play_system.c"
    #include "sound_update_system.c"
#endif

void define_systems_sounds(ecs_world_t *world) {
    zox_system(SoundProcessSystem, EcsOnUpdate, [in] SoundFrequency, [in] SoundData, [out] ProcessSound, [out] TriggerSound, [out] SoundDirty, [None] Sound)
    zox_system(SoundGenerateSystem, EcsOnUpdate, [in] InstrumentType, [in] SoundLength, [in] SoundFrequency, [in] SoundVolume, [out] GenerateSound, [out] SoundData, [out] SoundDirty, [none] Sound)
    #ifdef zox_lib_sdl_mixer
        zox_system(SoundUpdateSystem, EcsPostUpdate, [none] Sound, [in] SoundData, [out] SoundDirty, [out] SDLSound)
        zox_system(SoundPlaySystem, EcsPostUpdate, [in] SoundLength, [out] SDLSound, [out] TriggerSound, [out] timing.DestroyInTime, [none] Sound)
    #endif
    zox_system_1(SoundDebugSystem, zox_pip_mainthread, [none] Sound, [in] SoundData, [in] SoundDirty)
}