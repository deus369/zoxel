ecs_entity_t spawn_prefab_sound_file_instance(ecs_world_t *world,
    const ecs_entity_t prefab)
{
    zox_prefab_child(prefab)
    zox_prefab_name("sound_file_instance")
    zox_prefab_set(e, ProcessSound, { zox_sound_process_trigger })
    return e;
}

// clones the files sound data for processing to a new frequency
ecs_entity_t spawn_sound_from_file(ecs_world_t *world,
    const ecs_entity_t prefab,
    const ecs_entity_t src,
    float frequency,
    float volume)
{
    if (!src) {
        zox_log_error("invalid sound_file [spawn_sound_from_file]")
        return 0;
    }
    if (!prefab) {
        zox_log_error("invalid prefab [spawn_sound_from_file]")
        return 0;
    }
    zox_geter(src, SoundData, src_sound_data)
    zox_geter_value(src, SoundLength, float, sound_length)
    if (!src_sound_data->length) {
        zox_log_error("invalid sdl_sound [spawn_sound_from_file]")
        return 0;
    }
    if (!src_sound_data->value) {
        zox_log_error("invalid sdl_sound abuf [spawn_sound_from_file]")
        return 0;
    }
    int memory_length = sizeof(float) * src_sound_data->length;
    float *value = (float*) malloc(memory_length);
    if (!value) {
        zox_log_error("failed to malloc: %s", zox_get_name(src))
        return 0;
    }
    memcpy(value, src_sound_data->value, memory_length);
    // ecs
    zox_instance(prefab)
    zox_name("sound_file_instance")
    zox_set(e, SoundVolume, { default_sound_volume_loaded })
    zox_set(e, SoundData, {
        .value = value,
        .length = src_sound_data->length
    })
    zox_set(e, SoundLength, { sound_length })
    if (frequency) {
        zox_set(e, SoundFrequency, { frequency })
    }
    if (volume) {
        zox_set(e, SoundVolume, { volume })
    }
    zox_set(e, ProcessSound, { zox_sound_process_trigger })
    // zox_set(e, TriggerSound, { zox_sound_play_trigger })
    // zox_log_sounds("+ new [sound_file_instance] [%s] length [%f]", zox_get_name(e), sound_length)
    return e;
}