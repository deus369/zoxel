void free_files(FileList *fileList) {
    if (!fileList) {
        return;
    }
    if (fileList->files) {
        for (int i = 0; i < fileList->count; i++) {
            if (fileList->files[i]) {
                free(fileList->files[i]);
            }
        }
        free(fileList->files);
        fileList->files = NULL;
    }
    if (fileList->filenames) {
        for (int i = 0; i < fileList->count; i++) {
            if (fileList->filenames[i]) {
                free(fileList->filenames[i]);
            }
        }
        free(fileList->filenames);
        fileList->filenames = NULL;
    }
    fileList->count = 0;
}


// without extension
char* get_filename(const char* filepath, const byte keep_extension) {
    // Find the last occurrence of the directory separator
    const char *last_slash = strrchr(filepath, char_slash);
    const char *filename = (last_slash) ? last_slash + 1 : filepath;

    // If keeping extension, just return a strdup of filename
    if (keep_extension) {
        return strdup(filename);  // assumes POSIX; use custom clone if not
    }

    // Find the last occurrence of the dot
    const char *last_dot = strrchr(filename, '.');
    size_t length = (last_dot) ? (size_t)(last_dot - filename) : strlen(filename);

    // Allocate memory for the filename without extension
    char *result = (char*)malloc(length + 1);
    if (!result) {
        return NULL;  // Memory allocation failed
    }

    // Copy the filename without extension
    strncpy(result, filename, length);
    result[length] = '\0';  // Null-terminate the result

    return result;
}

void add_file(FileList *fileList, const char *filepath, byte keep_extension) {
    // zox_log(" + adding filepath: %s\n", filepath)
    // static int capacity = 10;
    if (fileList->count == 0) {
        fileList->capacity = 1;
        fileList->files = malloc(fileList->capacity * sizeof(char *));
        if (fileList->files == NULL) {
            perror("Memory allocation failed");
            return;
        }
        fileList->filenames = malloc(fileList->capacity * sizeof(char *));
        if (fileList->filenames == NULL) {
            perror("Memory allocation failed");
            return;
        }
    } else if (fileList->count >= fileList->capacity) {
        fileList->capacity *= 2;
        char **temp = realloc(fileList->files, fileList->capacity * sizeof(char *));
        char **temp2 = realloc(fileList->filenames, fileList->capacity * sizeof(char *));
        if (temp == NULL || temp2 == NULL) {
            if (temp) free(temp);
            if (temp2) free(temp2);
            zox_log(" ! memory reallocation failed\n")
            // perror("Memory reallocation failed");
            free_files(fileList);
            return;
        }
        fileList->files = temp;
        fileList->filenames = temp2;
    }
    const int len = strlen(filepath) + 1;
    char* filepath2 = malloc(len * sizeof(char)); //) strdup(filepath);
    // strncpy(filepath2, filepath, len - 1);
    // snprintf(filepath2, sizeof(filepath2), "%s", filepath);
    snprintf(filepath2, 256, "%s", filepath);

    // filepath2[len - 1] = '\0';
    fileList->files[fileList->count] = filepath2;

    // zox_log(" + filepath: %s\n", filepath)
    if (fileList->files[fileList->count] == NULL) {
        perror("strdup failed");
        return;
    }
    fileList->filenames[fileList->count] = get_filename(fileList->files[fileList->count], keep_extension);
    if (fileList->filenames[fileList->count] == NULL) {
        perror("get_filename failed");
        return;
    }
    fileList->count++;
}

void traverse_directory(
    FileList *fileList,
    const char *directory,
    byte keep_extension)
{
    if (directory == NULL) {
        zox_log_error("[traverse_directory] null directory")
        return;
    }
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    // zox_log(" ! opening directory [%s]\n", directory)
    dp = opendir(directory);
    if (dp == NULL) {
        zox_log_error("[traverse_directory] null opendir dp [%s]", directory)
        perror("        - ");
        return;
    }
    // zox_log(" > traversing directory [%s]\n", directory)
    while ((entry = readdir(dp)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }
        char *name = entry->d_name;
        char path[1024];
        snprintf(path, sizeof(path), "%s"character_slash"%s", directory, name);
        if (stat(path, &statbuf) == -1) {
            perror("Unable to stat file");
            continue;
        }
        if (S_ISDIR(statbuf.st_mode)) {
            traverse_directory(fileList, path, keep_extension);
        } else {
            add_file(fileList, path, keep_extension);
        }
    }
    closedir(dp);
}

FileList get_files(char *directory, byte keep_extension) {
    FileList fileList;
    fileList.count = 0;
    fileList.files = NULL;
    fileList.filenames = NULL;
    // size_t len = strlen(directory);
#ifndef zox_windows
    traverse_directory(&fileList, directory, keep_extension);
#else
    int len = strlen(directory);
    if (len > 1 && directory[len - 1] != char_slash) {
        traverse_directory(&fileList, directory, keep_extension);
    } else {
        char directory_non_slash[len - 1];
        strncpy(directory_non_slash, directory, len - 2);  // Ensuring no buffer overflow
        directory_non_slash[len - 2] = '\0';  // Null-terminate just in case
        traverse_directory(&fileList, directory_non_slash, keep_extension);
    }
#endif
    free(directory);
    return fileList;
}

void list_files(const char *directory) {
    if (directory == NULL) {
        zox_log(" ! directory is null in [list_files]\n")
        return;
    }
    struct dirent *entry;
    DIR *dp;
    // Opening the directory
    dp = opendir(directory);
    if (dp == NULL) {
        zox_log(" ! directory failed to open [%s]\n", directory)
        return;
    }
    // Reading the directory contents
    zox_log(" + directory opened [%s]\n", directory)
    while ((entry = readdir(dp)) != NULL) {
        // Skipping '.' and '..' entries
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }
        // Printing the file name
        // printf("%s\n", entry->d_name);
        zox_log("   + file [%s]\n", entry->d_name)
    }
    // Closing the directory
    closedir(dp);
}
