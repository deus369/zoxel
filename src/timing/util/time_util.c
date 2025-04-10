#define init_delta_time() const double delta_time = zox_delta_time;
#ifdef zox_mod_plots
    extern void add_plot_data_time(ecs_world_t *world, const double value);
#endif

double current_time_in_seconds() {
    struct timespec current_time;
    clock_gettime(CLOCK_REALTIME, &current_time);
    return current_time.tv_sec + (double) current_time.tv_nsec / 1000000000.0;
}

void initialize_time() {
    time_begin = current_time_in_seconds();
}

void skip_time_to_current() {
    zox_current_time = current_time_in_seconds() - time_begin;
    zox_delta_time = 0;
    // zox_log(" > restoring time to [%d]\n", zox_current_time)
}

void clear_system_times() {
    // for (int i = 0; i < record_frames_count; i++) system_times[i] = 0;
}

// todo: find a better way to grab time data in a new module

void iterate_time(ecs_world_t *world) {
    clear_system_times();
    double last_time = zox_current_time;
    zox_current_time = current_time_in_seconds() - time_begin;
    if (!updating_time) {
        zox_delta_time = 0;
        return;
    }
    zox_delta_time = zox_current_time - last_time;
    zox_current_time_check += zox_delta_time;
#ifdef zox_mod_plots
    add_plot_data_time(world, zox_delta_time);
#endif
    // todo: use a seperate physics time float? fixed_time?
#ifdef limit_time_delta
    if (zox_delta_time > max_zox_delta_time) {
        zox_delta_time = 0; // max_zox_delta_time;
    }
#endif
    // for (int i = 0; i < record_frames_count - 1; i++) zox_delta_times[i] = zox_delta_times[i + 1];
    // zox_delta_times[record_frames_count - 1] = zox_delta_time;
#ifdef zox_check_current_time
    if (zox_current_time != zox_current_time_check) {
        zox_log("current time and check not equal: %f - %f\n", zox_current_time, zox_current_time_check);
    }
#endif
    // zox_log("current time [%d]\n", zox_current_time);
    // zox_log("delta time [%f]\n", zox_delta_time * 1000.0);
    frames_count++;
    frames_per_second_time += zox_delta_time;
    if (frames_per_second_time >= 1.0) {
        frames_per_second_time -= 1.0;
        frames_per_second = frames_count;
        frames_count = 0;
#ifdef zoxel_log_frames_per_second
        zox_log("frames_per_second [%i]\n", frames_per_second);
#endif
    }
#ifdef zoxel_log_frame_ms
    zox_log(" > frame time [%fms]\n", (float) (zox_delta_time * 1000.0f))
#endif
}

float get_total_time_seconds() {
    return (float) (zox_current_time);
}
