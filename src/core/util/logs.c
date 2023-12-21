// different platform based logs
#ifdef zoxel_on_android
    #include <android/log.h>
    #define APPNAME "Zoxel"
#endif

#define max_log_length 256

//! Included Libraries for App
#ifndef zox_disable_logs
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
// #include <errno.h>   // do I need this?
#endif

// Helper macro to count the number of arguments
#define ARG_COUNT(...) (ARG_COUNT_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1, 0))
#define ARG_COUNT_IMPL(_1, _2, _3, _4, _5, count, ...) count
// #define ARG_COUNT_IMPL(_1, _2, _3, _4, _5, N, ...) N
// #define ARG_COUNT(...) (ARG_COUNT_IMPL(dummy, ##__VA_ARGS__, 5, 4, 3, 2, 1, 0) - 1)


#define debug_logs_countof(A) (sizeof(A) / sizeof(A[0]))

int clear_zoxel_log() {
#ifdef log_to_file
    fclose(fopen("log.txt", "w"));
#endif
    return 0;
}

#ifndef zox_disable_logs

#ifdef zoxel_on_android

// #define zoxel_log(debug_line) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, debug_line);
// #define zoxel_log(debug_line, ...) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, debug_line, __VA_ARGS__);
// #define zoxel_log(debug_line, ...) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, debug_line);

void zoxel_log(const char* msg, ...) {
#ifndef zox_disable_logs
        va_list a;
        va_start(a, msg);
        char msg2[1024] = { 0 };
        vsnprintf(msg2, debug_logs_countof(msg2), msg, a);
        fputs(msg2, stderr);
        // __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, msg2);
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "%s", msg2);
#endif
}

int zoxel_log_error(void *stream, const char *msg, ...) {
    return 0;
}

#define zox_logg(msg) {\
    fputs(msg, stderr);\
}

#define zox_log(msg, ...) {\
    zoxel_log(msg, __VA_ARGS__);\
}

/*#define zox_log(msg, ...) {\
    va_list a;\
    va_start(a, msg);\
    char msg2[max_log_length] = { };\
    vsnprintf(msg2, debug_logs_countof(msg2), msg, a);\
    fputs(msg2, stderr);\
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "%s", msg2);\
}*/

#else

const char *reset = "\x1b[0m";
const char *red = "\x1b[31m";
const char *green = "\x1b[32m";
const char *yellow = "\x1b[33m";
const char *blue = "\x1b[34m";
const char *magenta = "\x1b[35m";
const char *cyan = "\x1b[36m";

// #define zoxel_log(debug_line) printf(debug_line);
// #define zoxel_log(debug_line, ...) printf(debug_line, __VA_ARGS__); // #
void zoxel_log(const char* msg, ...) {
    va_list a;
    va_start(a, msg);
    char msg2[1024] = { 0 };
    vsnprintf(msg2, debug_logs_countof(msg2), msg, a);
#ifdef log_to_file
    FILE* f = fopen("log.txt", "a");
    if (f) {
        fputs(msg2, f);
        fclose(f);
    }
#else
    fputs(green, stdout);
    fputs(msg2, stderr);
    fputs(reset, stderr);
    // printf(msg2);
#endif
    va_end(a);
}

void zoxel_log_no_args(const char* msg) {
#ifdef log_to_file
    FILE* f = fopen("log.txt", "a");
    if (f) {
        fputs(msg, f);
        fclose(f);
    }
#else
    fputs(red, stderr);
    fputs(msg, stderr);
    fputs(reset, stderr);
#endif
}

int zoxel_log_error(void *stream, const char *msg, ...) {
    //    return fprintf((FILE*) stream, msg, __VA_ARGS__);
    return 0;
}

#define zox_logg(msg) { zoxel_log_no_args(msg); }

// fputs(msg, stderr);
/*zoxel_log(" = [args count %i]:\n", ARG_COUNT(__VA_ARGS__));\
zoxel_log_no_args(msg);\*/

#define zox_log(msg, ...) {\
    if (ARG_COUNT(__VA_ARGS__) == 0) {\
        zoxel_log_no_args(msg);\
    } else {\
        zoxel_log(msg, ##__VA_ARGS__);\
    }\
}
#endif

#else

void zoxel_log(const char* msg, ...) { }
#define zox_log(msg, ...) { }

#endif

// FILE *stream
/*
                    zoxel_log(msg, __VA_ARGS__);\
*/


// printf(msg, __VA_ARGS__);
/*va_list a;\
va_start(a, msg);\
char msg2[max_log_length] = { 0 };\
vsnprintf(msg2, debug_logs_countof(msg2), msg, a);\
fputs(msg2, stderr);\
va_end(a);\*/
