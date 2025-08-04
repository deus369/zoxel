ecs_entity_t spawn_prefab_generated_sound(ecs_world_t *world, const ecs_entity_t prefab) {
    zox_prefab_child(prefab)
    zox_prefab_name("generated_sound")
    zox_prefab_set(e, SoundFrequency, { 0 })
    zox_prefab_set(e, InstrumentType, { 0 })
    zox_prefab_set(e, GenerateSound, { zox_sound_generate_trigger })
    return e;
}

ecs_entity_t spawn_sound_generated(ecs_world_t *world,
    const ecs_entity_t prefab,
    const byte instrument_type,
    const float frequency,
    const float sound_length,
    const float volume)
{
    if (!prefab) {
        zox_log_error("spawn_sound_generated prefab is null")
        return 0;
    }
    zox_instance(prefab_sound_generated)
    zox_name("generated_sound")
    zox_set(e, SoundLength, { sound_length })
    zox_set(e, SoundFrequency, { frequency })
    zox_set(e, InstrumentType, { instrument_type })
    zox_set(e, SoundVolume, { volume })

    uint length = (uint) (sound_sample_rate * sound_length);
    if (length > MAX_SOUND_DATA) {
        zox_log_error("length out of bounds [%i] of [%i]", length, MAX_SOUND_DATA);
        length = MAX_SOUND_DATA;
    }
    SoundData data = { 0 };
    data.value = soundpool_alloc();
    data.length = length;
    zox_set_ptr(e, SoundData, data);

    return e;
}