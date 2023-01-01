// different platform based logs

//! Included Libraries for App
#ifdef zox_logs
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdarg.h>
    // #include <errno.h>   // do I need this?
#endif

#define debug_logs_countof(A) (sizeof(A) / sizeof(A[0]))

#ifdef ANDROID_BUILD
    #include <android/log.h>
    #define APPNAME "Zoxel"
    // #define zoxel_log(debug_line) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, debug_line);
    // #define zoxel_log(debug_line, ...) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, debug_line, __VA_ARGS__);
    // #define zoxel_log(debug_line, ...) __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, debug_line);
    void zoxel_log(const char* msg, ...)
    {
        #ifdef zox_logs
        va_list a;
        va_start(a, msg);
        char msg2[1024] = { 0 };
        vsnprintf(msg2, debug_logs_countof(msg2), msg, a);
        // fputs(msg2, stderr);
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, msg2);
        #endif
    }
#else
    // #define zoxel_log(debug_line) printf(debug_line);
    // #define zoxel_log(debug_line, ...) printf(debug_line, __VA_ARGS__); // #
    void zoxel_log(const char* msg, ...)
    {
        #ifdef zox_logs
            va_list a;
            va_start(a, msg);
            char msg2[1024] = { 0 };
            vsnprintf(msg2, debug_logs_countof(msg2), msg, a);
            fputs(msg2, stderr);
        #endif
    }

    // FILE *stream
    int zoxel_log_error(void *stream, const char *msg, ...)
    {
        #ifdef zox_logs
        //    return fprintf((FILE*) stream, msg, __VA_ARGS__);
        #endif
        return 0;
    }
#endif