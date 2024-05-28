void PlaySoundSystem(ecs_iter_t *it) {
#ifdef zox_disable_play_sounds
    return;
#endif
    int channel_available = Mix_GroupAvailable(-1); // -1 indicates all channels
    if (channel_available == -1) return;
    zox_iter_world()
    zox_field_in(SoundLength, soundLengths, 1)
    zox_field_out(TriggerSound, triggerSounds, 2)
    zox_field_out(SDLSound, sdlSounds, 3)
    for (int i = 0; i < it->count; i++) {
        zox_field_i_out(TriggerSound, triggerSounds, triggerSound)
        if (triggerSound->value != 1) continue;
        zox_field_e()
        zox_field_i(SoundLength, soundLengths, soundLength)
        zox_field_o(SDLSound, sdlSounds, sdlSound)
        if (soundLength->value && Mix_PlayChannel(channel_available, &sdlSound->value, 0) != -1) {
            zox_set(e, DestroyInTime, { soundLength->value + 1.0 })
        } else {
            if (soundLength->value) zox_log(" ! playing sound failed [%s]\n", Mix_GetError())
            zox_delete(e)
        }
        triggerSound->value = 0;
    }
} zox_declare_system(PlaySoundSystem)
