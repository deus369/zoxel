#define zox_pip_player_movement EcsPreUpdate // EcsPreUpdate | EcsOnUpdate
// ui
const int2 crosshair_texture_size = (int2) { 128, 128 };
const int2 crosshair_pixel_size = (int2) { 64, 64 };
const color crosshair_color = (color) { 255, 255, 255, 88 };
// more ui
unsigned char game_ui_has_taskbar = 0;
// more
#define zoxel_event_play_game 1
#define main_camera_rotation_speed 60 * 0.22f
ecs_entity_t zoxel_main_menu;
float4 main_menu_rotation_speed;