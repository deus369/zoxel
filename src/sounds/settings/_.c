#define channel_sample_rate 44100
#define sound_sample_rate 44100
#define sample_rate_f (float) sound_sample_rate
// keep big incase lag, we dont want to destroy while playing
#define sound_play_death_delay 8
#include "debug.c"
#include "io.c"
#include "generate.c"
#include "volume.c"