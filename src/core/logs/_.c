#ifndef zox_mod_logs
#define zox_mod_logs

// different platform based logs
// android
#ifdef zoxel_on_android
    #include <android/log.h>
    #define APPNAME "Zoxel"
#endif

//! Included Libraries for App
#ifndef zox_disable_logs
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <strings.h>
    // #include <errno.h>   // do I need this?
#endif

// settings
#define max_log_length 256
#define max_characters_log 512

#ifndef zox_disable_logs
    #ifdef zoxel_on_android
        #include "util/android.c"
    #else
        #include "util/default.c"
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

#else
    #include "util/disabled.c"
#endif

#define zox_log(msg, ...)\
    zox_log_basic(msg"\n", ##__VA_ARGS__)

#define zox_log_error(msg, ...)\
    zox_log_basic("! "msg"\n", ##__VA_ARGS__)

#define zox_log_warning(msg, ...)\
    zox_log_basic("@ "msg"\n", ##__VA_ARGS__)

int clear_zoxel_log() {
    #ifdef log_to_file
        fclose(fopen("log.txt", "w"));
    #endif
    //zox_log(" > begin [%s]\n", "zox_logs")
    return 0;
}

#include "util/log_types.c"

#endif