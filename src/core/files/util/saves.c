
void get_save_directory(const char *game, char *path, size_t size) {
#ifdef zoxel_on_windows
    char home_directory[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, home_directory))) {
        snprintf(path, size, "%s\\%s", home_directory, game);
    } else {
        zox_log(" ! home_directory null [get_save_directory]")
    }
#else
    const char *home_directory = getenv("HOME");
    if (home_directory) {
        snprintf(path, size, "%s/.local/share/%s", home_directory, game);
    } else {
        zox_log(" ! home_directory null [get_save_directory]")
    }
#endif
}

void get_save_filepath(const char *game, const char *filename, char *path, size_t size) {
    char dir[256];
    get_save_directory(game, dir, sizeof(dir));
    snprintf(path, size, "%s/%s", dir, filename);
}

unsigned char has_path_directory(const char *path) {
#ifdef zoxel_on_windows
    DWORD attrib = GetFileAttributesA(path);
    if (attrib != INVALID_FILE_ATTRIBUTES && (attrib & FILE_ATTRIBUTE_DIRECTORY)) {
        return 1;  // Save game directory exists
    }
#else
    struct stat st;
    if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
        return 1;  // Save game directory exists
    }
#endif
    return 0; // Save game directory does not exist
}

unsigned char has_save_game_directory(const char *game) {
    char path[256];
    get_save_directory(game, path, sizeof(path));
    // zox_log(" > save path is [%s]\n", path)
    return has_path_directory(path);
}



int delete_directory_contents(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    char filepath[256];
    int result = 0;
    if (!dir) {
        perror("Error opening directory");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);

#ifdef _WIN32
        DWORD attrib = GetFileAttributes(filepath);
        if (attrib & FILE_ATTRIBUTE_DIRECTORY) {
            result = delete_directory_contents(filepath);
            if (result != 0) break;
            if (!RemoveDirectory(filepath)) {
                perror("Error deleting directory");
                result = -1;
                break;
            }
        } else {
            if (!DeleteFile(filepath)) {
                perror("Error deleting file");
                result = -1;
                break;
            }
        }
#else
        struct stat st;
        if (stat(filepath, &st) == 0 && S_ISDIR(st.st_mode)) {
            result = delete_directory_contents(filepath);
            if (result != 0) break;
            if (rmdir(filepath) != 0) {
                perror("Error deleting directory");
                result = -1;
                break;
            }
        } else {
            if (remove(filepath) != 0) {
                perror("Error deleting file");
                result = -1;
                break;
            }
        }
#endif
    }

    closedir(dir);
    return result;
}

void delete_save_directory(const char *game) {
    char path[256];
    get_save_directory(game, path, sizeof(path));
    if (has_path_directory(path)) {
        zox_log(" + deleting directory [%s]\n", path)
        if (delete_directory_contents(path) == 0) {
#ifdef _WIN32
            if (RemoveDirectory(path)) {
                zox_log(" > directory deleted successfully\n");
            } else {
                perror("Error deleting directory");
            }
#else
            if (rmdir(path) == 0) {
                zox_log(" > directory deleted successfully\n");
            } else {
                perror("Error deleting directory");
            }
#endif
        }
    }
}

unsigned char create_new_save_directory(const char *game) {
    char path[256];
    get_save_directory(game, path, sizeof(path));
    if (!has_path_directory(path)) {
        zox_log(" + creating new directory [%s]\n")
#ifdef zoxel_on_windows
        if (_mkdir(path) == 0) {
            return 1;
        } else {
            perror("Error creating directory");
            return 0;
        }
#else
        if (mkdir(path, 0700) == 0) {
            return 1;
        } else {
            perror("Error creating directory");
            return 0;
        }
#endif
    } else {
        zox_log(" > save directory existed [%s]\n")
        return 1;
    }
}


/*
    User-specific Config Directory: ~/.config/<YourGame>
    User-specific Data Directory: ~/.local/share/<YourGame>
*/

unsigned char has_save_game_file(const char *game, const char *filename) {
    char path[256];
    get_save_filepath(game, filename, path, sizeof(path));
    // zox_log(" > has save? %s\n", path)
    FILE *file = fopen(path, "rb");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}
