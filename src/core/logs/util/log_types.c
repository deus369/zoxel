// log types

// io
#if defined(zox_enable_log_ios) && !defined(zox_disable_logs)
    #define zox_log_io(msg, ...) zox_log(msg, ##__VA_ARGS__)
#else
    #define zox_log_io(msg, ...) { }
#endif

// inputs
#if defined(zox_enable_log_input) && !defined(zox_disable_logs)
    #define zox_log_input(msg, ...) zox_log(msg, ##__VA_ARGS__)
#else
    #define zox_log_input(msg, ...) { }
#endif

// shaders
#if defined(zox_enable_log_shader) && !defined(zox_disable_logs)
    #define zox_log_shader(msg, ...) zox_log(msg, ##__VA_ARGS__)
#else
    #define zox_log_shader(msg, ...) { }
#endif

// uis
#if defined(zox_enable_log_ui) && !defined(zox_disable_logs)
    #define zox_log_ui(msg, ...) zox_log(msg, ##__VA_ARGS__)
#else
    #define zox_log_ui(msg, ...) { }
#endif

// realms
// games