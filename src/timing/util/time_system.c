
#define zox_profile_system_none 0
#define zox_profile_system_grassy_plains 1
#define zox_profile_system_vox_generation 2
#define zox_profile_system_chunk_builder_c 3
#define zox_profile_system_npc_spawns 4

byte profiler_state = zox_profile_system_none;

// zox_profile_system_none
// zox_profile_system_grassy_plains
// zox_profile_system_vox_generation
// zox_profile_system_chunk_builder_c
// profiler_state = zox_profile_system_grassy_plains;

// add these to system to debug
// zox_ts_begin(name);
// zox_ts_end(name, 3, zox_profile_system_type);

extern void add_plot_data_time_system(ecs_world_t *world, const double value);
double zox_delta_time_system = 0;

// main loop
void iterate_time_system(ecs_world_t *world) {
    add_plot_data_time_system(world, zox_delta_time_system);
    zox_delta_time_system = 0;
}

#define zox_ts_begin(N) \
    double system_start_##N = get_time_ms();

#define zox_ts_end(N, max_system_time, profile_type) \
    double total_time_##N = get_time_ms() - system_start_##N; \
    if (profiler_state == profile_type && total_time_##N > zox_delta_time_system) {\
        zox_delta_time_system = total_time_##N;\
        if (total_time_##N >= max_system_time) {\
            zox_log("- [%s]: %f", #N, total_time_##N); \
        }\
    }
