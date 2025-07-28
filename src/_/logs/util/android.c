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

/*#define zox_log(msg, ...) {\
if (ARG_COUNT(__VA_ARGS__) == 0) zoxel_log_no_args(msg);\
    else zoxel_log(msg, ##__VA_ARGS__);\
}*/

int zoxel_log_error(void *stream, const char *msg, ...) {
    return 0;
}