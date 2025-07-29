byte cpu_core_count;
byte cpu_tier;

void fetch_pc_info() {
    cpu_core_count = get_cpu_count();
    cpu_tier = get_cpu_tier(cpu_core_count);
}