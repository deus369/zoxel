// different platform based logs
#include "_includes.c"

#ifndef zox_disable_logs
    #ifdef zoxel_on_android
        #include "util/android.c"
    #else
        #include "util/default.c"
    #endif

    #define ARG_COUNT(...) (ARG_COUNT_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1, 0))
    #define ARG_COUNT_IMPL(_1, _2, _3, _4, _5, count, ...) count

    #define zox_log(msg, ...) {\
    if (ARG_COUNT(__VA_ARGS__) == 0) zoxel_log_no_args(msg);\
        else zoxel_log(msg, ##__VA_ARGS__);\
    }

#else
    #include "util/disabled.c"
#endif

#define zox_log_line(msg, ...) zox_log(msg"\n", ##__VA_ARGS__)

int clear_zoxel_log() {
    #ifdef log_to_file
        fclose(fopen("log.txt", "w"));
    #endif
    //zox_log(" > begin [%s]\n", "zox_logs")
    return 0;
}

#include "util/log_types.c"