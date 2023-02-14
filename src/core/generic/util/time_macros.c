// timing system macros

#define begin_timing()\
unsigned char did_do = 0;\
clock_t time_start = clock();

#define did_do_timing() if (did_do == 0) did_do = 1;

#define end_timing(system_name)\
if (did_do)\
{\
    clock_t time_end = clock();\
    long double time_taken = 0.1 * ((long double) (time_end - time_start) / CLOCKS_PER_SEC);\
    if (time_taken >= 1.0)\
    {\
        printf("%s [%Lgs]\n", system_name, time_taken);\
    }\
    else\
    {\
        time_taken *= 1000.0;\
        printf("%s [%Lgms]\n", system_name, time_taken);\
    }\
}
