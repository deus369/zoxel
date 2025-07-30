// log implementation
#ifndef zox_disable_logs
    #ifdef zox_android

        #define zox_log_(msg, ...) \
            __android_log_print(ANDROID_LOG_INFO, "SDL", "zox_log: "msg, ##__VA_ARGS__);

    #else
        #include "default.c"

        #define ARG_COUNT(...) (ARG_COUNT_IMPL(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
        # define ARG_COUNT_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, count, ...) count

        #define zox_log_(msg, ...) {\
            if (!ARG_COUNT(__VA_ARGS__)) {\
                zox_log__(msg);\
            } else {\
                zox_log_a(msg, ##__VA_ARGS__);\
            }\
        }
    #endif

    int clear_logs() {
#ifdef log_to_file
        fclose(fopen("log.txt", "w"));
#endif
        return 0;
    }

#else

    #define zox_log_(msg, ...) { }

    int clear_logs() { return 0; }

#endif

#define zox_logv(msg, ...) \
    if (zox_verbose) zox_log_("⚡️ "msg"\n", ##__VA_ARGS__);

#define zox_log(msg, ...) \
    zox_log_("> "msg"\n", ##__VA_ARGS__);

#define zox_log_error(msg, ...) \
    zox_log_("❌ "msg"\n", ##__VA_ARGS__);

#define zox_log_warning(msg, ...) \
    zox_log_("⚠️ "msg"\n", ##__VA_ARGS__);

#define zox_log_io(msg, ...) \
    if (is_log_io) zox_log(msg, ##__VA_ARGS__);

#define zox_log_info(msg, ...) \
    zox_log_("ℹ️ " msg "\n", ##__VA_ARGS__)

#define zox_log_debug(msg, ...) \
    if (zox_verbose) zox_log_("🐞 DEBUG: " msg "\n", ##__VA_ARGS__)

#define zox_log_success(msg, ...) \
    zox_log_("✅ " msg "\n", ##__VA_ARGS__)

#define zox_log_critical(msg, ...) \
    zox_log_("🔥 CRITICAL: " msg "\n", ##__VA_ARGS__)


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

// error no
#define zox_log_errno(msg, ...) \
    zox_log("%s: [%s] %s", msg, strerror(errno), ##__VA_ARGS__)
