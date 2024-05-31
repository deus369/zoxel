ecs_entity_t prefab_sound;

ecs_entity_t spawn_prefab_sound(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_sound")
    zox_add_tag(e, Sound)
    zox_prefab_set(e, TriggerSound, { 1 })
    zox_prefab_set(e, SoundDirty, { 0 })
    // zox_prefab_set(e, SoundFrequency, { 146.83f });
    zox_prefab_set(e, SoundLength, { 0 })
    zox_prefab_add(e, SoundData)
    zox_prefab_set(e, SoundVolume, { 0.5f })
    zox_prefab_set(e, DestroyInTime, { 0 })
#ifdef SDL_MIXER
    zox_prefab_add(e, SDLSound)
#endif
    prefab_sound = e;
    return e;
}
