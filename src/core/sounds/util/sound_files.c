#define directory_sounds "sounds"character_slash

int sound_files_count = 0;
#ifdef zox_lib_sdl_mixer
ecs_entity_t *files_sounds;
#endif
string_hashmap *files_hashmap_sounds;

void load_files_sounds() {
    char* load_directory = concat_file_path(resources_path, directory_sounds);
    FileList files = get_files(load_directory);
#ifdef zox_print_files
    zox_log("   > sounds found [%i]\n", files.count)
#endif
#ifdef zox_lib_sdl_mixer
    sound_files_count = files.count;
    files_sounds = malloc(sizeof(ecs_entity_t) * files.count);
    files_hashmap_sounds = create_string_hashmap(files.count);
    zox_log(" + loaded sounds [%i]\n", sound_files_count)
#endif
    for (int i = 0; i < files.count; i++) {
        char* filepath = files.files[i];
        char* filename = files.filenames[i];
#ifdef zox_print_files
        zox_log("   > sound file [%s]\n", filepath)
#endif
#ifdef zox_lib_sdl_mixer
        Mix_Chunk *sound_data = Mix_LoadWAV(filepath);
        if (!sound_data) {
            zox_log(" ! sound file failed to load [%s]\n", filepath)
            printf("  - SDL_mixer Error: %s\n", Mix_GetError());
            files_sounds[i] = 0;
            continue;
        }
        const float sound_length = get_mix_chunk_sound_length(sound_data);
        const ecs_entity_t e = spawn_sound_filepath(world, prefab_sound_filepath, sound_data, sound_length);
        files_sounds[i] = e;
        string_hashmap_add(files_hashmap_sounds, new_string_data_clone(filename), e);
#endif
    }
    free_files(&files);
    free(load_directory);
}

void dispose_files_sounds() {
    string_hashmap_dispose(files_hashmap_sounds);
    files_hashmap_sounds = NULL;
    free(files_sounds);
    files_sounds = NULL;
}


ecs_entity_t spawn_sound_from_file(ecs_world_t *world, const ecs_entity_t prefab, const ecs_entity_t sound_file) {
    if (!sound_file) {
        zox_log(" ! sound_file invalid\n")
        return 0;
    }
    zox_instance(prefab)
    zox_name("sound_file")
    zox_prefab_set(e, SoundVolume, { default_sound_volume_loaded })
#ifdef zox_lib_sdl_mixer
    const SDLSound *sdl_sound = zox_get(sound_file, SDLSound)
    const float sound_length = zox_get_value(sound_file, SoundLength)
    // zox_log(" > playing sound file [%i]\n", index)
    // Mix_Chunk *sound_data_cloned = clone_mix_chunk(sound_data);
    // zox_set(e, SDLSound, { sdl_sound->value })
    zox_set(e, SDLSound, { (Mix_Chunk) {
        .volume = sdl_sound->value.volume,
        .alen = sdl_sound->value.alen,
        .abuf = sdl_sound->value.abuf
    } })
    zox_set(e, SoundLength, { sound_length })
    // unless we justt  copy over
    // zox_set(e, SoundData, { mixChunk->abuf })
    // wait this won't clear, so we need SDLData t too'
    //Mix_LoadWAV(sound_file_names[0]) }); //  sounds[0] });
#else
    zox_log(" ! sound cannot play as no SDL_MIXER [%i]\n", index)
#endif
    return e;
}


ecs_entity_t spawn_sound_from_file_index(ecs_world_t *world, const ecs_entity_t prefab, const int index) {
    if (index < sound_files_count && files_sounds[index]) {
        const ecs_entity_t sound_file = files_sounds[index];
        return spawn_sound_from_file(world, prefab, sound_file);
    } else {
        zox_log(" ! sound is null at [%i]\n", index)
    }
    return 0;
}


ecs_entity_t spawn_sound_from_file_name(ecs_world_t *world, const ecs_entity_t prefab, char *name) {
    const ecs_entity_t sound_file = string_hashmap_get(files_hashmap_sounds, new_string_data(name));
    if (sound_file) {
        return spawn_sound_from_file(world, prefab, sound_file);
    } else {
        zox_log(" ! sound_file not found [%s]\n", name)
    }
    return 0;
}
