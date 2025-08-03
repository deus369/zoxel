extern void add_plot_data_time_system(ecs_world_t *world, const double value);
double zox_delta_time_system = 0;

void iterate_time_system(ecs_world_t *world) {
    add_plot_data_time_system(world, zox_delta_time_system);
    zox_delta_time_system = 0;
}

#define zox_start_time_system() \
    double system_start = get_time_ms();


#define zox_end_time_system() \
    double total_time = get_time_ms() - system_start; \
    if (total_time > zox_delta_time_system) {\
        zox_delta_time_system = total_time;\
        if (total_time >= 5) {\
            zox_log("- t %f", total_time); \
        }\
    }
