#ifndef zox_disable_logs

#define ARG_COUNT(...) (ARG_COUNT_IMPL(__VA_ARGS__, 5, 4, 3, 2, 1, 0))
#define ARG_COUNT_IMPL(_1, _2, _3, _4, _5, count, ...) count

#define zox_log__(msg, ...) {\
    if (ARG_COUNT(__VA_ARGS__) == 0) {\
        zox_log_a(msg);\
    } else {\
        zox_log_(msg, ##__VA_ARGS__);\
    }\
}

int clear_logs() {
#ifdef log_to_file
    fclose(fopen("log.txt", "w"));
#endif
    //zox_log(" > begin [%s]\n", "zox_logs")
    return 0;
}

#else

#define zox_log__(msg, ...) { }

int clear_logs() { return 0; }

#endif