void PlaySoundSystem(ecs_iter_t *it) {
    int group = -1;  // -1 indicates all channels
    int channels_available = Mix_GroupAvailable(group);
    if (channels_available == 0) {
        // printf("No free channels available!\n");
        return;
    }
    ecs_world_t *world = it->world;
    TriggerSound *playSounds = ecs_field(it, TriggerSound, 2);
    const SoundLength *soundLengths = ecs_field(it, SoundLength, 3);
    const SDLSound *sdlSounds = ecs_field(it, SDLSound, 4);
    for (int i = 0; i < it->count; i++) {
        TriggerSound *triggerSound = &playSounds[i];
        if (triggerSound->value != 1) continue;
        const SDLSound *sdlSound = &sdlSounds[i];
        const SoundLength *soundLength = &soundLengths[i];
        if (sdlSound->value != NULL) {
            if (Mix_PlayChannel(-1, sdlSound->value, 0) == -1) {
                zoxel_log(" ! playing sound failed [%s]\n", Mix_GetError());
                zox_delete(it->entities[i])
            } else {
                if (soundLength->value == 0) {
                    zox_delete(it->entities[i])
                } else {
                    zox_set_only(it->entities[i], DestroyInTime, { soundLength->value })
                    // zoxel_log(" > playing sound [%lu]\n", it->entities[i]);
                }
            }
        }
        triggerSound->value = 0;
    }
} zox_declare_system(PlaySoundSystem)