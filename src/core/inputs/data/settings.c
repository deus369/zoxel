#define zox_pipelines_devices_reset EcsOnLoad
#define zox_pipelines_devices_enables EcsPostUpdate // one before zox_pipelines_pre_render
#define zox_pip_raycasting EcsOnUpdate
const float joystick_min_cutoff = 0.06f;
const float joystick_cutoff_buffer = 0.12f;
unsigned char auto_switch_device = 1;
