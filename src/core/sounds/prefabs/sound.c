ecs_entity_t prefab_sound;
ecs_entity_t prefab_generated_sound;

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
    // zox_set(e, SoundFrequency, { 146.83f });
    ecs_defer_end(world);
    prefab_sound = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab sound [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_prefab_generated_sound(ecs_world_t *world) {
    ecs_defer_begin(world);
    zox_prefab_child(prefab_sound)
    zox_name("prefab_generated_sound")
    zox_set(e, SoundData, { 0, NULL })
    zox_set(e, SoundFrequency, { 0 })
    zox_set(e, InstrumentType, { 0 })
    zox_set(e, GenerateSound, { 1 })
    ecs_defer_end(world);
    prefab_generated_sound = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab generated_sound [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_generated_sound(ecs_world_t *world, float frequency, float sound_length, unsigned char instrument_type) {
    //ecs_defer_begin(world);
    zox_instance(prefab_generated_sound)
    zox_name("generated_sound")
    zox_set_only(e, SoundLength, { sound_length })
    zox_set_only(e, SoundFrequency, { frequency })
    zox_set_only(e, InstrumentType, { instrument_type })
    // zox_set_only(e, GenerateSound, { 1 })
    // zox_set_only(e, SoundData, { 0, NULL })
    //ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned generated_sound [%lu]\n", (long int) e);
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