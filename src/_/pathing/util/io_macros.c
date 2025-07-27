#define io_path_size 512

#define create_load_and_save_functions(Name, name)\
\
void save_##name(const char *game, const char *filename, Name *data) {\
    char path[io_path_size];\
    get_save_filepath(game, filename, path, sizeof(path));\
    FILE *file = fopen(path, "wb");\
    if (file == NULL) {\
        zox_log(" > error saving [%s]\n", path)\
        perror("Error opening file for writing");\
        return;\
    }\
    fwrite(data, sizeof(Name), 1, file);\
    fclose(file);\
    /*zox_log(" > saved to [%s]\n", path)*/\
}\
\
byte load_##name(const char *game, const char *filename, Name *data) {\
    char path[io_path_size];\
    get_save_filepath(game, filename, path, sizeof(path));\
    FILE *file = fopen(path, "rb");\
    if (file == NULL) {\
        perror("Error opening file for reading");\
        return 0;\
    }\
    size_t filesize = fread(data, sizeof(Name), 1, file);\
    fclose(file);\
    /*zox_log(" > loaded from [%s]\n", path)*/\
    return filesize > 0;\
}
