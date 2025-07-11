ecs_entity_t spawn_sound_from_file(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t sound_file) {
    if (!sound_file) {
        zox_log_error("invalid sound_file [spawn_sound_from_file]")
        return 0;
    }
    if (!prefab) {
        zox_log_error("invalid prefab [spawn_sound_from_file]")
        return 0;
    }
#ifdef zox_lib_sdl_mixer
    zox_geter(sound_file, SDLSound, sdl_sound)
    int memory_length = sdl_sound->value.alen;
    if (memory_length == 0) {
        zox_log_error("invalid sdl_sound [spawn_sound_from_file]")
        return 0;
    }
    if (!sdl_sound->value.abuf) {
        zox_log_error("invalid sdl_sound abuf [spawn_sound_from_file]")
        return 0;
    }
#endif
    zox_instance(prefab)
    zox_name("sound_file")
    zox_set(e, SoundVolume, { default_sound_volume_loaded })
#ifdef zox_lib_sdl_mixer
    const float sound_length = zox_get_value(sound_file, SoundLength)
    int array_length = memory_length / sizeof(float);
    float *new_data = (float*) malloc(memory_length);
    if (!new_data) {
        zox_log_error("failed to malloc: %s", zox_get_name(sound_file))
    } else {
        memcpy(new_data, sdl_sound->value.abuf, memory_length);
        zox_set(e, SoundData, { array_length, new_data })
        zox_set(e, SoundLength, { sound_length })
        zox_set(e, SDLSound, { sdl_sound->value })
        // zox_set(e, DestroyInTime, { sound_length })
        zox_log_sounds("+ new [sound] [%s] length [%f]", zox_get_name(e), sound_length)
    }
#else
    zox_log_error("sound cannot play as no SDL_MIXER")
#endif
    return e;
}

ecs_entity_t spawn_sound_from_file_index(ecs_world_t *world, const ecs_entity_t prefab, const int index) {
    if (index < sound_files_count && files_sounds[index]) {
        return spawn_sound_from_file(world, prefab, files_sounds[index]);
    } else {
        zox_log_error("sound is null at [%i]", index)
    }
    return 0;
}

ecs_entity_t spawn_sound_from_file_name(ecs_world_t *world, const ecs_entity_t prefab, char *name) {
    const ecs_entity_t sound_file = string_hashmap_get(files_hashmap_sounds, new_string_data(name));
    if (sound_file) {
        return spawn_sound_from_file(world, prefab, sound_file);
    } else {
        zox_log_error("sound_file not found [%s]", name)
        return 0;
    }
}

// zox_log(" > playing sound file [%i]\n", index)
// Mix_Chunk *sound_data_cloned = clone_mix_chunk(sound_data);
// zox_set(e, SDLSound, { sdl_sound->value })
// unless we justt  copy over
// if processed or dirty, this doesn't need to be set here
/*zox_set(e, SDLSound, { (Mix_Chunk) {
 . v*olume = global_master_volume,
*            // .volume = sdl_sound->value.volume,
.alen = memory_length,
.abuf = (void*) new_data // sdl_sound->value.abuf
} })*/