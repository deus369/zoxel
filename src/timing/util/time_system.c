extern void add_plot_data_time_system(ecs_world_t *world, const double value);
double zox_delta_time_system = 0;

// main loop
void iterate_time_system(ecs_world_t *world) {
    add_plot_data_time_system(world, zox_delta_time_system);
    zox_delta_time_system = 0;
}

// add these to system to debug
// zox_ts_begin(grassy_plains);
// zox_ts_end(grassy_plains, 5);

#define zox_ts_begin(N) \
    double system_start_##N = get_time_ms();

#define zox_ts_end(N, max_system_time, is_profile) \
    double total_time_##N = get_time_ms() - system_start_##N; \
    if (is_profile && total_time_##N > zox_delta_time_system) {\
        zox_delta_time_system = total_time_##N;\
        if (total_time_##N >= max_system_time) {\
            zox_log("- [%s]: %f", #N, total_time_##N); \
        }\
    }
