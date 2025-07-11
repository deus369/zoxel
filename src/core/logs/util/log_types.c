// log types
unsigned char is_log_io = 0;

#define zox_log_io(msg, ...)\
    if (is_log_io) { zox_log(msg, ##__VA_ARGS__) }


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