ecs_entity_t spawn_prefab_sound(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("sound")
    zox_add_tag(e, Sound)
    zox_prefab_set(e, SoundLength, { 0 })
    zox_prefab_set(e, SoundFrequency, { 440 })
    zox_prefab_set(e, SoundVolume, { default_sound_volume })
    zox_prefab_set(e, TriggerSound, { zox_sound_play_none })
    zox_prefab_set(e, ProcessSound, { zox_sound_process_none })
    zox_prefab_set(e, DestroyInTime, { sound_play_death_delay })
    zox_prefab_set(e, SoundData, { .length = 0 }) // 0, NULL
    if (!headless) {
        zox_prefab_set(e, SDLMixChunk, { NULL });
    }
    return e;
}