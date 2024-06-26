#ifndef zoxel_on_android
#define default_ui_scale 1.0f
#else
#define default_ui_scale 2.0f
#endif
#define canvas_edge_size 8
#define ui_active_brightness 1.8f
#define ui_dragging_brightness 1.56f
#define ui_selected_brightness 1.24f
#define ui_default_brightness 0.9f
#define ui_navigation_joystick_cutoff 0.6f
#define ui_navigation_timing 0.3
#define restore_joystick_cutoff 0.06f
ecs_entity_t main_canvas;
ecs_entity_t zox_canvases[max_cameras];
// debugs
// #define zox_debug_ui_trails
// #define zoxel_debug_ui_selectable_states
const unsigned char pause_ui_overlay_layer = 2;
