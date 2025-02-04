unsigned char get_cpu_tier(int core_count) {
#ifdef zox_log_cores
    zox_log(" + detected cpu cores [%i]\n", core_count)
#endif
    if (core_count > 8) {
        return 3;
    } else if (core_count > 6) {
        return 2;
    } else if (core_count > 4) {
        return 1;
    } else {
        return 0;
    }
}
