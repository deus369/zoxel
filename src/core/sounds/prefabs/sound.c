ecs_entity_t prefab_sound;

ecs_entity_t spawn_prefab_sound(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_sound")
    zox_add_tag(e, Sound)
    zox_prefab_set(e, TriggerSound, { 1 })
    zox_prefab_set(e, SoundDirty, { 0 })
    // zox_prefab_set(e, SoundFrequency, { 146.83f });
    zox_prefab_set(e, SoundLength, { 0 })
    zox_prefab_set(e, SoundData, { 0, NULL })
#ifdef SDL_MIXER
    zox_prefab_set(e, SDLSound, { NULL })
#endif
    zox_prefab_set(e, SoundVolume, { 0.5f })
    zox_prefab_set(e, DestroyInTime, { 0 })
    prefab_sound = e;
#ifdef zoxel_debug_prefabs
    zox_log(" > spawn_prefab sound [%lu]\n", e)
#endif
    return e;
}

/*ecs_entity_t spawn_sound(ecs_world_t *world) {
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_sound);
    set_unique_entity_name(world, e, "sound");
    zox_set(e, SDLSound, { Mix_LoadWAV(sound_file_names[0]) }); //  sounds[0] });
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned sound [%lu]\n", (long int) e);
    #endif
    return e;
}*/
