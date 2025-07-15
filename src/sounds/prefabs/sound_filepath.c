ecs_entity_t spawn_prefab_sound_filepath(ecs_world_t *world) {
    zox_prefab()
    zox_prefab_name("sound_filepath")
    zox_prefab_set(e, SoundVolume, { default_sound_volume })
    zox_prefab_add(e, SoundData)
    // zox_prefab_add(e, SoundDataRef)
    return e;
}

ecs_entity_t spawn_sound_filepath(ecs_world_t *world,
    const ecs_entity_t prefab,
    SoundData soundData,
    const float sound_length)
{
    if (!prefab) {
        zox_log_error("prefab_sound_filepath or sound_data is null")
        return 0;
    }
    zox_instance(prefab)
    zox_set(e, SoundData, {
        .value = soundData.value,
        .length = soundData.length
    })
    // zox_set(e, SDLSound, { *sound_data })
    /*zox_set(e, SoundDataRef, {
        .value = (float*) mix_chunk->abuf,
        .length = mix_chunk->alen
    })*/
    zox_set(e, SoundLength, { sound_length })
    return e;
}