#define canvas_edge_size 8
#define ui_dragging_brightness 1.56f
#define ui_selected_brightness 1.24f
#define ui_default_brightness 0.7f
#define ui_navigation_joystick_cutoff 0.6f
#define ui_navigation_timing 0.3
#define restore_joystick_cutoff 0.06f
ecs_entity_t main_canvas;
ecs_entity_t zox_canvases[max_cameras];
// debugs
// #define zox_debug_ui_trails
// #define zoxel_debug_ui_selectable_states
