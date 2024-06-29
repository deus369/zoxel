

#define load_and_save_data(Name, name)\
\
void save_##name(const char *game, const char *filename, Name *data) {\
    char path[256];\
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
void load_##name(const char *game, const char *filename, Name *data) {\
    char path[256];\
    get_save_filepath(game, filename, path, sizeof(path));\
    FILE *file = fopen(path, "rb");\
    if (file == NULL) {\
        perror("Error opening file for reading");\
        return;\
    }\
    fread(data, sizeof(Name), 1, file);\
    fclose(file);\
    /*zox_log(" > loaded from [%s]\n", path)*/\
}
