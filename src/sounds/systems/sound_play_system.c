void SoundPlaySystem(ecs_iter_t *it) {
    const float volume = global_master_volume;
    int channels = get_channels_count();
    if (!audio_enabled || channels < 0) {
        // zox_log_error("> no mixer channels")
        return;
    }
    zox_sys_begin()
    zox_sys_in(TriggerSound)
    zox_sys_in(SoundData)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TriggerSound, triggerSound)
        zox_sys_i(SoundData, soundData)
        if (triggerSound->value == zox_sound_play_run) {
            if (soundData->value) {
                zox_log_sounds("+ playing [%s] (%i:%f)", zox_sys_e_name, channels, volume)
                sdl_play_sound(soundData->value, soundData->length, channels, volume);
            }
        }
    }
} zox_declare_system(SoundPlaySystem)

void SoundPlayRefSystem(ecs_iter_t *it) {
    int channels = get_channels_count();
    if (!audio_enabled || channels < 0) {
        // zox_log_error("> no mixer channels")
        return;
    }
    zox_sys_begin()
    zox_sys_in(TriggerSound)
    zox_sys_in(SoundDataRef)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TriggerSound, triggerSound)
        zox_sys_i(SoundDataRef, soundDataRef)
        if (triggerSound->value == zox_sound_play_run) {
            if (soundDataRef->value) {
                zox_log("+ playing sound ref")
                sdl_play_sound(soundDataRef->value, soundDataRef->length, channels, global_master_volume);
            }
        }
    }
} zox_declare_system(SoundPlayRefSystem)