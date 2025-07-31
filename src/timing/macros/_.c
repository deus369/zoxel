// time function

#define define_fun_stopwatch(name, d)\
    byte zox_##name = d;

#define startwatch(name) \
    double section_time = 0; \
    double section_sum = 0; \
    double start_total = get_time_ms(); \
    double start = get_time_ms(); \
    if (zox_##name) { \
        zox_log("-> Stopwatch Started [%s]: %.01fms", #name, start_total); \
    }

#define tapwatch(name, label)\
    section_time = get_time_ms() - start;\
    section_sum += section_time;\
    if (zox_##name) { \
        zox_log("   - "label": %.01fms", section_time); \
    } \
    start = get_time_ms();


#define endwatch(name, label) \
    double total_time = get_time_ms() - start_total; \
    if (zox_##name) { \
        zox_log("->"label"| Total Time: %.2fms, Unaccounted: %.2fms", total_time, total_time - section_sum); \
    }
