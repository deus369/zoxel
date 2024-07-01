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
const color default_fill_color = (color) { 155, 155, 155, 144 };
const color default_outline_color = (color) { 155, 88, 45, 200 };
// windows
const color default_fill_color_header = (color) { 122, 22, 22, 77 };
const color default_outline_color_header = (color) { 44, 44, 44, 77 };
const color default_fill_color_window = (color) { 22, 22, 22, 44 };
const color default_outline_color_window = (color) { 44, 44, 44, 77 };
// buttons
const color default_fill_color_button = (color) { 122, 22, 22, 77 };
const color default_outline_color_button = (color) { 155, 88, 45, 77 };
//  icons
const color default_fill_color_frame = (color) { 6, 55, 55, 122 };
const color default_outline_color_frame = (color) { 0, 0, 0, 200 };
const color default_fill_color_icon = (color) { 88, 144, 200, 200 };
const color default_outline_color_icon = (color) { 0, 0, 0, 144 };
const int default_icon_size = 64;
const unsigned char default_icon_radius = 16;
// pause
const float pause_fade_alpha = 0.76f;
const float pause_fade_time = 0.48f;
