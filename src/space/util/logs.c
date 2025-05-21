// #define zox_enable_log_start_game

#if defined(zox_enable_log_start_game) && !defined(zox_disable_logs)
    #define zox_log_start_game(msg, ...) zox_log_line(msg, ##__VA_ARGS__)
#else
    #define zox_log_start_game(msg, ...) { }
#endif