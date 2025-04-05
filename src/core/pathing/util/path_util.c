void debug_base_path(const char *base_path) {
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(base_path)) != NULL) {
        zox_log(" > directories and files in [%s]\n", base_path)
        while ((entry = readdir(dir)) != NULL) zox_log("     + [%s]\n", entry->d_name)
        closedir(dir);
    } else zox_log(" - failed to open directory [%s]\n", base_path)
}

char* concat_file_path(const char* resources_path, const char* file_path) {
    if (resources_path == NULL || file_path == NULL) return NULL;
    char* full_file_path = malloc(strlen(resources_path) + strlen(file_path) + 1);
    strcpy(full_file_path, resources_path);
    strcat(full_file_path, file_path);
    return full_file_path;
}

char* get_full_file_path(const char* filepath) {
    char* fullpath = malloc(strlen(data_path) + strlen(filepath) + 1);
    strcpy(fullpath, data_path);
    strcat(fullpath, filepath);
#ifdef zoxel_debug_pathing
    zox_log("fullpath: %s\n", fullpath)
#endif
    return fullpath;
}

void convert_file_path_slashes(char* path) {
    while (*path) {
        if (*path == '\\') {
            *path = '/';
        }
        ++path;
    }
}

char* clone_str(const char* text) {
    int length = strlen(text);
    char *new_text = malloc(length);
    memcpy(new_text, text, length);
    return new_text;
}

char* get_base_path() {
    char path[PATH_SIZE];
    char *base = NULL;
    #ifdef _WIN32
        /* Get the full path to the executable */
        DWORD len = GetModuleFileNameA(NULL, path, sizeof(path));
        if (len == 0 || len == sizeof(path)) return NULL;
        /* Find the last backslash and terminate the string just after it */
        char *last_backslash = strrchr(path, '\\');
        if (!last_backslash) return NULL;
        *(last_backslash + 1) = '\0';
        base = _strdup(path);  /* use strdup (or _strdup on Windows) */
    #else
        /* Linux and other Unix-like systems: use /proc/self/exe */
        ssize_t n = readlink("/proc/self/exe", path, sizeof(path) - 1);
        if (n == -1) return NULL;
        path[n] = '\0';
        /* Find the last '/' and terminate the string after it */
        char *last_slash = strrchr(path, '/');
        if (!last_slash) return NULL;
        *(last_slash + 1) = '\0';
        base = strdup(path);
    #endif
    return base;
}

char* initialize_base_path() {
    char* base_path;
    #ifdef zoxel_on_android
        base_path = clone_str(SDL_AndroidGetInternalStoragePath());
        __android_log_print(ANDROID_LOG_VERBOSE, "Zoxel", "base_path [%s]", base_path);
    #else
        base_path = get_base_path();
        /* ifdef zoxel_using_sdl
            base_path = SDL_GetBasePath();
        #else */
        // can i use a base path here based on platform?
        // zox_log(" ! SDL is disabled\n")
    #endif
    #ifdef zoxel_debug_base_path
        debug_base_path(base_path);
    #endif
    return base_path;
}

char* get_terminal_path_with_raw() {
    char* cwd = getcwd(NULL, 0);  // malloc'd by glibc
    if (!cwd) return NULL;
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

// sets base_path, data_path
byte initialize_pathing() {
    #ifdef zox_disable_io
        zox_log(" ! io is disabled\n")
        return EXIT_SUCCESS;
    #endif
    raw_path = get_terminal_path_with_raw();
    char* base_path = initialize_base_path();
    if (base_path == NULL) {
        zox_log("! failed to get base_path\n")
        return EXIT_FAILURE;
    }
    data_path = base_path;
    zox_log_io("> io base_path [%s]", base_path)
    DIR* dir = opendir(base_path);
    if (dir) {
#ifndef zoxel_on_android
        resources_path = malloc(strlen(base_path) + strlen(resources_folder_name) + 1);
        strcpy(resources_path, base_path);
        strcat(resources_path, resources_folder_name);
#else
        resources_path = malloc(strlen(base_path) + strlen("/resources/") + 1);
        strcpy(resources_path, base_path);
        strcat(resources_path, "/resources/");
#endif
        zox_log_io("> resources_path [%s]", resources_path)
#ifdef zoxel_on_android
        decompress_android_resources();
#endif
        DIR* dir2 = opendir(resources_path);
        if (dir2) {
            closedir(dir2);
        } else {
            zox_log("! resources_path does not exist [%s]\n", resources_path)
        }
        closedir(dir);
    } else if (ENOENT == errno) {
        zox_log("SDL data_path (DOES NOT EXIST): %s\n", data_path)
    } else {
        zox_log("SDL data_path (MYSTERIOUSLY DOES NOT EXIST): %s\n", data_path)
    }
    return EXIT_SUCCESS;
}
