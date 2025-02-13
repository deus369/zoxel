ecs_entity_t spawn_prefab_generated_sound(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("prefab_generated_sound")
    zox_prefab_set(e, SoundFrequency, { 0 })
    zox_prefab_set(e, InstrumentType, { 0 })
    zox_prefab_set(e, GenerateSound, { 1 })
    return e;
}

ecs_entity_t spawn_sound_generated(ecs_world_t *world, const byte instrument_type, const float frequency, const float sound_length, const float sound_volume) {
    zox_instance(prefab_sound_generated)
    zox_name("generated_sound")
    zox_set(e, SoundLength, { sound_length })
    zox_set(e, SoundFrequency, { frequency })
    zox_set(e, InstrumentType, { instrument_type })
    zox_set(e, SoundVolume, { sound_volume })
    return e;
}
