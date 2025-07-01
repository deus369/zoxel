// logging
// #define zox_enable_log_streaming
#if defined(zox_enable_log_streaming) && !defined(zox_disable_logs)
    #define zox_log_streaming(msg, ...) zox_log_line(msg, ##__VA_ARGS__)
#else
    #define zox_log_streaming(msg, ...) { }
#endif