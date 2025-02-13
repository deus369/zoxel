double time_begin, zox_current_time, zox_delta_time = 0.0;
double frames_per_second_time = 0.0;
int frames_count, frames_per_second = 0;
double zox_current_time_check = 0.0;
#define record_frames_count 120
// double zox_delta_times[record_frames_count];
// double system_times[record_frames_count];
const double max_zox_delta_time = 1.0 / 30.0;
byte last_updated_time = 0;
byte updating_time = 1;
