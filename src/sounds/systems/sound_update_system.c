/*void SoundUpdateSystem(ecs_iter_t *it) {
    if (!audio_enabled) {
      return;
    }
    zox_sys_begin()
    zox_sys_in(SoundData)
    zox_sys_out(SoundDirty)
    zox_sys_out(SDLSound)
    for (int i = 0; i < it->count; i++) {
        zox_sys_i(SoundData, soundData)
        zox_sys_o(SoundDirty, soundDirty)
        zox_sys_o(SDLSound, sdlSound)
        if (!soundDirty->value || !soundData->value) {
            continue;
        }
        const int memory_length = soundData->length * sizeof(float);
        sdlSound->value = (Mix_Chunk) {
          .volume = global_master_volume,
          .alen = memory_length,
          .abuf = (void*) soundData->value
        };
        soundDirty->value = 0;
        zox_log_sounds("  -> sdl mix sound updated [%f]", zox_current_time)
    }
} zox_declare_system(SoundUpdateSystem)*/

/*void SoundPlaySystem(ecs_iter_t *it) {
    if (!audio_enabled) {
        return;
    }
    int channels = get_channels_count();
    if (channels < 0) {
        return;
    }
    zox_sys_world()
    zox_sys_begin()
    zox_sys_in(SoundLength)
    zox_sys_in(TriggerSound)
    zox_sys_in(SDLSound)
    zox_sys_out(DestroyInTime)
    for (int i = 0; i < it->count; i++) {
        zox_sys_e()
        zox_sys_i(SoundLength, soundLength)
        zox_sys_i(TriggerSound, triggerSound)
        zox_sys_i(SDLSound, sdlSound)
        zox_sys_o(DestroyInTime, destroyInTime)
        if (triggerSound->value != zox_sound_play_run) {
            continue;
        }
        if (soundLength->value) {
#ifdef zox_lib_sdl_mixer
            if (!sdlSound->value.abuf) {
                zox_log_error("invalid [sdlSound->value.abuf] for %s", zox_get_name(e))
            } else if (Mix_PlayChannel(channels, &sdlSound->value, 0) == -1) {
                zox_log_error(" ! failed to play sound: %s", Mix_GetError())
            }
#endif
        }
        destroyInTime->value = soundLength->value + sound_play_death_delay; // 16.0;
        zox_log_sounds("+ play at [%f]", zox_current_time)
    }
} zox_declare_system(SoundPlaySystem)*/