ecs_entity_t prefab_sound;

ecs_entity_t spawn_prefab_sound(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab()
    zox_name("prefab_sound")
    zox_add_tag(e, Sound)
    zox_set(e, SoundLength, { 0 })
    zox_set(e, SDLSound, { NULL })
    zox_set(e, DestroyInTime, { 0 })
    zox_set(e, TriggerSound, { 1 })
    zox_set(e, SoundDirty, { 0 })
    zox_set(e, SoundVolume, { 0.5f })
    // zox_set(e, SoundFrequency, { 146.83f });
    ecs_defer_end(world);
    prefab_sound = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab sound [%lu].\n", (long int) (e));
    #endif
    return e;
}

/*ecs_entity_t spawn_sound(ecs_world_t *world) {
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_sound);
    set_unique_entity_name(world, e, "sound");
    ecs_set(world, e, SDLSound, { Mix_LoadWAV(sound_file_names[0]) }); //  sounds[0] });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned sound [%lu]\n", (long int) e);
    #endif
    return e;
}*/