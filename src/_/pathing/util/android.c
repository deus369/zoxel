#ifdef zox_android

/*char* android_base_path() {
    char* base_path = clone_str(SDL_AndroidGetInternalStoragePath());
    // __android_log_print(ANDROID_LOG_VERBOSE, "Zoxel", "base_path [%s]", base_path);
    return base_path;
}*/

char* get_terminal_path_with_raw() {
    char* cwd = getcwd(NULL, 0);  // malloc'd by glibc
    if (!cwd) {
        return NULL;
    }
    const char* suffix = "/raw/";
    size_t cwd_len = strlen(cwd);
    size_t suffix_len = strlen(suffix);
    char* result = malloc(cwd_len + suffix_len + 1);
    if (!result) {
        free(cwd);
        return NULL;
    }
    strcpy(result, cwd);
    strcat(result, suffix);
    free(cwd);
    return result;
}

byte initialize_pathing_android() {
    char* base_path = SDL_AndroidGetInternalStoragePath();
    if (!base_path) {
        zox_log_error("[pathing_android] failed to get base_path")
        return EXIT_FAILURE;
    }
    zox_logv("Android Base Path [%s]", base_path);
    data_path = clone_str(base_path);
    DIR* dir = opendir(base_path);
    if (dir) {
        resources_path = malloc(strlen(base_path) + strlen("/"resources_dir_name"/") + 1);
        strcpy(resources_path, base_path);
        strcat(resources_path, "/"resources_dir_name"/");
        zox_logv("resources_path [%s]", resources_path)
        closedir(dir);
    } else if (ENOENT == errno) {
        zox_log_error("SDL data_path (DOES NOT EXIST): %s", data_path)
    } else {
        zox_log_error("SDL data_path (MYSTERIOUSLY DOES NOT EXIST): %s", data_path)
    }
    decompress_android_resources(resources_path);
    return EXIT_SUCCESS;
}

#endif
