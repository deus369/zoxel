#ifndef zox_sounds
#define zox_sounds

int global_master_volume = 64;
const int global_master_volume_max = 128;
const int global_master_volume_increment = 16;
#include "util/import_sdl_mixer.c"
#include "settings/settings.c"
zox_declare_tag(Sound)
zox_declare_tag(ClickMakeSound)
zox_component_byte(InstrumentType)
zox_component_byte(GenerateSound)        //! A state event for generating sounds
// remember: renamed PlaySound to TriggerSound temporarily, cause of windows.h conflict
zox_component_byte(TriggerSound)         //! A state event for playing sounds
zox_component_byte(SoundDirty)
zox_component_float(SoundFrequency)     //! The frequency of the generated sound
zox_component_float(SoundVolume)     //! The frequency of the generated sound
zox_component_double(SoundLength)       //! The length of a sound
zox_memory_component(SoundData, float)   //! A sound has an array of bytes
#include "components/SDLSound.c"
#include "prefabs/sound.c"
#include "prefabs/generated_sound.c"
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
#ifdef SDL_MIXER
#include "systems/play_sound_system.c"
#include "systems/sound_update_system.c"
#endif
#include "systems/click_sound_system.c"

void initialize_sounds(ecs_world_t *world) {
#ifndef SDL_MIXER
    zox_log(" ! sdl sounds are disabled\n")
#endif
    load_files_sounds();
}

void dispose_sounds(ecs_world_t *world, void *ctx) {
    dispose_sound_files();
    close_audio_sdl();
}

void spawn_prefabs_sounds(ecs_world_t *world) {
    spawn_prefab_sound(world);
    spawn_prefab_generated_sound(world);
}

zox_begin_module(Sounds)
zox_module_dispose(dispose_sounds)
zox_define_tag(Sound)
zox_define_tag(ClickMakeSound)
zox_define_component_byte(InstrumentType)
zox_define_component_byte(SoundDirty)
zox_define_component_byte(TriggerSound)
zox_define_component_byte(GenerateSound)
zox_define_component_double(SoundLength)
zox_define_component_float(SoundFrequency)
zox_define_component_float(SoundVolume)
zox_define_memory_component(SoundData)
#ifdef SDL_MIXER
// zox_define_component_w_dest(SDLSound)
zox_define_component(SDLSound)
#endif
zox_system(SoundGenerateSystem, EcsOnUpdate, [none] Sound, [out] GenerateSound, [out] SoundData, [out] SoundDirty, [in] SoundLength, [in] SoundFrequency, [in] SoundVolume, [in] InstrumentType)
#ifdef SDL_MIXER
zox_system(SoundUpdateSystem, EcsPostUpdate, [none] Sound, [in] SoundData, [out] SoundDirty, [out] SDLSound)
zox_system(PlaySoundSystem, zox_pipelines_pre_render, [in] SoundLength, [out] TriggerSound, [out] SDLSound, [none] Sound)
#endif
zox_system_1(SoundDebugSystem, main_thread_pipeline, [none] Sound, [in] SoundData, [in] SoundDirty)
zox_system_1(ClickSoundSystem, main_thread_pipeline, [in] ClickState, [none] ClickMakeSound)
load_audio_sdl();
initialize_sounds(world);
spawn_prefabs_sounds(world);
zoxel_end_module(Sounds)

#endif
