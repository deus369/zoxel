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

// log types
// #define zox_enable_log_ios
#define zox_enable_log_input