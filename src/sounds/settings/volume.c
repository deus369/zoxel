#define scale_volumes 1 // debug 0.1 / 1

// volumes
const float mixer_audio_volume = 1.0f;  // not used atm until my sound driver fixed
const float default_sound_volume = 1.0f; // 0.5f
const float default_sound_volume_loaded = 1.3f * scale_volumes;

// channels
float master_volume = 0.5f;
float volume_sfx = 0.6f;
float volume_music = 0.4f;
float music_load_volume = 0.75f;
float master_volume_increment = 0.05f;

byte get_volume_label() {
    return (int) (100 * master_volume);
}

float get_volume_sfx() {
    return master_volume * volume_sfx;
}

float get_volume_music() {
    return master_volume * volume_music;
}