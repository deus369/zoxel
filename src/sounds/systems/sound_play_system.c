void SoundPlaySystem(ecs_iter_t *it) {
    int channels = get_channels_count();
    if (!audio_enabled || channels < 0 || nosounds) {
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
                zox_log_sounds("+ playing [%s] (%i:%f)", zox_sys_e_name, channels, mixer_audio_volume)
                sdl_play_sound(
                    soundData->value,
                    soundData->length,
                    channels,
                    mixer_audio_volume);
            }
        }
    }
} zox_declare_system(SoundPlaySystem)