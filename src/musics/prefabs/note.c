ecs_entity_t spawn_prefab_note(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("prefab_note")
    zox_add_tag(e, Note)
    zox_prefab_set(e, InstrumentType, { instrument_piano })
    zox_prefab_set(e, SoundFrequencyIndex, { 32 })
    zox_prefab_set(e, SoundVolume, { 1 })
    zox_prefab_set(e, SoundLength, { 0 })
    return e;
}

ecs_entity_t spawn_note(ecs_world_t *world,
    const ecs_entity_t prefab,
    const int note,
    const byte instrument,
    const float length,
    const float volume)
{
    zox_instance(prefab)
    zox_name("note")
    zox_set(e, InstrumentType, { instrument })
    zox_set(e, SoundFrequencyIndex, { note })
    zox_set(e, SoundLength, { length })
    zox_set(e, SoundVolume, { volume })
    return e;
}