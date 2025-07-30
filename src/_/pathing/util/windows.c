#ifdef zox_windows

#ifndef PATH_SIZE
    #define PATH_SIZE 1024
#endif

char* get_base_path_windows() {
    zox_logv("Getting Windows base_path.");

    char path[PATH_SIZE];
    char *base = NULL;

    DWORD len = GetModuleFileNameA(NULL, path, sizeof(path));
    if (len == 0) {
        zox_log_error("GetModuleFileNameA failed with error %lu", GetLastError());
        return NULL;
    }
    if (len == sizeof(path)) {
        zox_log_error("Buffer too small for executable path");
        return NULL;
    }

    zox_logv("Full executable path: %s", path);

    char *last_backslash = strrchr(path, char_slash);
    if (!last_backslash) {
        zox_log_error("Failed to find last backslash in path");
        return NULL;
    }

    // Terminate string just after the last backslash to get the base directory
    *(last_backslash + 1) = '\0';

    base = _strdup(path);
    if (!base) {
        zox_log_error("Failed to duplicate path string");
    }
    return base;
}

#endif