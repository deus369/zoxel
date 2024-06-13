#define directory_sounds "sounds"character_slash

int sound_files_count = 0;
#ifdef zox_lib_sdl_mixer
Mix_Chunk **sound_files;
#endif

void load_files_sounds() {
    // get a list of files in monsters_directory
    char* load_directory = concat_file_path(resources_path, directory_sounds);
    // list_files(load_directory);
    FileList files = get_files(load_directory);
#ifdef zox_print_files
    zox_log("   > sounds found [%i]\n", files.count)
#endif
    // vox_files_count = files.count;
#ifdef zox_lib_sdl_mixer
    sound_files_count = files.count;
    sound_files = malloc(sizeof(Mix_Chunk) * files.count);
#endif
    for (int i = 0; i < files.count; i++) {
        // char* filepath = concat_file_path(load_directory, files.files[i]);
        char* filepath = files.files[i];
#ifdef zox_print_files
        zox_log("   > sound file [%s]\n", filepath)
#endif
#ifdef zox_lib_sdl_mixer
        sound_files[i] = Mix_LoadWAV(filepath);
#endif
        // free(filepath);
    }
    free_files(&files);
    free(load_directory);
}

void dispose_sound_files() {
#ifdef zox_lib_sdl_mixer
    for (int i = 0; i < sound_files_count; i++) free(sound_files[i]);
    free(sound_files);
#endif
}

ecs_entity_t spawn_sound_from_file(ecs_world_t *world, const ecs_entity_t prefab, const int index) {
    zox_instance(prefab)
    zox_name("sound_file")
#ifdef zox_lib_sdl_mixer
    if (index < sound_files_count && sound_files[index]) {
        zox_log(" > playing sound file [%i]\n", index)
        Mix_Chunk *mixChunk = clone_mix_chunk(sound_files[index]);
        zox_set(e, SDLSound, { *mixChunk })
        zox_set(e, SoundLength, { get_mix_chunk_sound_length(mixChunk) })
    } else {
        zox_log(" ! sound index not found [%i]\n", index)
    }
    //Mix_LoadWAV(sound_file_names[0]) }); //  sounds[0] });
#else
    zox_log(" ! sound cannot play as no SDL_MIXER [%i]\n", index)
#endif
    return e;
}
