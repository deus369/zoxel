void SoundPlaySystem(ecs_iter_t *it) {
    if (!audio_enabled) {
        return;
    }
#ifdef zox_disable_play_sounds
    return;
#endif
#ifndef zox_lib_sdl_mixer
    int channel_available = -1;
#else
    int channel_available = Mix_GroupAvailable(-1);
#endif
    if (channel_available < 0) {
        return;
    }
    zox_field_world()
    zox_field_in(SoundLength, soundLengths, 1)
    zox_field_out(SDLSound, sdlSounds, 2)
    zox_field_out(TriggerSound, triggerSounds, 3)
    zox_field_out(DestroyInTime, destroyInTimes, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_e()
        zox_field_i(SoundLength, soundLengths, soundLength)
        zox_field_o(TriggerSound, triggerSounds, triggerSound)
        zox_field_o(DestroyInTime, destroyInTimes, destroyInTime)
        zox_field_o(SDLSound, sdlSounds, sdlSound)
        if (!triggerSound->value) {
            continue;
        }
        if (zox_has(e, SoundDirty) && zox_gett_value(e, SoundDirty)) {
            continue;
        }
        if (zox_has(e, GenerateSound) && zox_gett_value(e, GenerateSound)) {
            continue;
        }
        if (zox_has(e, ProcessSound) && zox_gett_value(e, ProcessSound)) {
            continue;
        }
        if (soundLength->value) {
#ifdef zox_lib_sdl_mixer
            if (!sdlSound->value.abuf) {
                zox_log_error("invalid [sdlSound->value.abuf] for %s", zox_get_name(e))
            } else if (Mix_PlayChannel(channel_available, &sdlSound->value, 0) == -1) {
                zox_log_error(" ! failed to play sound: %s", Mix_GetError())
            }
#endif
        }
        destroyInTime->value = soundLength->value + sound_play_death_delay; // 16.0;
        triggerSound->value = 0;
        zox_log_sounds("+ play at [%f]", zox_current_time)
    }
} zox_declare_system(SoundPlaySystem)