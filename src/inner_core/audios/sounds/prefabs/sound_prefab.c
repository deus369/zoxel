ecs_entity_t prefab_sound;

ecs_entity_t spawn_prefab_sound(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_prefab(world, "prefab_sound");
    set_unique_entity_name(world, e, "prefab_sound");
    zoxel_add_tag(world, e, Sound);
    zoxel_set(world, e, PlaySound, { 1 });
    zoxel_set(world, e, SDLSound, { NULL });
    // zoxel_set(world, e, SoundFrequency, { 146.83f });
    ecs_defer_end(world);
    prefab_sound = e;
    #ifdef zoxel_debug_prefabs
    zoxel_log("spawn_prefab sound [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_sound(ecs_world_t *world)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_sound);
    set_unique_entity_name(world, e, "sound");
    ecs_set(world, e, SDLSound, { Mix_LoadWAV(sound_file_names[0]) }); //  sounds[0] });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned sound [%lu]\n", (long int) e);
    #endif
    return e;
}

ecs_entity_t spawn_generated_sound(ecs_world_t *world,
    float frequency, float sound_length, unsigned char instrument_type)
{
    ecs_defer_begin(world);
    ecs_entity_t e = ecs_new_w_pair(world, EcsIsA, prefab_sound);
    set_unique_entity_name(world, e, "sound");
    zoxel_set(world, e, GenerateSound, { 1 });
    zoxel_add(world, e, SoundData);
    zoxel_set(world, e, SoundFrequency, { frequency });
    zoxel_set(world, e, SoundLength, { sound_length });
    zoxel_set(world, e, InstrumentType, { instrument_type });
    zoxel_set(world, e, SoundDirty, { 0 });
    ecs_defer_end(world);
    #ifdef zoxel_debug_spawns
    zoxel_log("Spawned generated_sound [%lu]\n", (long int) e);
    #endif
    return e;
}