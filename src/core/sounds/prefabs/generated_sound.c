ecs_entity_t prefab_generated_sound;

ecs_entity_t spawn_prefab_generated_sound(ecs_world_t *world) {
    zox_prefab_child(prefab_sound)
    zox_prefab_name("prefab_generated_sound")
    zox_prefab_set(e, SoundFrequency, { 0 })
    zox_prefab_set(e, InstrumentType, { 0 })
    zox_prefab_set(e, GenerateSound, { 1 })
    prefab_generated_sound = e;
    return e;
}

ecs_entity_t spawn_generated_sound(ecs_world_t *world, float frequency, float sound_length, unsigned char instrument_type) {
    zox_instance(prefab_generated_sound)
    zox_name("generated_sound")
    zox_set(e, SoundLength, { sound_length })
    zox_set(e, SoundFrequency, { frequency })
    zox_set(e, InstrumentType, { instrument_type })
    return e;
}
