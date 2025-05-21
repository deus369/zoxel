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
        zox_field_o(TriggerSound, triggerSounds, triggerSound)
        if (!triggerSound->value) {
            continue;
        }
        zox_field_e()
        if (zox_has(e, SoundDirty) && zox_gett_value(e, SoundDirty)) {
            continue;
        }
        if (zox_has(e, GenerateSound) && zox_gett_value(e, GenerateSound)) {
            continue;
        }
        if (zox_has(e, ProcessSound) && zox_gett_value(e, ProcessSound)) {
            continue;
        }
        zox_field_i(SoundLength, soundLengths, soundLength)
        if (soundLength->value) {
#ifdef zox_lib_sdl_mixer
            zox_field_o(SDLSound, sdlSounds, sdlSound)
            if (!sdlSound->value.abuf) {
                // zox_log(" ! SdlSound value is invalid.\n")
            } else if (Mix_PlayChannel(channel_available, &sdlSound->value, 0) == -1) {
                zox_log(" ! failed to play sound: %s\n", Mix_GetError())
                // zox_log(" ! error playing sound\n")
            }
#endif
        }
        zox_field_o(DestroyInTime, destroyInTimes, destroyInTime)
        destroyInTime->value = soundLength->value + sound_play_death_delay; // 16.0;
        triggerSound->value = 0;
        // zox_log(" + play at [%f]\n", zox_current_time)
    }
} zox_declare_system(SoundPlaySystem)

//zox_set(e, DestroyInTime, { soundLength->value + 1.0 })
/*else {
    if (soundLength->value) zox_log(" ! playing sound failed [%s]\n", Mix_GetError())
    zox_delete(e)
}*/
