#define scale_volumes 1 // debug 0.1 / 1

// volumes
const float default_sound_volume = 1.0f; // 0.5f
const float default_sound_volume_loaded = 1.3f * scale_volumes;
int global_master_volume = 16 * scale_volumes;
const int global_master_volume_max = 128 * scale_volumes;
const int global_master_volume_increment = 8 * scale_volumes;

// channels
float global_volume_sfx = 0.5f;
float global_volume_music = 0.38f;
float music_load_volume = 0.5f;