typedef struct FileList {
    char **files;
    int count;
} FileList;

void free_files(FileList fileList) {
    for (int i = 0; i < fileList.count; i++) free(fileList.files[i]);
    free(fileList.files);
}

FileList get_files(const char *directory) {
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
}

// todo: test on windows
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
