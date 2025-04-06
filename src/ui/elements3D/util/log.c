// #define zox_enable_log_elements3D
// #define zox_enable_log_text3D

#if defined(zox_enable_log_elements3D) && !defined(zox_disable_logs)
    #define zox_log_elements3D(msg, ...) zox_log_line(msg, ##__VA_ARGS__)
#else
    #define zox_log_elements3D(msg, ...) { }
#endif

#if defined(zox_enable_log_text3D) && !defined(zox_disable_logs)
    #define zox_log_text3D(msg, ...) zox_log_line(msg, ##__VA_ARGS__)
#else
    #define zox_log_text3D(msg, ...) { }
#endif