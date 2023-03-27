
#ifdef ANDROID_BUILD
    #define resources_folder_name "android-resources/"
#else
    #ifdef WINDOWS_BUILD
        #define resources_folder_name "resources\\"
    #else
        #define resources_folder_name "resources/"
    #endif
#endif
#include <dirent.h>
#include <errno.h>
char *data_path = NULL;
char *resources_path = NULL;

void set_data_path() {
    #ifdef ANDROID_BUILD
        char *base_path = SDL_GetPrefPath("libsdl", "app");
        /*char *android_path = SDL_GetBasePath(); // SDL_AndroidGetInternalStoragePath();
        char *base_path = malloc(strlen(android_path) + 1 + 0); // 1
        strcpy(base_path, android_path);
        strcat(base_path, "");  // /*/
    #else
        char *base_path = SDL_GetBasePath();
    #endif
    if (base_path) {
        data_path = base_path;
    } else {
        data_path = SDL_strdup("./");
    }
    DIR* dir = opendir(base_path);
    if (dir) {
        #ifdef zoxel_debug_pathing
        zoxel_log("SDL data_path (EXISTS): %s\n", data_path);
        #endif
        /*char *path_test = malloc(strlen(base_path) + 1 + 1);
        strcpy(path_test, base_path);
        strcat(path_test, ".");
        DIR* dir3 = opendir(path_test);
        if (dir3)
        {
            zoxel_log(" -> path_test [%s]\n", path_test);
            struct dirent *dir3_data;
            while ((dir3_data = readdir(dir3)) != NULL)
            {
                zoxel_log("     -> child path [%s]\n", dir3_data->d_name);
            }
            closedir(dir3);
        }
        free(path_test);*/
        resources_path = malloc(strlen(base_path) + strlen(resources_folder_name) + 1); // char *
        strcpy(resources_path, base_path);
        strcat(resources_path, resources_folder_name);
        DIR* dir2 = opendir(resources_path);
        if (dir2) {
            //#ifdef zoxel_debug_pathing
                zoxel_log(" > resources path is [%s]\n", resources_path);
            //#endif
            closedir(dir2);
        } else {
            zoxel_log("resources_path (DOES NOT EXIST): %s\n", resources_path);
        }
        // free(resources_path);
    } else if (ENOENT == errno) {
        zoxel_log("SDL data_path (DOES NOT EXIST): %s\n", data_path);
    } else {
        zoxel_log("SDL data_path (MYSTERIOUSLY DOES NOT EXIST): %s\n", data_path);
    }
}

char* get_full_file_path(const char* filepath) {
    char* fullpath = malloc(strlen(data_path) + strlen(filepath) + 1);
    strcpy(fullpath, data_path);
    strcat(fullpath, filepath);
    #ifdef zoxel_debug_pathing
        zoxel_log("fullpath: %s\n", fullpath);
    #endif
    return fullpath;
}

char* concat_file_path(char* resources_path, char* file_path) {
    if (resources_path == NULL || file_path == NULL) {
        return NULL;
    }
    char* full_file_path = malloc(strlen(resources_path) + strlen(file_path) + 1);
    strcpy(full_file_path, resources_path);
    strcat(full_file_path, file_path);
    return full_file_path;
}