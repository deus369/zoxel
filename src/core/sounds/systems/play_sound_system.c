void PlaySoundSystem(ecs_iter_t *it) {
#ifdef zox_disable_play_sounds
    return;
#endif
    int channel_available = Mix_GroupAvailable(-1); // -1 indicates all channels
    if (channel_available == -1) return;
    zox_iter_world()
    const SoundLength *soundLengths = ecs_field(it, SoundLength, 3);
    const SDLSound *sdlSounds = ecs_field(it, SDLSound, 4);
    TriggerSound *playSounds = ecs_field(it, TriggerSound, 2);
    for (int i = 0; i < it->count; i++) {
        TriggerSound *triggerSound = &playSounds[i];
        if (triggerSound->value != 1) continue;
        const ecs_entity_t e = it->entities[i];
        const SDLSound *sdlSound = &sdlSounds[i];
        const SoundLength *soundLength = &soundLengths[i];
        if (sdlSound->value != NULL) {
            if (soundLength->value && Mix_PlayChannel(channel_available, sdlSound->value, 0) != -1) {
                zox_set(e, DestroyInTime, { soundLength->value + 1.0 })
            } else {
                if (soundLength->value) zox_log(" ! playing sound failed [%s]\n", Mix_GetError())
                zox_delete(e)
            }
        }
        triggerSound->value = 0;
    }
} zox_declare_system(PlaySoundSystem)
