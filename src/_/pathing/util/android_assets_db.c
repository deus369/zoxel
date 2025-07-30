#ifdef zox_android

// Reads assets.txt from Android assets and returns array of strings (dirs).
// *out_count will be set to number of dirs read.
// Caller must free returned array and each string inside it.
char** get_assets_dirs(AAssetManager* manager, const char* assets_txt_path, int* out_count) {
    *out_count = 0;
    AAsset* asset = AAssetManager_open(manager, assets_txt_path, AASSET_MODE_STREAMING);
    if (!asset) {
        zox_log_error("Failed to open assets.txt at [%s]", assets_txt_path);
        return NULL;
    }

    off_t size = AAsset_getLength(asset);
    if (size <= 0) {
        AAsset_close(asset);
        zox_log_error("assets.txt is empty or invalid size");
        return NULL;
    }

    char* buffer = malloc(size + 1);
    if (!buffer) {
        AAsset_close(asset);
        zox_log_error("Failed to malloc buffer for assets.txt");
        return NULL;
    }

    int read_size = AAsset_read(asset, buffer, size);
    AAsset_close(asset);
    if (read_size <= 0) {
        free(buffer);
        zox_log_error("Failed to read assets.txt content");
        return NULL;
    }
    buffer[read_size] = '\0'; // Null terminate

    // Count lines first
    int lines = 0;
    for (char* p = buffer; *p; p++) {
        if (*p == '\n') lines++;
    }
    if (read_size > 0 && buffer[read_size - 1] != '\n') lines++; // last line may not have newline

    char** dirs = malloc(sizeof(char*) * lines);
    if (!dirs) {
        free(buffer);
        zox_log_error("Failed to malloc dirs array");
        return NULL;
    }

    // Split lines
    int idx = 0;
    char* line = buffer;
    for (char* p = buffer; ; p++) {
        if (*p == '\n' || *p == '\0') {
            *p = '\0';

            // Strip trailing '\r' for Windows line endings
            char* end = p - 1;
            if (end >= line && *end == '\r') {
                *end = '\0';
            }

            if (*line) { // skip empty lines
                dirs[idx] = strdup(line);
                if (!dirs[idx]) {
                    // Free previously allocated strings on failure
                    for (int j = 0; j < idx; j++) free(dirs[j]);
                    free(dirs);
                    free(buffer);
                    zox_log_error("Failed strdup for dir line");
                    return NULL;
                }
                idx++;
            }
            line = p + 1;
            if (*p == '\0') break;
        }
    }

    free(buffer);
    *out_count = idx;
    return dirs;
}

#endif