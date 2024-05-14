#define max_players 16
unsigned char players_playing = 0;
ecs_entity_t zox_players[max_players];
#define zox_pip_player_movement EcsPreUpdate // EcsPreUpdate | EcsOnUpdate
#ifndef zox_disable_player_character3D
unsigned char game_rule_attach_to_character = 1;
#else
unsigned char game_rule_attach_to_character = 0;
#endif
const unsigned char player_vox_index = 1;
#define player_vox_scale  (1 / 64.0f) // 42 // * 0.5f
// ui
const int2 crosshair_texture_size = (int2) { 128, 128 };
const int2 crosshair_pixel_size = (int2) { 64, 64 };
const color crosshair_color = (color) { 255, 255, 255, 88 };
