// timing system macros
#include <time.h>

#define clocks_per_second 1000000.0 // 0
double time_app_started = 0;

#define begin_timing()\
unsigned char did_do = 0;\
clock_t time_start = clock();

#define did_do_timing() if (did_do == 0) did_do = 1;

#define begin_timing_absolute()\
    begin_timing()\
    did_do_timing()

double get_time_seconds() {
    if (time_app_started == 0)
        time_app_started = (double) (clock() / clocks_per_second);
    return ((double) (clock() / clocks_per_second) - time_app_started);
}

#define get_timing_passed()\
     (double) (clock() - time_start) / CLOCKS_PER_SEC

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
        double time_taken = (double) (clock() - time_start) / clocks_per_second;\
        if (time_taken >= 1.0) {\
            zoxel_log("%s [%fs]\n", system_name, time_taken);\
        } else {\
            zoxel_log("%s [%fms]\n", system_name, 1000.0 * time_taken);\
        }\
    }
#endif

#define end_timing_absolute(system_name)\
    double time_taken = (double) (clock() - time_start) / CLOCKS_PER_SEC;\
    if (time_taken >= 1.0) {\
        zoxel_log("%s [%fs]\n", system_name, time_taken);\
    } else {\
        zoxel_log("%s [%fms]\n", system_name, 1000.0 * time_taken);\
    }


#define end_timing_cutoff(system_name, cuttoff)\
if (did_do) {\
    long double time_taken = ((long double) (clock() - time_start) / clocks_per_second);\
    if (time_taken >= 1.0) {\
        zoxel_log("%s [%Lgs] - [Seconds]\n", system_name, time_taken);\
    } else {\
        time_taken *= 1000.0;\
        if (time_taken >= cuttoff) {\
            zoxel_log("%s [%Lgms]\n", system_name, time_taken);\
        }\
    }\
}

/*
long double time_taken = ((long double) 0.1) * ((long double) (clock() - time_start) / CLOCKS_PER_SEC);\
    
    time_taken *= 1000.0;\
*/
