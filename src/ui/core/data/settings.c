float zox_ui_scale = 0.78f; // todo: effect actionbar, taskbar and user uis
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
const byte game_overlay_layer = max_layers2D - 12; // -1
// debugs
// #define zox_debug_ui_trails
// #define zoxel_debug_ui_selectable_states
const byte pause_ui_overlay_layer = 2;
const color default_fill_color = (color) { 155, 155, 155, 144 };
const color default_outline_color = (color) { 155, 88, 45, 200 };
// windows
const color default_fill_color_header = (color) { 122, 22, 22, 77 };
const color default_outline_color_header = (color) { 44, 44, 44, 77 };
const color default_fill_color_window = (color) { 22, 22, 22, 99 };
const color default_outline_color_window = (color) { 44, 44, 44, 77 };
// buttons
const color default_fill_color_button = (color) { 122, 22, 22, 77 };
const color default_outline_color_button = (color) { 155, 88, 45, 77 };
//  icons
const color default_fill_color_frame = (color) { 6, 55, 55, 122 };
const color default_outline_color_frame = (color) { 0, 0, 0, 200 };
const color default_fill_color_icon = (color) { 88, 144, 200, 200 };
const color default_outline_color_icon = (color) { 0, 0, 0, 144 };
const int default_frame_size = 96; // 64;
const int default_icon_size = 80; // 48;
const float default_icon_radius = 0.369f; // 16 outt  of 48 originally
const int default_icon_texture_size = 16; // 32
// blue + red = purple
const color default_fill_color_frame_action = (color) { 77, 6, 77, 122 };
const color default_fill_color_frame_item = (color) { 6, 6, 77, 122 };
const color default_fill_color_frame_skill = (color) { 77, 6, 6, 122 };
const color default_fill_color_frame_stat = (color) { 33, 33, 33, 122 };
// corner and outline
const byte default_button_corner = 8;
const byte default_window_corner = 16;
const byte default_button_frame_thickness = 4;
// pause settings
const float pause_fade_alpha = 0.52f;
const float pause_fade_time = 0.48f;

const color icon_overlay_fill_color = (color) { 55, 255, 255, 44 };
const color icon_overlay_outline_color = (color) { 33, 0, 0, 22 };