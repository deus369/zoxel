#define canvas_edge_size 8
#define ui_dragging_brightness 1.42f
#define ui_selected_brightness 1.24f
#define ui_default_brightness 1.0f
#define ui_navigation_joystick_cutoff 0.6f
#define ui_navigation_timing 0.3
#define restore_joystick_cutoff 0.06f
// #define zox_debug_ui_trails
// #define zoxel_debug_ui_selectable_states
ecs_entity_t main_canvas;
ecs_entity_t zox_canvases[max_cameras];
int cache_header_height = 42;   // used for dragging tweaks, temp solution
