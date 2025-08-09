// frames
const color default_outline_color_frame = { 0, 0, 0, 200 };
const color default_outline_color_icon = { 0, 0, 0, 144 };
// nothing uses these? wait taskbar?
const color default_fill_color_frame = { 6, 55, 55, 122 };
const color default_fill_color_icon = { 88, 144, 200, 200 };

const int default_frame_size = 96;
const int default_icon_size = 64; // 64; // 48;
const float default_icon_radius = 0.369f; // 16 outt  of 48 originally
const int default_icon_texture_size = 16; // 32
// blue + red = purple
#define frame_alpha 188
#define window_alpha 122
const color default_fill_color_frame_item = { 6, 6, 77, frame_alpha };
const color default_fill_color_frame_skill = { 77, 6, 6, frame_alpha };
const color default_fill_color_frame_stat = { 33, 33, 33, frame_alpha };

// actionbar
const color fill_color_frame_action = { 5, 16, 28, frame_alpha };
const color outline_color_frame_action = { 28, 16, 4, frame_alpha };
const color fill_color_actionbar = { 2, 28, 16, window_alpha };
const color outline_color_actionbar = { 2, 44, 44, frame_alpha };

const color icon_overlay_fill_color = { 191, 107, 6, 144 };
const color icon_overlay_outline_color = { 0, 0, 0, 0 };