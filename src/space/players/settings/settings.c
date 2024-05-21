#define max_players 16
ecs_entity_t zox_players[max_players];
unsigned char players_playing = 0;
#define zox_pip_player_movement EcsPreUpdate // EcsPreUpdate | EcsOnUpdate
#ifndef zox_disable_player_character3D
unsigned char game_rule_attach_to_character = 1;
#else
unsigned char game_rule_attach_to_character = 0;
#endif
#define player_vox_scale  (1 / 64.0f)
const unsigned char player_vox_index = 5; // tall vox cube (number 2)
// ui
const int2 crosshair_texture_size = (int2) { 128, 128 };
const int2 crosshair_pixel_size = (int2) { 64, 64 };
const color crosshair_color = (color) { 255, 255, 255, 88 };
