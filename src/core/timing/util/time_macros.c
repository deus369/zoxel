// timing system macros

#define clocks_per_second2 CLOCKS_PER_SEC
#define clocks_per_second CLOCKS_PER_SEC // 10000000.0 // 0
double time_app_started = 0;

#define clock_as_double (((double) clock()) / clocks_per_second)

#define begin_timing()\
unsigned char did_do = 0;\
double time_start = clock_as_double;
// clock_t

#define did_do_timing() if (did_do == 0) did_do = 1;

#define begin_timing_absolute()\
    begin_timing()\
    did_do_timing()

double get_time_seconds() {
    if (time_app_started == 0) time_app_started = clock_as_double;
    return clock_as_double - time_app_started;
}

#define get_timing_passed() clock_as_double - time_start

#ifdef zoxel_time_always
    #define end_timing(system_name)\
    double time_taken = get_timing_passed();\
    if (time_taken >= 1.0) {\
        zoxel_log("%s [%fs]\n", system_name, time_taken);\
    } else {\
        zoxel_log("%s [%fms]\n", system_name, 1000.0 * time_taken);\
    }
#else
    #define end_timing(system_name)\
    if (did_do) {\
        double time_taken = clock_as_double - time_start;\
        if (time_taken >= 1.0) {\
            zoxel_log("%s [%fs]\n", system_name, time_taken);\
        } else {\
            zoxel_log("%s [%fms]\n", system_name, 1000.0 * time_taken);\
        }\
    }
#endif

#define end_timing_absolute(system_name)\
    double time_taken = clock_as_double - time_start;\
    if (time_taken >= 1.0) {\
        zoxel_log("%s [%fs]\n", system_name, time_taken);\
    } else {\
        zoxel_log("%s [%fms]\n", system_name, 1000.0 * time_taken);\
    }


#define end_timing_cutoff(system_name, cuttoff)\
if (did_do) {\
    long double time_taken = clock_as_double - time_start;\
    if (time_taken >= 1.0) {\
        zoxel_log("%s [%Lgs] - [Seconds]\n", system_name, time_taken);\
    } else {\
        time_taken *= 1000.0;\
        if (time_taken >= cuttoff) {\
            zoxel_log("%s [%Lgms]\n", system_name, time_taken);\
        }\
    }\
}

#define time_cycle_begin() double cycle_start = clock_as_double;
#define time_cycle_end(system_name)\
double cycle_delta = clock_as_double - cycle_start;\
if (cycle_delta >= 1.0) {\
    zoxel_log("%s [%fs]\n", system_name, cycle_delta);\
} else {\
    zoxel_log("%s [%fms]\n", system_name, 1000.0 * cycle_delta);\
}
