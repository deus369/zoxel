void load_files_sounds() {
    char* load_directory = concat_file_path(resources_path, directory_sounds);
    FileList files = get_files(load_directory);
    sound_files_count = files.count;
    files_sounds = malloc(sizeof(ecs_entity_t) * files.count);
    files_hashmap_sounds = create_string_hashmap(files.count);
    zox_log_io(" + io loaded [sounds] [%i]", files.count)
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i];
        char* filename = files.filenames[i];
        zox_log_io("   - [%i] [sound] [%s]", i, filepath)
#ifdef zox_lib_sdl_mixer
        Mix_Chunk *sound_data = Mix_LoadWAV(filepath);
        if (!sound_data) {
            zox_log(" ! sound file failed to load [%s]\n", filepath)
            zox_log("  - SDL_mixer Error: %s\n", Mix_GetError())
            files_sounds[i] = 0;
            continue;
        }
        const float sound_length = get_mix_chunk_sound_length(sound_data);
        const ecs_entity_t e = spawn_sound_filepath(world, prefab_sound_filepath, sound_data, sound_length);
        files_sounds[i] = e;
        string_hashmap_add(files_hashmap_sounds, new_string_data_clone(filename), e);
#else
        files_sounds[i] = 0;
#endif
    }
    free_files(&files);
}

void dispose_files_sounds() {
    zox_log_io(" > disposing [%i] [sounds]", files_hashmap_sounds->size)
    string_hashmap_dispose(files_hashmap_sounds);
    files_hashmap_sounds = NULL;
    free(files_sounds);
    files_sounds = NULL;
}