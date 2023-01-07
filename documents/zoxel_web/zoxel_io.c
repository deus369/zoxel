#include <sys/stat.h>
#include <time.h>

// Structure to store the initial modification time of the file
struct stat initial_mod_time;

void set_mod_time(char* path) {
    // Get the initial modification time of the file
    stat(path, &initial_mod_time);
}

int was_modified(char* path) {
    struct stat current_mod_time;
    // Get the current modification time of the file
    stat(path, &current_mod_time);

    int changed = initial_mod_time.st_mtime != current_mod_time.st_mtime;
    if (changed) {
        // initial_mod_time = current_mod_time;
    }
    return changed;
}


char* load_file(const char* filename) {
    // Open the HTML file
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen failed");
        return NULL;
    }

    // Determine the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Read the contents of the file into a buffer
    char* file_buffer = malloc(file_size + 1);
    fread(file_buffer, 1, file_size, file);
    file_buffer[file_size] = '\0';

    // Close the file
    fclose(file);

    return file_buffer;
}