#include "sound_process_system.c"
#include "sound_generate_system.c"
#include "sound_play_system.c"
#include "sound_play_ref_system.c"
#include "sound_debug_system.c"
zox_increment_system_with_reset(TriggerSound, zox_sound_play_end)
zox_increment_system_with_reset(ProcessSound, zox_sound_process_end)
zox_increment_system_with_reset(GenerateSound, zox_sound_generate_end)

void define_systems_sounds(ecs_world_t *world) {
    zox_define_increment_system(TriggerSound, [none] Sound)
    zox_define_increment_system(ProcessSound, [none] Sound)
    zox_define_increment_system(GenerateSound, [none] Sound)
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
        [in] SoundData,
        [out] TriggerSound,
        [none] Sound)
    zox_system(SoundPlaySystem, EcsOnUpdate,
        [in] TriggerSound,
        [in] SoundData,
        [out] sdl.SDLMixChunk,
        [none] Sound)
    zox_system(SoundPlayRefSystem, EcsOnUpdate,
        [in] TriggerSound,
        [in] SoundDataRef,
        [out] sdl.SDLMixChunk,
        [none] Sound)
    zox_system_1(SoundDebugSystem, zox_pip_mainthread,
        [in] SoundData,
        [in] TriggerSound,
        [none] Sound)
}