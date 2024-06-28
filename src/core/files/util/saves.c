typedef struct {
    // char playerName[50];
    int seed;
} GameSave;

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
    zox_log(" > save path is [%s]\n", path)
    return has_path_directory(path);
}


void create_new_save_directory(const char *game) {
    char path[256];
    get_save_directory(game, path, sizeof(path));
    if (!has_path_directory(path)) {
        zox_log(" + creating new directory [%s]\n")
#ifdef zoxel_on_windows
        if (_mkdir(path) == 0) {
            zox_log(" > directory created successfully");
        } else {
            perror("Error creating directory");
        }
#else
        if (mkdir(path, 0700) == 0) {
            zox_log(" > directory created successfully");
        } else {
            perror("Error creating directory");
        }
#endif
    } else {
        zox_log(" > save directory existed [%s]\n")
    }
}


/*
    User-specific Config Directory: ~/.config/<YourGame>
    User-specific Data Directory: ~/.local/share/<YourGame>
*/

// clearing:
// memset(&myGame, 0, sizeof(GameSave));

unsigned char has_save_game_file(const char *game, const char *filename) {
    char path[256];
    get_save_filepath(game, filename, path, sizeof(path));
    FILE *file = fopen(path, "rb");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void save_game(const char *game, const char *filename, GameSave *data) {
    char path[256];
    get_save_filepath(game, filename, path, sizeof(path));
    FILE *file = fopen(path, "wb");
    if (file == NULL) {
        zox_log(" > error saving [%s]\n", path)
        perror("Error opening file for writing");
        return;
    }
    fwrite(data, sizeof(GameSave), 1, file);
    fclose(file);
    zox_log(" > saved game [%i] to [%s]\n", data->seed, path)
}

void load_game(const char *game, const char *filename, GameSave *data) {
    char path[256];
    get_save_filepath(game, filename, path, sizeof(path));
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }
    fread(data, sizeof(GameSave), 1, file);
    fclose(file);
    zox_log(" > loaded game [%i] to [%s]\n", data->seed, path)
}
