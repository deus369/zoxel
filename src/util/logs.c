// different platform based logs
#ifdef zoxel_on_android
    #include <android/log.h>
    #define APPNAME "Zoxel"
#endif

#define max_log_length 256
#define max_characters_log 512

//! Included Libraries for App
#ifndef zox_disable_logs
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <strings.h>
// #include <errno.h>   // do I need this?
#endif

// Helper macro to count the number of arguments
#define ARG_COUNT(...) (ARG_COUNT_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1, 0))
#define ARG_COUNT_IMPL(_1, _2, _3, _4, _5, count, ...) count

#define debug_logs_countof(A) (sizeof(A) / sizeof(A[0]))

#ifndef zox_disable_logs

#ifdef zoxel_on_android

void zoxel_log(const char* format, ...) {
    char msg[max_characters_log] = { 0 };
    va_list args;
    va_start(args, format);
    vsprintf(msg, format, args); // less safe, can lead to buffer overflows
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "%s", msg);
}

void zoxel_log_no_args(const char* msg) {
    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "%s", msg);
}

#define zox_log(msg, ...) {\
    if (ARG_COUNT(__VA_ARGS__) == 0) zoxel_log_no_args(msg);\
    else zoxel_log(msg, ##__VA_ARGS__);\
}

int zoxel_log_error(void *stream, const char *msg, ...) {
    return 0;
}

#else

const char *reset = "\x1b[0m";
const char *red = "\x1b[31m";
const char *green = "\x1b[32m";
const char *yellow = "\x1b[33m";
const char *blue = "\x1b[34m";
const char *magenta = "\x1b[35m";
const char *cyan = "\x1b[36m";

void zoxel_log(const char* msg, ...) {
    va_list a;
    va_start(a, msg);
    char msg2[max_characters_log] = { 0 };
    // vsnprintf(msg2, debug_logs_countof(msg2), msg, a);
    vsnprintf(msg2, sizeof(msg2), msg, a);
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

#define zox_log(msg, ...) {\
    if (ARG_COUNT(__VA_ARGS__) == 0) zoxel_log_no_args(msg);\
    else zoxel_log(msg, ##__VA_ARGS__);\
}

#endif

#else

void zoxel_log(const char* msg, ...) { }
#define zox_log(msg, ...) { }

#endif

int clear_zoxel_log() {
#ifdef log_to_file
    fclose(fopen("log.txt", "w"));
#endif
    zox_log(" > begin [%s]\n", "zox_logs")
    return 0;
}


// printf(msg, __VA_ARGS__);
/*va_list a;\
va_start(a, msg);\
char msg2[max_log_length] = { 0 };\
vsnprintf(msg2, debug_logs_countof(msg2), msg, a);\
fputs(msg2, stderr);\
va_end(a);\*/
