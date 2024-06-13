void PlaySoundSystem(ecs_iter_t *it) {
#ifdef zox_disable_play_sounds
    return;
#endif
#ifndef zox_lib_sdl_mixer
    int channel_available = 0;
#else
    int channel_available = Mix_GroupAvailable(-1); // -1 indicates all channels
    if (channel_available == -1) return;
#endif
    // zox_iter_world()
    zox_field_in(SoundLength, soundLengths, 1)
    zox_field_out(TriggerSound, triggerSounds, 2)
    zox_field_out(SDLSound, sdlSounds, 3)
    zox_field_out(DestroyInTime, destroyInTimes, 4)
    for (int i = 0; i < it->count; i++) {
        zox_field_o(TriggerSound, triggerSounds, triggerSound)
        if (triggerSound->value != 1) continue;
        zox_field_i(SoundLength, soundLengths, soundLength)
        zox_field_o(SDLSound, sdlSounds, sdlSound)
        zox_field_o(DestroyInTime, destroyInTimes, destroyInTime)
        destroyInTime->value = soundLength->value + 1.0;
        if (soundLength->value) {
#ifdef zox_lib_sdl_mixer
            Mix_PlayChannel(channel_available, &sdlSound->value, 0);// != -1)
#endif
        }
        triggerSound->value = 0;
    }
} zox_declare_system(PlaySoundSystem)

//zox_set(e, DestroyInTime, { soundLength->value + 1.0 })
/*else {
    if (soundLength->value) zox_log(" ! playing sound failed [%s]\n", Mix_GetError())
    zox_delete(e)
}*/
