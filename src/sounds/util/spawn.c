ecs_entity_t spawn_sound_from_file_index(ecs_world_t *world,
    const ecs_entity_t prefab,
    const int index)
{
    if (index < sound_files_count && files_sounds[index]) {
        return spawn_sound_from_file(world, prefab, files_sounds[index], 0, global_volume_sfx);
    } else {
        zox_log_error("sound is null at [%i]", index)
    }
    return 0;
}

ecs_entity_t spawn_sound_from_file_name(ecs_world_t *world,
    const ecs_entity_t prefab,
    char *name,
    float frequency,
    float volume)
{
    const ecs_entity_t sound_file = string_hashmap_get(files_hashmap_sounds, new_string_data(name));
    if (sound_file) {
        return spawn_sound_from_file(world,
            prefab,
            sound_file,
            frequency,
            volume);
    } else {
        zox_log_error("sound_file not found [%s]", name)
        return 0;
    }
}