#ifdef zoxel_on_android
// #define zox_log_android_io
// i will have to manually add in the resource directories for android until ndk updates
// #define resources_folder_name character_slash resources_dir_name character_slash
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

byte create_directory(const char* path) {
    if (mkdir(path, 0777) != 0) {
        zox_log(" !!! directory failed to create [%s]\n", path)
        return 0;
    } else {
        return 1;   // success
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
    #ifdef zox_log_android_io
    zox_log(" > extracting directory from [%s]\n", source_path)
    zox_log("   > destination [%s]\n", destination_path)
    #endif
    AAssetDir* asset_directory = AAssetManager_openDir(asset_manager, source_path);
    if (!asset_directory) {
        zox_log("   ! android source directory does not exist [%s]\n", source_path)
        return;
    }
    // zox_log("     + asset source directory exists [%s]\n", source_path)
    const char* filename = NULL;
    if (!create_directory(destination_path)) { // create the directory we are copying to
        return;
    }
    #ifdef zox_log_android_io
    zox_log("   + created new directory [%s]\n", destination_path)
    #endif
    int files_count = 0;
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
                #ifdef zox_log_android_io
                zox_log("       - extracting bytes [%i] from [%s]\n", (int) size, full_source_path)
                zox_log("       + to [%s]\n", full_destination_path)
                #endif
                // zox_log("         + asset opened size [%i]\n", (int) size)
                // Open the destination file on the device's internal storage
                FILE* destination_file = fopen(full_destination_path, "wb");
                if (destination_file) {
                    fwrite(data, size, 1, destination_file);
                    fclose(destination_file);
                } else zox_log("    ! file opened is null [%s]\n", full_destination_path)
            } else zox_log("    ! asset data is null [%s]\n", full_source_path)
                AAsset_close(asset);
        } else  zox_log("         ! asset failed to open [%s]\n", full_source_path)
            files_count++;
    }
    AAssetDir_close(asset_directory);
    #ifdef zox_log_android_io
    zox_log("       - total files was [%i]\n", files_count)
    #endif
}

// zox_log("     + directory has sub directories count [%i]\n", num_of_directories);
// Iterate over all the files in the directory and copy them to the destination path
// If the file is a directory, recursively copy its contents
// zox_log("     > is directory? [%s]\n", full_source_path);
// Open the source file in the APK's assets folder
// zox_log("         - file opened [%s]\n", full_destination_path);
// zox_log("         - file contents copied [%s]\n", full_destination_path);

void decompress_android_directory(AAssetManager *assetManager, char *path) {
    char *path_input = malloc(strlen(resources_folder_name) + strlen(path) + 1);
    strcpy(path_input, resources_folder_name);
    strcat(path_input, path);
    char *path_output = malloc(strlen(resources_path) + strlen(path) + 1);
    strcpy(path_output, resources_path);
    strcat(path_output, path);
    copy_resources_directory(assetManager, path_input, path_output);
    free(path_input);
    free(path_output);
}

int resource_directories_length = 15;
char* resource_directories[] = {
    "voxes",
    "fonts",
    "music",
    "sounds",
    "textures",
    "textures/cursors",
    "textures/input",
    "textures/skills",
    "textures/taskbar",
    "textures/voxels",
    "textures/stats",
    "textures/stats/attributes",
    "textures/stats/base",
    "textures/stats/regens",
    "textures/stats/states",
};

void decompress_android_resources() {
    #ifdef zox_log_android_io
    zox_log(" > zoxel: decompressing android resources from jar\n")
    #endif
    AAssetManager *assetManager = get_asset_manager();
    delete_directory_recursive(resources_path);
    if (!create_directory(resources_path)) {
        return;
    }
    #ifdef zox_log_android_io
    zox_log(" + created new directory [%s]\n", resources_path)
    #endif
    // now copy all our data out
    for (int i = 0; i < resource_directories_length; i++) {
        decompress_android_directory(assetManager, resource_directories[i]);
    }
}
#endif
