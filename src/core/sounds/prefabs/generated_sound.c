ecs_entity_t prefab_generated_sound;

ecs_entity_t spawn_prefab_generated_sound(ecs_world_t *world) {
    zox_prefab_child(prefab_sound)
    zox_prefab_name("prefab_generated_sound")
    zox_prefab_set(e, SoundData, { 0, NULL })
    zox_prefab_set(e, SoundFrequency, { 0 })
    zox_prefab_set(e, InstrumentType, { 0 })
    zox_prefab_set(e, GenerateSound, { 1 })
    prefab_generated_sound = e;
    #ifdef zoxel_debug_prefabs
        zoxel_log(" > spawn_prefab generated_sound [%lu].\n", (long int) (e));
    #endif
    return e;
}

ecs_entity_t spawn_generated_sound(ecs_world_t *world, float frequency, float sound_length, unsigned char instrument_type) {
    zox_instance(prefab_generated_sound)
    zox_name("generated_sound")
    zox_set(e, SoundLength, { sound_length })
    zox_set(e, SoundFrequency, { frequency })
    zox_set(e, InstrumentType, { instrument_type })
    #ifdef zoxel_debug_spawns
        zoxel_log(" > spawned generated_sound [%lu]\n", (long int) e);
    #endif
    return e;
}