void free_files(FileList *fileList) {
    for (int i = 0; i < fileList->count; i++) {
        free(fileList->files[i]);
        free(fileList->filenames[i]);
    }
    free(fileList->files);
    free(fileList->filenames);
    fileList->files = NULL;
    fileList->filenames = NULL;
    fileList->count = 0;
}


// without extension
char* get_filename(const char* filepath) {
    // Find the last occurrence of the directory separator
    const char *last_slash = strrchr(filepath, '/');
    if (!last_slash) {
        last_slash = strrchr(filepath, '\\');  // For Windows paths
    }
    const char *filename = (last_slash) ? last_slash + 1 : filepath;

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

void add_file(FileList *fileList, const char *filepath) {
    static int capacity = 10;
    if (fileList->count == 0) {
        fileList->files = malloc(capacity * sizeof(char *));
        if (fileList->files == NULL) {
            perror("Memory allocation failed");
            return;
        }
        fileList->filenames = malloc(capacity * sizeof(char *));
        if (fileList->filenames == NULL) {
            perror("Memory allocation failed");
            return;
        }
    } else if (fileList->count >= capacity) {
        capacity *= 2;
        char **temp = realloc(fileList->files, capacity * sizeof(char *));
        char **temp2 = realloc(fileList->filenames, capacity * sizeof(char *));
        if (temp == NULL || temp2 == NULL) {
            if (temp) free(temp);
            if (temp2) free(temp2);
            perror("Memory reallocation failed");
            free_files(fileList);
            return;
        }
        fileList->files = temp;
        fileList->filenames = temp2;
    }
    fileList->files[fileList->count] = strdup(filepath);
    // zox_log(" + filepath: %s\n", filepath)
    if (fileList->files[fileList->count] == NULL) {
        perror("strdup failed");
        return;
    }
    fileList->filenames[fileList->count] = get_filename(fileList->files[fileList->count]);
    if (fileList->filenames[fileList->count] == NULL) {
        perror("get_filename failed");
        return;
    }
    fileList->count++;
}


void traverse_directory(FileList *fileList, const char *directory) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    dp = opendir(directory);
    if (dp == NULL) {
        perror("Unable to open directory");
        return;
    }
    while ((entry = readdir(dp)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
        char *name = entry->d_name;
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", directory, name);
        if (stat(path, &statbuf) == -1) {
            perror("Unable to stat file");
            continue;
        }
        if (S_ISDIR(statbuf.st_mode)) {
            traverse_directory(fileList, path);
        } else {
            add_file(fileList, path);
        }
    }
    closedir(dp);
}

FileList get_files(const char *directory) {
    FileList fileList;
    fileList.count = 0;
    fileList.files = NULL;
    char *directory_non_slash = strdup(directory);
    if (directory_non_slash == NULL) {
        perror("Memory allocation failed");
        return fileList;
    }
    size_t len = strlen(directory_non_slash);
    if (len > 1 && directory_non_slash[len - 1] == '/') {
        directory_non_slash[len - 1] = '\0';
    }
    traverse_directory(&fileList, directory_non_slash);
    free(directory_non_slash);
    return fileList;
}

/*FileList get_files(const char *directory) {
    DIR *dp;
    struct dirent *entry;
    FileList fileList;
    fileList.count = 0;
    fileList.files = NULL;
    int capacity = 10; // Initial capacity for file array
    dp = opendir(directory);
    if (dp == NULL) {
        perror("Unable to open directory");
        return fileList;
    }
    fileList.files = malloc(capacity * sizeof(char *));
    if (fileList.files == NULL) {
        perror("Memory allocation failed");
        closedir(dp);
        return fileList;
    }
    while ((entry = readdir(dp)) != NULL) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) {
            continue;
        }
        // Resize array if necessary
        if (fileList.count >= capacity) {
            capacity *= 2;
            char **temp = realloc(fileList.files, capacity * sizeof(char *));
            if (temp == NULL) {
                perror("Memory reallocation failed");
                for (int i = 0; i < fileList.count; i++) free(fileList.files[i]);
                free(fileList.files);
                fileList.files = NULL;
                fileList.count = 0;
                closedir(dp);
                return fileList;
            }
            fileList.files = temp;
        }

        // Store the file name
        fileList.files[fileList.count] = strdup(entry->d_name);
        fileList.count++;
    }
    closedir(dp);
    return fileList;
}*/

void list_files(const char *directory) {
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
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
        // Printing the file name
        // printf("%s\n", entry->d_name);
        zox_log("   + file [%s]\n", entry->d_name)
    }
    // Closing the directory
    closedir(dp);
}
