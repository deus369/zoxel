// Helper macro to count the number of arguments
const char *reset = "\x1b[0m";
const char *red = "\x1b[31m";
const char *green = "\x1b[32m";
const char *yellow = "\x1b[33m";
const char *blue = "\x1b[34m";
const char *magenta = "\x1b[35m";
const char *cyan = "\x1b[36m";

void zox_log_internal(const char* msg, ...) {
    va_list a;
    va_start(a, msg);
    char msg2[max_characters_log] = { 0 };
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
    #endif
    va_end(a);
}

void zox_log_internal_(const char* msg) {
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