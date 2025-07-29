void zox_log_internal(const char* format, ...) {
    char msg[max_characters_log] = { 0 };
    va_list args;
    va_start(args, format);
    vsprintf(msg, format, args); // less safe, can lead to buffer overflows
    vsnprintf(msg, sizeof(msg), format, args);
    va_end(args);
    __android_log_print(ANDROID_LOG_INFO, "SDL", "%s", msg);
}

void zox_log_internal__(const char* msg) {
    __android_log_print(ANDROID_LOG_INFO, "SDL", "%s", msg);
}