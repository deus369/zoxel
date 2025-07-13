void SoundPlayRefSystem(ecs_iter_t *it) {
    int channels = get_channels_count();
    if (!audio_enabled || channels < 0) {
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
                sdl_play_sound(soundDataRef->value, soundDataRef->length, channels, mixer_audio_volume);
            }
        }
    }
} zox_declare_system(SoundPlayRefSystem)