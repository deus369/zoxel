ecs_entity_t spawn_prefab_sound_filepath(ecs_world_t *world) {
    zox_prefab();
    zox_prefab_name("sound_filepath");
    zox_prefab_set(e, SoundVolume, { default_sound_volume });
    zox_prefab_add(e, SoundData);
    return e;
}

ecs_entity_t spawn_sound_filepath(ecs_world_t *world,
    const ecs_entity_t prefab,
    const float* value,
    int length,
    const float sound_length)
{
    if (!prefab) {
        zox_log_error("prefab_sound_filepath or sound_data is null")
        return 0;
    }
    zox_instance(prefab);
    zox_set(e, SoundLength, { sound_length });

    if (length > MAX_SOUND_DATA) {
        zox_log_error("length out of bounds [%i] of [%i]", length, MAX_SOUND_DATA);
        length = MAX_SOUND_DATA;
    }
    SoundData data = { 0 };
    data.value = soundpool_alloc();
    data.length = length;
    memcpy(data.value, value, length * sizeof(float));
    zox_set_ptr(e, SoundData, data);

    return e;
}