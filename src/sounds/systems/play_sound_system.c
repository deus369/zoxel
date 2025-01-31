void PlaySoundSystem(ecs_iter_t *it) {
    if (!audio_enabled) return;
#ifdef zox_disable_play_sounds
    return;
#endif
#ifndef zox_lib_sdl_mixer
    int channel_available = -1;
#else
    int channel_available = Mix_GroupAvailable(-1);
#endif
    if (channel_available < 0) return;
    // zox_iter_world()
    zox_field_in(SoundLength, soundLengths, 1)
    zox_field_out(TriggerSound, triggerSounds, 2)
    zox_field_out(SDLSound, sdlSounds, 3)
    zox_field_out(DestroyInTime, destroyInTimes, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TriggerSound, triggerSounds, triggerSound)
        if (triggerSound->value != 1) continue;
        // generating
        zox_field_e()
        /*if (zox_has(e, GenerateSound)) {
            const unsigned char generating = zox_get_value(e, GenerateSound)
            if (generating) continue;
        }*/
        if (zox_has(e, GenerateSound) && zox_gett_value(e, GenerateSound)) continue;
        if (zox_has(e, ProcessSound) && zox_gett_value(e, ProcessSound)) continue;
        zox_field_i(SoundLength, soundLengths, soundLength)
        zox_field_o(SDLSound, sdlSounds, sdlSound)
        zox_field_o(DestroyInTime, destroyInTimes, destroyInTime)
        destroyInTime->value = soundLength->value + 16.0;
        if (soundLength->value) {
#ifdef zox_lib_sdl_mixer
            if (Mix_PlayChannel(channel_available, &sdlSound->value, 0) == -1) {
                zox_log(" ! failed to play sound: %s\n", Mix_GetError())
                // zox_log(" ! error playing sound\n")
            }
#endif
        }
        triggerSound->value = 0;
        // zox_log(" + play at [%f]\n", zox_current_time)
    }
} zox_declare_system(PlaySoundSystem)

//zox_set(e, DestroyInTime, { soundLength->value + 1.0 })
/*else {
    if (soundLength->value) zox_log(" ! playing sound failed [%s]\n", Mix_GetError())
    zox_delete(e)
}*/
