#ifdef zox_android

int directory_exists(const char *path) {
    struct stat info;
    if (stat(path, &info) != 0) {
        // Can't access path (doesn't exist or other error)
        return 0;
    } else {
        // Check if it is a directory
        return (info.st_mode & S_IFDIR) != 0;
    }
}

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
        zox_log_error("directory failed to create [%s]", path)
        return 0;
    } else {
        return 1;   // success
    }
}

byte android_create_directory_r(const char* path) {
    if (directory_exists(path)) {
        return 1;
    }
    char parent[1024];
    strcpy(parent, path);
    // remove last directory component from parent
    char* last_slash = strrchr(parent, '/');
    if (last_slash) {
        *last_slash = 0;
        if (!android_create_directory_r(parent)) {
            return 0;
        }
    }
    return mkdir(path, 0777) == 0 || errno == EEXIST;
}


AAssetManager* get_asset_manager() {
    JNIEnv* env = (JNIEnv*) SDL_AndroidGetJNIEnv();
    if (!env) {
        zox_log_error("SDL_AndroidGetJNIEnv() returned NULL");
        return NULL;
    }

    jobject activity = (jobject) SDL_AndroidGetActivity();
    if (!activity) {
        zox_log_error("SDL_AndroidGetActivity() returned NULL");
        return NULL;
    }

    jclass activityClass = (*env)->GetObjectClass(
        env,
        activity);
    if (!activityClass) {
        zox_log_error("GetObjectClass failed");
        return NULL;
    }

    jmethodID methodID = (*env)->GetMethodID(
        env,
        activityClass,
        "getAssets",
        "()Landroid/content/res/AssetManager;");
    if (!methodID) {
        zox_log_error("GetMethodID failed for getAssets()");
        return NULL;
    }

    jobject assetManagerObj = (*env)->CallObjectMethod(
        env,
        activity,
        methodID);
    if (!assetManagerObj) {
        zox_log_error("CallObjectMethod returned NULL for getAssets()");
        return NULL;
    }

    AAssetManager* manager = AAssetManager_fromJava(env, assetManagerObj);
    if (!manager) {
        zox_log_error("AAssetManager_fromJava() failed");
        return NULL;
    }

    return manager;
}

// remember - source is assets, the jar apk
void extract_android_assets(
    AAssetManager* asset_manager,
    const char* source_path,
    const char* destination_path)
{
    zox_logv("📦 Decompressing [%s] -> [%s]", source_path, destination_path)

    AAssetDir* asset_dir = AAssetManager_openDir(asset_manager, source_path);
    if (!asset_dir) {
        zox_log_error("asset directory does not exist [%s]", source_path)
        return;
    }

    if (!android_create_directory_r(destination_path)) {
        zox_log_error("Failed Destination Directory [%s]", destination_path)
        return;
    }

    zox_logv("Success creating directory [%s]", destination_path)
    const char* filename = NULL;
    while ((filename = AAssetDir_getNextFileName(asset_dir)) != NULL) {

        char nested_source_path[1024];
        char nested_dest_path[1024];
        // snprintf(nested_source_path, sizeof(nested_source_path), "%s/%s", source_path, filename);
        // snprintf(nested_dest_path, sizeof(nested_dest_path), "%s/%s", destination_path, filename);
        snprintf(nested_source_path, sizeof(nested_source_path), "%s%s%s",
                 source_path,
                 (source_path[strlen(source_path) - 1] == '/') ? "" : "/",
                 filename);
        snprintf(nested_dest_path, sizeof(nested_dest_path), "%s%s%s",
                 destination_path,
                 (destination_path[strlen(destination_path) - 1] == '/') ? "" : "/",
                 filename);


        AAsset* asset = AAssetManager_open(
            asset_manager,
            nested_source_path,
            AASSET_MODE_BUFFER);

        if (asset) {
            const void* data = AAsset_getBuffer(asset);
            size_t size = AAsset_getLength(asset);
            FILE* out = fopen(nested_dest_path, "wb");
            if (data && out && size) {
                zox_logv("  + asset opened size [%i]", (int) size)
                fwrite(data, size, 1, out);
                fclose(out);
            } else {
                zox_log_error("⚠️ failed writing to [%s]", nested_dest_path);
            }
            AAsset_close(asset);
        } else {
            // zox_log_error("asset failed to open [%s]", full_source_path)
            // Not a file? Treat it as a nested directory.
            zox_logv("📁 found nested directory: [%s]", nested_source_path, nested_dest_path);
            extract_android_assets(asset_manager, nested_source_path, nested_dest_path);
        }
    }

    AAssetDir_close(asset_dir);
}

void extract_android_assets_init(AAssetManager *assetManager, char *path) {
    char path_input[1024];
    char path_output[1024];
    snprintf(path_input, 1024, "%s%s", resources_folder_name, path);
    snprintf(path_output, 1024, "%s%s", resources_path, path);
    extract_android_assets(assetManager, path_input, path_output);
}

// todo: when building, we create a txt file with resource paths
void decompress_android_resources(const char* resources_path) {
    if (!resources_path) {
        zox_log_error("[decompress_android_resources]: resources_path is null.")
        return;
    }
    zox_logv("Initial Decompression at [%s]", resources_path);
    AAssetManager *manager = get_asset_manager();
    if (!manager) {
        zox_log_error("[decompress_android_resources]: Android AssetManager Null")
        return;
    }
    zox_logv("Deleting old Resources [%s]", resources_path);
    delete_directory_recursive(resources_path);

    zox_logv("Creating Export Path [%s]", resources_path);
    if (!android_create_directory_r(resources_path)) {
        zox_log_error("[decompress_android_resources]: could not create directory: %s", resources_path)
        return;
    }
    zox_logv("Created new directory [%s]", resources_path);
    // extract_android_assets_init(manager, "");
    extract_android_assets(manager, resources_dir_name, resources_path);
    // now copy all our data out
    /*for (int i = 0; i < resource_directories_length; i++) {
        extract_android_assets(manager, resource_directories[i]);
    }*/
}

#endif