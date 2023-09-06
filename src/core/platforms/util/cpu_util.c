unsigned char get_cpu_tier(int core_count) {
    if (core_count > 8) {
        zoxel_log(" > high core count detected [%i]\n", core_count);
        return 3;
    } else if (core_count > 6) {
        zoxel_log(" > average core count detected [%i]\n", core_count);
        return 2;
    } else if (core_count > 4) {
        zoxel_log(" > low (-) core count detected [%i]\n", core_count);
        return 1;
    } else {
        zoxel_log(" > lowest core count detected [%i]\n", core_count);
        return 0;
    }
}