void load_files_sounds(ecs_world_t *world) {
    char* load_directory = concat_file_path(resources_path, directory_sounds);
    FileList files = get_files(load_directory, 0);
    sound_files_count = files.count;
    files_sounds = malloc(sizeof(ecs_entity_t) * files.count);
    files_hashmap_sounds = create_string_hashmap(files.count);
    zox_log_io(" + io loaded [sounds] [%i]", files.count)
    zox_log_sounds(" + io loaded [sounds] [%i]", files.count)
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i];
        char* filename = files.filenames[i];
        zox_log_io("   - [%i] [sound] [%s]", i, filepath)
#ifdef zox_lib_sdl_mixer
        Mix_Chunk *mix_chunk = Mix_LoadWAV(filepath);
        if (!mix_chunk) {
            zox_log_error("sound file failed to load [%s] due to [%s]", filepath, Mix_GetError())
            files_sounds[i] = 0;
            continue;
        }
        const float sound_length = get_mix_chunk_sound_length(mix_chunk);
        SoundData soundData = process_mix_chunk(mix_chunk);
        const ecs_entity_t e = spawn_sound_filepath(world, prefab_sound_filepath, soundData, sound_length);
        zox_log_sounds("   - [%i] [sound] [%s] - length [%f]", i, filepath, sound_length)
        files_sounds[i] = e;
        string_hashmap_add(files_hashmap_sounds, new_string_data_clone(filename), e);
#else
        files_sounds[i] = 0;
#endif
    }
    free_files(&files);
}

void dispose_files_sounds() {
    if (!files_hashmap_sounds) {
        zox_log_error("cannot dispose null files_hashmap_sounds")
    } else {
        zox_log_io(" > disposing [%i] [sounds]", files_hashmap_sounds->size)
        zox_log_sounds(" > disposing [%i] [sounds]", files_hashmap_sounds->size)
        string_hashmap_dispose(files_hashmap_sounds);
        files_hashmap_sounds = NULL;
        free(files_sounds);
        files_sounds = NULL;
    }
}