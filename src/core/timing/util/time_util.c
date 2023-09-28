const double frame_rate_update_speed = 1.0; // 1.0;
double time_begin, zox_current_time, zox_delta_time = 0.0;
double frames_per_second_time = 0.0;
int frames_count, frames_per_second = 0;
double zox_current_time_check = 0.0;
const int record_frames_count = 120;
double zox_delta_times[120];
// todo: make physics run multiple timesteps incase it needs to step through more
const double max_zox_delta_time = 1.0 / 2.0;

double current_time_in_seconds() {
    struct timespec current_time;
    clock_gettime(CLOCK_REALTIME, &current_time);
    return current_time.tv_sec + (double) current_time.tv_nsec / 1000000000.0;
    // return (double) current_time.tv_nsec / 1000000000.0;
    // return current_time.tv_sec;
}

void initialize_time() {
    time_begin = current_time_in_seconds();
}

void iterate_time() {
    double last_time = zox_current_time;
    zox_current_time = current_time_in_seconds() - time_begin;
    zox_delta_time = zox_current_time - last_time;
    zox_current_time_check += zox_delta_time;
    for (int i = 0; i < record_frames_count - 1; i++) zox_delta_times[i] = zox_delta_times[i + 1];
    zox_delta_times[record_frames_count - 1] = zox_delta_time;
    #ifdef zox_check_current_time
        if (zox_current_time != zox_current_time_check) {
            zoxel_log("current time and check not equal: %f - %f\n", zox_current_time, zox_current_time_check);
        }
    #endif
    // zoxel_log("current time [%d]\n", zox_current_time);
    // zoxel_log("delta time [%f]\n", zox_delta_time * 1000.0);
    if (zox_delta_time > max_zox_delta_time) zox_delta_time = max_zox_delta_time;
    frames_count++;
    frames_per_second_time += zox_delta_time;
    if (frames_per_second_time >= 1.0) {
        frames_per_second_time -= 1.0;
        frames_per_second = frames_count;
        frames_count = 0;
        #ifdef zoxel_log_frames_per_second
            zoxel_log("frames_per_second [%i]\n", frames_per_second);
        #endif
    }
}

float get_total_time_seconds() {
    return (float) (zox_current_time);
}