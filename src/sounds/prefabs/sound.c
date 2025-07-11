ecs_entity_t spawn_prefab_sound(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_sound")
    zox_add_tag(e, Sound)
    zox_prefab_set(e, TriggerSound, { 1 })
    zox_prefab_set(e, SoundDirty, { 0 })
    zox_prefab_set(e, ProcessSound, { 0 })
    // zox_prefab_set(e, SoundFrequency, { 146.83f });
    zox_prefab_set(e, SoundLength, { 0 })
    zox_prefab_set(e, SoundVolume, { default_sound_volume })
    zox_prefab_set(e, DestroyInTime, { sound_play_death_delay * 2 })
    zox_prefab_set(e, SoundFrequency, { 440 })
    zox_prefab_add(e, SoundData)
#ifdef zox_lib_sdl_mixer
    zox_prefab_add(e, SDLSound)
#endif
    return e;
}