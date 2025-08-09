void SoundPlaySystem(ecs_iter_t *it) {
    int channel = get_channels_count();
    if (!audio_enabled || channel < 0 || nosounds) {
        return;
    }
    if (zox_current_time <= 1) {
        // zox_log("waiting: %f", zox_current_time);
        return;
    }
    zox_sys_begin()
    zox_sys_in(TriggerSound)
    zox_sys_in(SoundData)
    zox_sys_out(SDLMixChunk)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(TriggerSound, triggerSound)
        zox_sys_i(SoundData, soundData)
        zox_sys_o(SDLMixChunk, chunk)
        if (triggerSound->value == zox_sound_play_run) {
            if (soundData->value) {
                zox_log_sounds("+ playing [%s] (%i:%f)", zox_sys_e_name, channel, mixer_audio_volume)
                sdl_play_sound(
                    chunk,
                    soundData->value,
                    soundData->length,
                    mixer_audio_volume,
                    channel);
            } else {
                zox_log_error("Invalid SoundData, triggered.");
            }
        }
    }
} zoxd_system(SoundPlaySystem)