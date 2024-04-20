// #define zoxel_debug_base_path
// todo: make sure to copy folder, with bash, resources into:
//      > /build/android-build/app/src/main/assets/resources
/*#ifdef zoxel_on_web
#define resources_dir_name "resources"
#else
#define resources_dir_name "resources"
#endif*/
#ifndef resources_dir_name
    #define resources_dir_name "resources"
#endif
const char *data_path = NULL;
char *resources_path = NULL;

#if defined(zoxel_on_windows) && !defined(_WINE) //__WINE__)
    #define character_slash "\\"
#else
    #define character_slash "/"
#endif

#ifndef zoxel_on_android
    #define resources_folder_name resources_dir_name character_slash
#else
    // i will have to manually add in the resource directories for android until ndk updates
    #define resources_folder_name character_slash resources_dir_name character_slash
    #define voxes_folder_path "voxes"
    #define textures_folder_path "textures"
    #include <SDL_system.h>
    #include <android/asset_manager.h>
    #include <android/asset_manager_jni.h>
    #include <sys/stat.h>
    #include <sys/types.h>

    void delete_directory_recursive(const char* path) {
        DIR* dir = opendir(path);
        if (dir != NULL) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
                char* sub_path = (char*) malloc(strlen(path) + strlen(entry->d_name) + 2);
                sprintf(sub_path, "%s/%s", path, entry->d_name);
                if (entry->d_type == DT_DIR) delete_directory_recursive(sub_path);
                else remove(sub_path);
                free(sub_path);
            }
            closedir(dir);
            rmdir(path);
        } else {
            zox_log("Error opening directory %s: %s\n", path, strerror(errno))
        }
    }

    unsigned char create_directory(const char* path) {
        if (mkdir(path, 0777) != 0) {
            zox_log(" !!! directory failed to create [%s]\n", path)
            return 1;
        } else {
            return 0;
        }
    }

    AAssetManager* get_asset_manager() {
#ifdef zoxel_using_sdl
            JNIEnv* env = (JNIEnv*) SDL_AndroidGetJNIEnv();
            jobject activity = (jobject) SDL_AndroidGetActivity();
#else
            JNIEnv* env = NULL;
            jobject activity = NULL;
#endif
        jclass activityClass = (*env)->GetObjectClass(env, activity);
        jmethodID methodID = (*env)->GetMethodID(env, activityClass, "getAssets", "()Landroid/content/res/AssetManager;");
        jobject assetManager = (*env)->CallObjectMethod(env, activity, methodID);
        AAssetManager* asset_manager = AAssetManager_fromJava(env, assetManager);
        return asset_manager;
    }

    void copy_resources_directory(AAssetManager* asset_manager, const char* source_path, const char* destination_path) {
        AAssetDir* asset_directory = AAssetManager_openDir(asset_manager, source_path);
        if (!asset_directory) {
            zox_log("   ! android source directory does not exist [%s]\n", source_path)
            return;
        }
        zox_log(" + copying resources from [%s] to [%s]\n", source_path, destination_path)
        // zox_log("     + asset source directory exists [%s]\n", source_path)
        int files_count = 0;
        const char* filename = NULL;
        create_directory(destination_path); // create the directory we are copying to
        while ((filename = AAssetDir_getNextFileName(asset_directory)) != NULL) {
            char full_source_path[512]; // asset folder
            char full_destination_path[512];    // internal storage
            sprintf(full_source_path, "%s/%s", source_path, filename);
            sprintf(full_destination_path, "%s/%s", destination_path, filename);
            AAsset* asset = AAssetManager_open(asset_manager, full_source_path, AASSET_MODE_BUFFER);
            if (asset) {
                const void* data = AAsset_getBuffer(asset);
                if (data) {
                    size_t size = AAsset_getLength(asset);
                    zox_log("         + copying [%s] to [%s] size [%i]\n", full_source_path, full_destination_path, (int) size)
                    // zox_log("         + asset opened size [%i]\n", (int) size)
                    // Open the destination file on the device's internal storage
                    FILE* destination_file = fopen(full_destination_path, "wb");
                    if (destination_file) {
                        fwrite(data, size, 1, destination_file);
                        fclose(destination_file);
                    } else zox_log("            ! file opened is null [%s]\n", full_destination_path)
                } else zox_log("     - asset data is null [%s]\n", full_source_path)
                AAsset_close(asset);
            } else  zox_log("         ! asset failed to open [%s]\n", full_source_path)
            files_count++;
        }
        AAssetDir_close(asset_directory);
        zox_log("         + total files was [%i]\n", files_count)
    }

    // zoxel_log("     + directory has sub directories count [%i]\n", num_of_directories);
    // Iterate over all the files in the directory and copy them to the destination path
    // If the file is a directory, recursively copy its contents
    // zoxel_log("     > is directory? [%s]\n", full_source_path);
    // Open the source file in the APK's assets folder
    // zoxel_log("         - file opened [%s]\n", full_destination_path);
    // zoxel_log("         - file contents copied [%s]\n", full_destination_path);

    void decompress_android_resources() {
        zox_logg("   > zoxel: decompressing android resources from jar\n")
        AAssetManager *assetManager = get_asset_manager();
        delete_directory_recursive(resources_path);
        create_directory(resources_path);
        char *path2 = malloc(strlen(resources_path) + strlen(voxes_folder_path) + 1);
        strcpy(path2, resources_path);
        strcat(path2, voxes_folder_path);
        copy_resources_directory(assetManager, "resources/"voxes_folder_path, path2);
        free(path2);
        char *path3 = malloc(strlen(resources_path) + strlen(textures_folder_path) + 1);
        strcpy(path3, resources_path);
        strcat(path3, textures_folder_path);
        copy_resources_directory(assetManager, "resources/"textures_folder_path, path3);
        free(path3);
        // copy_resources_directory(assetManager, resources_path, "resources");
        //create_directory(path2);
        //create_directory(path3);
    }
