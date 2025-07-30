

#ifndef zox_windows

char* get_base_path_native() {
    char path[PATH_SIZE];
    char *base = NULL;
    /* Linux and other Unix-like systems: use /proc/self/exe */
    ssize_t n = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (n == -1) {
        return NULL;
    }
    path[n] = '\0';
    /* Find the last '/' and terminate the string after it */
    char *last_slash = strrchr(path, char_slash);
    if (!last_slash) {
        return NULL;
    }
    *(last_slash + 1) = '\0';
    base = strdup(path);
    return base;
}

#endif