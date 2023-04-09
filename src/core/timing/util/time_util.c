const double frame_rate_update_speed = 1.0;
int frames_per_second = 0;
int frames_count;
double time_passed = 0.0;
double zoxel_delta_time = 0.0;
double zoxel_max_delta_time = 1.0 / 30.0;

void iterate_fps_time() {
    frames_count++;
    time_passed += zoxel_delta_time;
    if (time_passed >= 1.0) {
        time_passed -= 1.0;
        frames_per_second = frames_count;
        frames_count = 0;
        #ifdef zoxel_log_frames_per_second
            zoxel_log("frames_per_second [%i]\n", frames_per_second);
        #endif
    }
}