#endif

void debug_base_path(const char *base_path) {
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(base_path)) != NULL) {
        zox_log(" > directories and files in [%s]\n", base_path)
        while ((entry = readdir(dir)) != NULL) zox_log("     + [%s]\n", entry->d_name)
        closedir(dir);
    } else zox_log(" - failed to open directory [%s]\n", base_path)
}

char* concat_file_path(const char* resources_path, const char* file_path) {
    if (resources_path == NULL || file_path == NULL) return NULL;
    char* full_file_path = malloc(strlen(resources_path) + strlen(file_path) + 1);
    strcpy(full_file_path, resources_path);
    strcat(full_file_path, file_path);
    return full_file_path;
}

char* get_full_file_path(const char* filepath) {
    char* fullpath = malloc(strlen(data_path) + strlen(filepath) + 1);
    strcpy(fullpath, data_path);
    strcat(fullpath, filepath);
#ifdef zoxel_debug_pathing
    zox_log("fullpath: %s\n", fullpath)
#endif
    return fullpath;
}

void convert_file_path_slashes(char* path) {
    while (*path) {
        if (*path == '\\') {
            *path = '/';
        }
        ++path;
    }
}

char* clone_str(const char* text) {
    int length = strlen(text);
    char *new_text = malloc(length);
    memcpy(new_text, text, length);
    return new_text;
}

unsigned char initialize_pathing() {
#ifdef zox_disable_io
    return EXIT_SUCCESS;
#endif
    char* base_path;
#ifdef zoxel_using_sdl
    #ifdef zoxel_on_android
    base_path = clone_str(SDL_AndroidGetInternalStoragePath());
    __android_log_print(ANDROID_LOG_VERBOSE, "Zoxel", "base_path [%s]", base_path);
    #else
    base_path = SDL_GetBasePath();
#ifdef zoxel_on_windows
    // convert_file_path_slashes(base_path);
#endif
    /*zox_log("   + base_path [%s]\n", base_path)
    if (is_platform_wine()) {
        zox_logg("wine platform\n")
        convert_file_path(base_path);
    } else exit(0);*/
    #endif
#else
    // can i use a base path here based on platform?
    base_path = NULL;
    return EXIT_FAILURE;
#endif
#ifdef zoxel_debug_base_path
    debug_base_path(base_path);
#endif
    if (base_path) data_path = base_path;
#ifdef zoxel_using_sdl
    else data_path = SDL_strdup("./");
#endif
    zox_log(" + opening base_path [%s]\n", base_path)
    DIR* dir = opendir(base_path);
    if (dir) {
#ifdef zoxel_debug_pathing
        zox_log(" + base path exists [%s]\n", data_path)
#endif
        // resources_path = resources_folder_name; // malloc(strlen(resources_folder_name) + 1);
        // strcat(resources_path, resources_folder_name);
        resources_path = malloc(strlen(base_path) + strlen(resources_folder_name) + 1);
        strcpy(resources_path, base_path);
        strcat(resources_path, resources_folder_name);
        zox_log(" > resources_folder_name [%s] resources_path [%s]\n", resources_folder_name, resources_path)
#ifdef zoxel_on_android
        decompress_android_resources();
#endif
        DIR* dir2 = opendir(resources_path);
        if (dir2) {
#ifdef zoxel_debug_pathing
            zox_log("     + resources path is [%s]\n", resources_path)
#endif
            closedir(dir2);
        } else {
            zoxel_log(" !!! resources_path does not exist [%s]\n", resources_path);
        }
        closedir(dir);
        // free(resources_path);
    } else if (ENOENT == errno) {
        zoxel_log("SDL data_path (DOES NOT EXIST): %s\n", data_path);
    } else {
        zoxel_log("SDL data_path (MYSTERIOUSLY DOES NOT EXIST): %s\n", data_path);
    }
    return EXIT_SUCCESS;
}
