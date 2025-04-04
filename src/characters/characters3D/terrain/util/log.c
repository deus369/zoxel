#if defined(zox_enable_log_spawning) && !defined(zox_disable_logs)
    #define zox_log_spawning(msg, ...) zox_log_line(msg, ##__VA_ARGS__)
#else
    #define zox_log_spawning(msg, ...) { }
#endif