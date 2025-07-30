#define zox_log_android_io

#ifdef zox_windows
    #define character_slash "\\"
    #define char_slash '\\'
#else
    #define character_slash "/"
    #define char_slash '/'
#endif

#define resources_dir_name "res"
#define resources_folder_name resources_dir_name character_slash

#ifdef _WIN32
    #define PATH_SIZE MAX_PATH
#else
    #ifndef PATH_MAX
        #define PATH_MAX 4096
    #endif
    #define PATH_SIZE PATH_MAX
#endif

#define get_asset_path(folder_path, filename) \
    concat_file_path(resources_path, folder_path character_slash filename);

const char* data_path = NULL;
char* resources_path = NULL;
char* raw_path = NULL;