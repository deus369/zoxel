void zox_log_a(const char* format, ...) {
    char log[max_characters_log] = { 0 };
    va_list args;
    va_start(args, format);
    vsprintf(log, format, args); // less safe, can lead to buffer overflows
    vsnprintf(log, sizeof(log), format, args);
    va_end(args);
    __android_log_print(ANDROID_LOG_INFO, "SDL", log);
}

void zox_log__(const char* log) {
    __android_log_print(ANDROID_LOG_INFO, "SDL", log);
}

/*#define zox_log_a(...) ((void)__android_log_print(ANDROID_LOG_INFO, "SDL", __VA_ARGS__))

#define zox_log_() ((void)__android_log_print(ANDROID_LOG_INFO, "SDL")*/