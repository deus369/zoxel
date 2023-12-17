#define directory_sounds "sounds"character_slash

int sound_files_count = 0;
#ifdef SDL_MIXER
Mix_Chunk **sound_files;
#endif

void load_files_sounds() {
    // get a list of files in monsters_directory
    char* load_directory = concat_file_path(resources_path, directory_sounds);
    // list_files(load_directory);
    FileList files = get_files(load_directory);
    zox_log("   > sounds found [%i]\n", files.count)
    // vox_files_count = files.count;
#ifdef SDL_MIXER
    sound_files_count = files.count;
    sound_files = malloc(sizeof(Mix_Chunk) * files.count);
#endif
    for (int i = 0; i < files.count; i++) {
        char* file_path = concat_file_path(load_directory, files.files[i]);
        zox_log("   > sound file [%s]\n", file_path)
#ifdef SDL_MIXER
        sound_files[i] = Mix_LoadWAV(file_path);
#endif
        free(file_path);
    }
    free_files(files);
    free(load_directory);
}

void dispose_sound_files() {
#ifdef SDL_MIXER
    for (int i = 0; i < sound_files_count; i++) free(sound_files[i]);
    free(sound_files);
#endif
}

ecs_entity_t spawn_sound_from_file(ecs_world_t *world, int index) {
    zox_instance(prefab_sound)
    zox_name("sound_file")
#ifdef SDL_MIXER
    Mix_Chunk *mixChunk = clone_mix_chunk(sound_files[index]);
    zox_set(e, SDLSound, { mixChunk })
    zox_set(e, SoundLength, { get_mix_chunk_sound_length(mixChunk) })
    //Mix_LoadWAV(sound_file_names[0]) }); //  sounds[0] });
#endif
#ifdef zoxel_debug_spawns
    zox_log(" + spawned sound [%lu]\n", e)
#endif
    return e;
}
