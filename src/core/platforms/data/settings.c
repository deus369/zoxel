// #define zox_log_cores
byte cpu_core_count;
byte cpu_tier;

void fetch_pc_info() {
    cpu_core_count = get_cpu_count();
    cpu_tier = get_cpu_tier(cpu_core_count);
    // zox_log(" > CPU CORES [%i]\n", cpu_core_count)
}