#ifndef zox_disable_logs

#ifdef zoxel_on_android
    #include "android.c"
#else
    #include "default.c"
#endif

#define ARG_COUNT(...) (ARG_COUNT_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1, 0))
#define ARG_COUNT_IMPL(_1, _2, _3, _4, _5, count, ...) count

#define zox_log_basic(msg, ...) {\
    if (ARG_COUNT(__VA_ARGS__) == 0) {\
        zoxel_log_no_args(msg);\
    } else {\
        zoxel_log(msg, ##__VA_ARGS__);\
    }\
}

int clear_zoxel_log() {
    #ifdef log_to_file
    fclose(fopen("log.txt", "w"));
    #endif
    //zox_log(" > begin [%s]\n", "zox_logs")
    return 0;
}

#else

void zoxel_log(const char* msg, ...) { }

#define zox_log_basic(msg, ...) { }

int clear_zoxel_log() { return 0; }

int zoxel_log_error(void *stream, const char *msg, ...) { return 0; }

#endif